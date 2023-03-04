#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <string_view>
#include <memory>
#include <array>

#include "basic_physics.hpp"

namespace wava
{
    class WavAudio
    {
    private:
        uint32_t buffer;
        bool loop = true;
        bool loaded = false;

        // RIFF chunk (main chunk)
        uint32_t chunkSize;
        char format[5] = { '\0' };

        // sub-chunk 1 (fmt chunk)
        uint32_t subChunk1Size;
        uint16_t audioFormat;
        uint16_t numChannels;
        uint32_t sampleRate;
        uint32_t byteRate;
        uint16_t blockAlign;
        uint16_t bitsPerSample;

        // sub-chunk 2 (data)
        uint32_t subChunk2Size;
        unsigned char* data;

        int getFileCursorMark(std::ifstream& fs, std::string mark);

    public:
        WavAudio();
        WavAudio(const char* path);
        ~WavAudio();

        void load(const char* path);
        uint32_t getBuffer();
    };
}

namespace flat
{
    class AudioSource : public flat::PhysicsObject
    {
    private:
        ALuint source;
        void releaseAudioSource();
        void initializeAudioSource();
    public:
        AudioSource();
        ~AudioSource();
        void playSound(uint32_t buffer);
        void stopSound();
        bool getSoundLoopable();
        void setLoopable(bool b);
        void updateSoundPhysics();
    };

    class AudioListener
    {
    private:
        ALCdevice* device = nullptr;
        ALCcontext* context = nullptr;
        void initializeOpenAL();
        void releaseOpenAL();
        void createListener();
    protected:
        AudioListener();
        ~AudioListener();
        void initializeListener();
        void setListenerPosition(float x, float y, float z);
        void setListenerVelocity(float x, float y, float z);
        void setVolume(float var);
    };
}