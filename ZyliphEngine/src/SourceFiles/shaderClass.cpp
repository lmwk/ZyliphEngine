#include "../HeaderFiles/shaderClass.h"

#include <glm/gtc/type_ptr.hpp>

#include "../Utils/ZLogger.h"

//gets shader code in file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexfile, const char* fragmentfile, const char* geomfile)
{
	std::string vertexCode = get_file_contents(vertexfile);
	std::string fragmentCode = get_file_contents(fragmentfile);
	std::string geomCode = get_file_contents(geomfile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();
	const char* geomSource = geomCode.c_str();

	GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, &vertexSource, NULL);
	glCompileShader(vertexshader);
	compileErrors(vertexshader, "VERTEX");

	//Compiling the fragment shader and what not
	GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentshader);
	compileErrors(fragmentshader, "FRAGMENT");

	GLuint geomshader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geomshader, 1, &geomSource, NULL);
	glCompileShader(geomshader);
	compileErrors(fragmentshader, "GEOMETRY");

	//Creating a shader program and stuff
	ID = glCreateProgram();
	glAttachShader(ID, vertexshader);
	glAttachShader(ID, fragmentshader);
	glAttachShader(ID, geomshader);
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");

	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);
	glDeleteShader(geomshader);
}

Shader::Shader(const char* vertexfile, const char* fragmentfile)
{
	std::string vertexCode = get_file_contents(vertexfile);
	std::string fragmentCode = get_file_contents(fragmentfile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, &vertexSource, NULL);
	glCompileShader(vertexshader);
	compileErrors(vertexshader, "VERTEX");

	//Compiling the fragment shader and what not
	GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentshader);
	compileErrors(fragmentshader, "FRAGMENT");

	//Creating a shader program and stuff
	ID = glCreateProgram();
	glAttachShader(ID, vertexshader);
	glAttachShader(ID, fragmentshader);
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");

	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);
}


void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::compileErrors(unsigned shader, const char* type)
{
	GLint hasCompiled;
	char infolog[1024];
    if (type != "PROGRAM")
    {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
			glGetShaderInfoLog(shader, 1024, NULL, infolog);
			Z_CORE_CRITICAL("SHADER_COMPILATION_ERROR for: {0} \n {1}", type, infolog);
        }
    }
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infolog);
			Z_CORE_CRITICAL("SHADER_LINKING_ERROR for: {0} \n {1}", type, infolog);
		}
	}
}
