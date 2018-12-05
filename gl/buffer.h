//
// Created by nikita on 2018-12-03.
//

#ifndef UPLOADBENCH_BUFFER_H
#define UPLOADBENCH_BUFFER_H

#include <memory>
#include "base.h"

namespace gl {
	class Buffer{

	private:
		GLuint bufferId;
		GLsizeiptr size;


	public:
		Buffer(GLuint bufferId, GLsizeiptr size) : bufferId(0), size(size) {}

		static std::shared_ptr<Buffer> create(GLsizeiptr size, GLenum usage, GLvoid* data = nullptr);

		GLuint getBufferId() const {
			return bufferId;
		}

		GLsizeiptr getSize() const {
			return size;
		}

		void update(GLubyte* data);

		void free();
	};


}

#endif //UPLOADBENCH_BUFFER_H
