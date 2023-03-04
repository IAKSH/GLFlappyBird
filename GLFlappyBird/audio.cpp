#include "audio.hpp"

#include <iostream>
#include <fstream>
#include <format>
#include <array>

#include <AL/al.h>
#include <AL/alc.h>

flat::AudioSource::AudioSource()
{
    initializeAudioSource();
}

flat::AudioSource::~AudioSource()
{
    releaseAudioSource();
}

void flat::AudioSource::releaseAudioSource()
{
    alDeleteSources(1, &source);
}

void flat::AudioSource::initializeAudioSource()
{
    alGenSources(1, &source);
    alSourcef(source, AL_PITCH, 1.0f);
    alSourcef(source, AL_GAIN, 1.0f);
}

void flat::AudioSource::playSound(uint32_t buffer)
{
    alSourcei(source, AL_BUFFER, buffer);
    alSourcePlay(source);
}

void flat::AudioSource::stopSound()
{
    alSourceStop(source);
}

void flat::AudioSource::updateSoundPhysics()
{
    alBuffer3f(source, AL_POSITION, posX, posY, posZ);
    alBuffer3f(source, AL_VELOCITY, velX, velY, velZ);
}

void flat::AudioSource::setLoopable(bool b)
{
    alSourcei(source, AL_LOOPING, b);
}

bool flat::AudioSource::getSoundLoopable()
{
    int val;
    alGetSourcei(source, AL_LOOPING, &val);
    return static_cast<bool>(val);
}

int wava::WavAudio::getFileCursorMark(std::ifstream& fs, std::string mark)
{
    int len = mark.length();
    char* buf = new char[len + 1];
    buf[len] = '\0';
    int i = 0;
    while (!fs.eof())
    {
        fs.seekg(i++, std::ios::beg);
        fs.read(buf, sizeof(char) * len);
        if (mark.compare(buf) == 0)
        {
            delete[] buf;
            return i;
        }
    }
    std::cerr << "[libwavaudio] ERROR: failed to locate mark (" << mark << ") in moveFileCursorToMark()\n";
    abort();

}

wava::WavAudio::WavAudio()
{

}

wava::WavAudio::WavAudio(const char* path)
{
    load(path);
}

wava::WavAudio::~WavAudio()
{
    alDeleteBuffers(1, &buffer);
}

void wava::WavAudio::load(const char* path)
{
    int i;
    std::ifstream fs(path, std::ios::in | std::ios::binary);
    if (!fs)
    {
        std::cerr << "[libwavaudio] ERROR: can't open file (" << path << ")\n";
        abort();
    }

    i = getFileCursorMark(fs, "RIFF") - 1;
    fs.seekg(i + 4, std::ios::beg);
    fs.read((char*)&chunkSize, 4);
    fs.seekg(i + 8, std::ios::beg);
    fs.read((char*)&format, 4);

    if (std::string(format).compare("WAVE") != 0)
    {
        std::cerr << "[libwavaudio] ERROR: trying to load a none-wav format file (" << path << ")\n";
        abort();
    }

    i = getFileCursorMark(fs, "fmt") - 1;
    fs.seekg(i + 4, std::ios::beg);
    fs.read((char*)&subChunk1Size, 4);
    fs.seekg(i + 8, std::ios::beg);
    fs.read((char*)&audioFormat, 2);
    fs.seekg(i + 10, std::ios::beg);
    fs.read((char*)&numChannels, 2);
    fs.seekg(i + 12, std::ios::beg);
    fs.read((char*)&sampleRate, 4);
    fs.seekg(i + 16, std::ios::beg);
    fs.read((char*)&byteRate, 4);
    fs.seekg(i + 20, std::ios::beg);
    fs.read((char*)&blockAlign, 2);
    fs.seekg(i + 22, std::ios::beg);
    fs.read((char*)&bitsPerSample, 2);
    fs.seekg(i + 24, std::ios::beg);

    i = getFileCursorMark(fs, "data") - 1;
    fs.seekg(i + 4, std::ios::beg);
    fs.read((char*)&subChunk2Size, 4);
    fs.seekg(i + 8, std::ios::beg);
    data = new unsigned char[subChunk2Size];
    fs.read((char*)data, subChunk2Size);

    // load data to OpenAL buffer
    alGenBuffers(1, &buffer);
    if (bitsPerSample == 16)
    {
        if (numChannels == 1)
            alBufferData(buffer, AL_FORMAT_MONO16, data, subChunk2Size, sampleRate);
        else if (numChannels == 2)
            alBufferData(buffer, AL_FORMAT_STEREO16, data, subChunk2Size, sampleRate);
        else
            abort();
    }
    else if (bitsPerSample == 8)
    {
        if (numChannels == 1)
            alBufferData(buffer, AL_FORMAT_MONO8, data, subChunk2Size, sampleRate);
        else if (numChannels == 2)
            alBufferData(buffer, AL_FORMAT_STEREO8, data, subChunk2Size, sampleRate);
        else
            abort();
    }
    else
    {
        std::cerr << std::format("[ERROR] wava::WavAudio::load > unsupported format,bitsPerSample = {}", bitsPerSample) << std::endl;
        abort();
    }

    // release data
    delete[] data;
    fs.close();

    loaded = true;
}

uint32_t wava::WavAudio::getBuffer()
{
    if (loaded)
        return buffer;
    else
    {
        std::cerr << "[libwavaudio] ERROR: called getBuffer() from an unloaded WavAudio\n";
        abort();
    }
}

flat::AudioListener::AudioListener()
{
    initializeListener();
}

flat::AudioListener::~AudioListener()
{
    releaseOpenAL();
}

void flat::AudioListener::initializeListener()
{
    initializeOpenAL();
}

void flat::AudioListener::setListenerPosition(float x, float y, float z)
{

}

void flat::AudioListener::setListenerVelocity(float x, float y, float z)
{

}

void flat::AudioListener::setVolume(float val)
{

}

void flat::AudioListener::initializeOpenAL()
{
    // open defeault device
    device = alcOpenDevice(nullptr);
    context = alcCreateContext(device, nullptr);
    alcMakeContextCurrent(context);
}

void flat::AudioListener::releaseOpenAL()
{
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
}