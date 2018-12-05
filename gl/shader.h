//
// Created by nikita on 2018-12-03.
//

#ifndef UPLOADBENCH_SHADER_H
#define UPLOADBENCH_SHADER_H

#include <string>

#include "uniform.h"
#include "base.h"
#include "vertex_array.h"

namespace gl {
	class Shader : public NamedObject<GLuint> {
		bool isBindedAttribs = false;

		void bindAttribs(UniformData &data);
	public:
		Shader(GLuint objectId){this->objectId = objectId;}

		GLint getAttribute(const std::string& name) const;

		static std::shared_ptr<Shader> createShader(const std::string &vertexShaderCode,
		                                            const std::string &fragmentShaderCode);

		template<typename VertexType, typename ElementType>
		void render(UniformData &data, VertexArray<VertexType, ElementType>& vertexArray){
			glUseProgram(objectId);

			if(!isBindedAttribs){
				bindAttribs(data);
			}

			for(auto* member: data.members){
				member->assignData();
			}

			vertexArray.bind();
			glDrawElements(GL_TRIANGLES, vertexArray.getNumElements(), GL_UNSIGNED_INT, 0);
			vertexArray.disable();
		}
	};
}
#endif //UPLOADBENCH_SHADER_H
