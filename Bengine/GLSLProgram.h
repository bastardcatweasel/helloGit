#pragma once
#include <string>
#include <GL/glew.h>

namespace Bengine{
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();
		void use();
		void unuse();

		void compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);

		void linkShaders();
		void addAttribute(const std::string& attributeName);
		GLuint getUniformLocation(const std::string& uniformName);
	private:
		int _numAttributes;
		GLuint _programID;

		GLuint _vertexShaderID;

		GLuint _fragmentShaderID;

		void compileShader(const std::string &filePath, GLuint id);
	};

}