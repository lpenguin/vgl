//
// Created by nikita on 2018-12-03.
//

#ifndef UPLOADBENCH_BUFFER_H
#define UPLOADBENCH_BUFFER_H

#include <memory>
#include <iostream>
#include "base.h"

namespace gl {
	enum class BufferTarget : GLuint {
		PixelUnpackBuffer = GL_PIXEL_UNPACK_BUFFER,
		ArrayBuffer = GL_ARRAY_BUFFER,
	};

	enum class BufferUsage : GLuint {
		StreamDraw = GL_STREAM_DRAW,
		StaticDraw = GL_STATIC_DRAW
	};

	template<BufferTarget target>
	class Buffer: NamedObject<GLuint>{

	private:
		GLuint objectId;
		GLsizeiptr size;
		const GLuint glTarget = static_cast<GLenum>(target);

	public:
		Buffer(GLuint objectId, GLsizeiptr size, BufferUsage usage, GLvoid* data) : NamedObject(objectId), size(size) {
			bind();
			glBufferData(glTarget, size, data, static_cast<GLenum>(usage));
			gl::checkErrorAndThrow("glBufferData");

		}

		Buffer(Buffer&& other) noexcept: NamedObject(other.objectId), size(other.size)  {}

		Buffer(const Buffer& buffer) = delete;

		static Buffer create(GLsizeiptr size, BufferUsage usage, GLvoid* data = nullptr){
			GLuint bufferId;
			glGenBuffers(1, &bufferId);
			gl::checkErrorAndThrow("glGenBuffers");

			return {bufferId, size, usage, data};
		}

		GLuint getBufferId() const {
			return objectId;
		}

		GLsizeiptr getSize() const {
			return size;
		}

		void update(GLubyte* data){
			glBindBuffer(glTarget, objectId);
			checkErrorAndThrow("glBindBuffer");

			glBufferData(glTarget, size, nullptr, GL_STREAM_DRAW);
			checkErrorAndThrow("glBufferData");

			GLubyte* ptr = (GLubyte*)glMapBuffer(glTarget, GL_WRITE_ONLY);
			gl::checkErrorAndThrow("glMapBuffer");
			if(ptr)
			{
				memcpy(ptr, data, size);
				glUnmapBuffer(glTarget);
				gl::checkErrorAndThrow("glUnmapBuffer");
			}else{
				std::cerr<<"Unabled to map buffer"<<std::endl;
			}
		}

		void free(){
			glDeleteBuffers(glTarget, &objectId);
			gl::checkErrorAndThrow("glDeleteBuffers");
		}

		void bind(){
			std::cout<<glTarget<<", "<<GL_ARRAY_BUFFER<<", "<<objectId<<std::endl;
			glBindBuffer(glTarget, objectId);
			gl::checkErrorAndThrow("glBindBuffer");
		}
	};

	typedef Buffer<BufferTarget::ArrayBuffer> ArrayBuffer;
	typedef Buffer<BufferTarget::PixelUnpackBuffer> PixelUnpackBuffer;


}

#endif //UPLOADBENCH_BUFFER_H
