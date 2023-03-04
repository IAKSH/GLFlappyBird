#include "shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <string>

flat::Shader::Shader(std::string_view vshaderPath, std::string_view fshaderPath)
{
	loadAnimation(vshaderPath, fshaderPath);
}

flat::Shader::Shader()
{

}

flat::Shader::~Shader()
{
	glDeleteShader(shaderProgram);
}

uint32_t flat::Shader::makeShaderProgram(std::string& vshader, std::string& fshader)
{
	uint32_t shaderProgram = glCreateProgram();
	uint32_t vertexShader = compileVertexShader(vshader);
	uint32_t fragmentShader = compileFragmentShader(fshader);

	checkVertexShader(vertexShader);
	checkFragmentShader(fragmentShader);

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

uint32_t flat::Shader::compileVertexShader(std::string_view vshader)
{
	const char* source = &vshader.at(0);
	uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &source, nullptr);
	glCompileShader(vertexShader);
	return vertexShader;
}

uint32_t flat::Shader::compileFragmentShader(std::string_view fshader)
{
	const char* source = &fshader.at(0);
	uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &source, nullptr);
	glCompileShader(fragmentShader);
	return fragmentShader;
}

void flat::Shader::checkVertexShader(uint32_t vshaderProgram)
{
	int success;
	char infoLog[512];
	glGetShaderiv(vshaderProgram, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vshaderProgram, sizeof(infoLog), nullptr, infoLog);
		std::cout << "[ERROR] flat::Shader::checkVertexShader | Failed to compile vertex shader:\n" << infoLog << std::endl;
		abort();
	}
}

void flat::Shader::checkFragmentShader(uint32_t fshaderProgram)
{
	int success;
	char infoLog[512];
	glGetShaderiv(fshaderProgram, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fshaderProgram, sizeof(infoLog), nullptr, infoLog);
		std::cout << "[ERROR] flat::Shader::checkFragmentShader | Failed to compile fragment shader:\n" << infoLog << std::endl;
		abort();
	}
}

void flat::Shader::use()
{
	glUseProgram(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture0"), 0);// "texture0" -> GL_TEXTURE0
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 1);// "texture1" -> GL_TEXTURE1
}

// set position offset then draw image
void flat::Shader::draw(flat::TransformMap& map, std::array<float, 3>* trans, std::array<float, 4>* rotate, flat::GameObject& go)
{
	glm::mat4 matrix(1.0f);
	if (trans)
		matrix = glm::translate(matrix, glm::vec3(trans->at(0), trans->at(1), trans->at(2)));
	if (rotate)
		matrix = glm::rotate(matrix, rotate->at(0), glm::vec3(rotate->at(0), rotate->at(1), rotate->at(2)));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(matrix));

	go.drawRaw();
}

void flat::Shader::loadAnimation(std::string_view vshaderPath, std::string_view fshaderPath)
{
	std::string vshaderBuffer, fshaderbuffer, readinBuffer;
	std::ifstream ifs(&vshaderPath.at(0), std::ios::in);
	while (!ifs.eof())
	{
		std::getline(ifs, readinBuffer);
		vshaderBuffer += readinBuffer + '\n';
	}

	readinBuffer = "";
	ifs.close();

	ifs.open(&fshaderPath.at(0), std::ios::in);
	while (!ifs.eof())
	{
		std::getline(ifs, readinBuffer);
		fshaderbuffer += readinBuffer + '\n';
	}

	shaderProgram = makeShaderProgram(vshaderBuffer, fshaderbuffer);
}