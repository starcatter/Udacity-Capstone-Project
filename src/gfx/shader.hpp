//
// Created by superbob on 2020-06-03.
//

#ifndef CAPSTONE_SDL_SHADER_HPP
#define CAPSTONE_SDL_SHADER_HPP


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

// based on https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader.h
class Shader
{
public:
	static std::string shader_path;
	
	unsigned int ID;
	
	// constructor generates the shader on the fly
	// ------------------------------------------------------------------------
	Shader( const std::string vertexPath, const std::string fragmentPath );
	
	// activate the shader
	// ------------------------------------------------------------------------
	void use()
	{
		glUseProgram(ID);
	}
	
	// utility uniform functions
	// ------------------------------------------------------------------------
	void setBool( const std::string &name, bool value ) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
	}
	
	// ------------------------------------------------------------------------
	void setInt( const std::string &name, int value ) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	
	// ------------------------------------------------------------------------
	void setFloat( const std::string &name, float value ) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	
	// ------------------------------------------------------------------------
	void setVec2( const std::string &name, const glm::vec2 &value ) const
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	
	void setVec2( const std::string &name, float x, float y ) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}
	
	// ------------------------------------------------------------------------
	void setVec3( const std::string &name, const glm::vec3 &value ) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	
	void setVec3( const std::string &name, float x, float y, float z ) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
	
	// ------------------------------------------------------------------------
	void setVec4( const std::string &name, const glm::vec4 &value ) const
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	
	void setVec4( const std::string &name, float x, float y, float z, float w )
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}
	
	// ------------------------------------------------------------------------
	void setMat2( const std::string &name, const glm::mat2 &mat ) const
	{
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	
	// ------------------------------------------------------------------------
	void setMat3( const std::string &name, const glm::mat3 &mat ) const
	{
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	
	// ------------------------------------------------------------------------
	void setMat4( const std::string &name, const glm::mat4 &mat ) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

private:
	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void checkCompileErrors( GLuint shader, std::string type );
};


#endif //CAPSTONE_SDL_SHADER_HPP
