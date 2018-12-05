//
// Created by nikita on 2018-12-04.
//

#include "util.h"
#include <iostream>

#include "buffer.h"

std::shared_ptr<gl::Buffer> gl::Buffer::create(GLsizeiptr size, GLenum usage, void *data) {
	GLuint bufferId;

	glGenBuffers(1, &bufferId);
	gl::checkErrorAndThrow("glGenBuffers");

	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, bufferId);
	gl::checkErrorAndThrow("glBindBuffer");
	//usage = GL_STREAM_DRAW;
	glBufferData(GL_PIXEL_UNPACK_BUFFER, size, data, usage);
	gl::checkErrorAndThrow("glBufferData");

	return std::make_shared<Buffer>(bufferId, size);
}

void gl::Buffer::update(GLubyte *data) {
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, bufferId);
	checkErrorAndThrow("glBindBuffer");

	glBufferData(GL_PIXEL_UNPACK_BUFFER, size, nullptr, GL_STREAM_DRAW);
	checkErrorAndThrow("glBufferData");

	GLubyte* ptr = (GLubyte*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
	gl::checkErrorAndThrow("glMapBuffer");
	if(ptr)
	{
		memcpy(ptr, data, size);
		glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
		gl::checkErrorAndThrow("glUnmapBuffer");
	}else{
		std::cerr<<"Unabled to map buffer"<<std::endl;
	}
}

void gl::Buffer::free() {
	glDeleteBuffers(1, &bufferId);
	gl::checkErrorAndThrow("glDeleteBuffers");
}
