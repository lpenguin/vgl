//
// Created by nikita on 2018-12-03.
//

#ifndef UPLOADBENCH_VERTEX_ARRAY_H
#define UPLOADBENCH_VERTEX_ARRAY_H

#include <vector>
#include <memory>
#include <string>

#include "util.h"
#include "base.h"
#include "buffer.h"


namespace gl {

class VertexArrayAttrib : public NamedObject<GLuint>{
	private:
		GLint size;
		size_t offset;
		size_t stride;
	public:
		VertexArrayAttrib(GLuint objectId, GLint size, size_t offset, size_t stride) : NamedObject() {
			this->objectId = objectId;
			this->size = size;
			this->offset = offset;
			this->stride = stride;
		}

		void enable(){
			glEnableVertexAttribArray(objectId);
			gl::checkErrorAndThrow("glEnableVertexAttribArray");
			glVertexAttribPointer(objectId, size, GL_FLOAT, GL_FALSE, stride, (void*)(offset));
			gl::checkErrorAndThrow("glVertexAttribPointer");
		}

	};


	template<typename VertexType, typename ElementType>
	class VertexArray : NamedObject<GLuint>{

	private:
		std::shared_ptr<Buffer> vertexBuffer;
		std::shared_ptr<Buffer> elementBuffer;
		std::vector<VertexArrayAttrib> vertexArrayAttribs;
		int numElements;

	public:
		int getNumElements() const {
			return numElements;
		}

		void init(){
			glGenVertexArrays(1, &objectId);
			gl::checkErrorAndThrow("glGenVertexArrays");
		}

		void free(){
			// TODO:
		}
		void bind(){
			glBindVertexArray(objectId);
			for(int i = 0; i < vertexArrayAttribs.size(); i++){
				vertexArrayAttribs[i].enable();
			}
		}

		void disable(){
			for(int i = 0; i < vertexArrayAttribs.size(); i++){
				glDisableVertexAttribArray(i);
				gl::checkErrorAndThrow("glDisableVertexAttribArray");
			}
		}

		void defineData(std::vector<VertexType> &data, std::vector<ElementType>& elements){
			glBindVertexArray(objectId);
			vertexBuffer = Buffer::create(sizeof(VertexType) * data.size(), GL_STATIC_DRAW, &data[0]);
			elementBuffer = Buffer::create(sizeof(ElementType) * elements.size(), GL_STATIC_DRAW, &elements[0]);
			numElements = data.size;
		}

		void addAttrib(GLuint attribId, GLint size, size_t offset){
			auto stride = sizeof(VertexType);
			VertexArrayAttrib vat(attribId, size, offset, stride);
			vertexArrayAttribs.push_back(vat);
		}
	};


}

#endif //UPLOADBENCH_VERTEX_ARRAY_H
