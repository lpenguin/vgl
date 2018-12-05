//
// Created by nikita on 2018-12-02.
//

#ifndef UPLOADBENCH_UTIL_H
#define UPLOADBENCH_UTIL_H

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace gl{
	GLuint load_shaders_str(const std::string &vertex_shader_code, const std::string &fragment_shader_code);

	char const *getErrorString(GLenum const err) noexcept;

	GLenum checkError(const char *name = nullptr);

	class Exception{
	public:
		GLenum code;
		const std::string message;
	};

	void checkErrorAndThrow(const char* name = nullptr);

}
#endif //UPLOADBENCH_UTIL_H
