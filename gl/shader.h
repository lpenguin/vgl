//
// Created by nikita on 2018-12-03.
//

#ifndef UPLOADBENCH_SHADER_H
#define UPLOADBENCH_SHADER_H

#include <string>
#include <vector>

#include "uniform.h"
#include "base.h"
#include "vertex_array.h"
#include "itexture.h"

namespace gl {
	class _EmptyTexture: public ITexture{
		void bind(){}
		void free(){}
	};

	class TextureAttribute: public NamedObject<GLint>{
	private:
		TextureAttribute(const TextureAttribute& textureAttribute) = delete;
	public:
		ITexture& texture;

		TextureAttribute(TextureAttribute&& other) noexcept :
				NamedObject(other.objectId),
			texture(other.texture) {}

		TextureAttribute(GLint objectId, ITexture& texture):
			NamedObject(objectId),
			texture(texture){}
	};

	const GLuint GlTextures[] = {
		GL_TEXTURE0,
		GL_TEXTURE1,
		GL_TEXTURE2,
		GL_TEXTURE3
	};

	class Shader : public NamedObject<GLuint> {
		bool isBindedAttribs = false;
		void bindAttribs(UniformData &data);
		std::vector<TextureAttribute> textureAttributes;
	public:
		void addTexture(gl::ITexture& texture, const std::string &name);

		Shader(GLuint objectId):NamedObject(objectId){}

		Shader(Shader&& other) noexcept : NamedObject(other.objectId){}

		Shader& operator=(Shader&& other) noexcept{
			objectId = other.objectId;
			return *this;
		}


		GLint getAttribute(const std::string& name) const;

		static Shader createShader(const std::string &vertexShaderCode,
		                                            const std::string &fragmentShaderCode);

		template<typename VertexType, typename ElementType>
		void render(UniformData &data, VertexArray<VertexType, ElementType>& vertexArray){
			glUseProgram(objectId);
			gl::checkErrorAndThrow("glUseProgram");
			if(!isBindedAttribs){
				bindAttribs(data);
			}

			for(auto* member: data.members){
				member->assignData();
			}

			for(int i = 0; i < textureAttributes.size();i++){
				glActiveTexture(GlTextures[i]);
				textureAttributes[i].texture.bind();
				glUniform1i(textureAttributes[i].getObjectId(), i);
			}

			vertexArray.bind();
			glDrawElements(GL_TRIANGLES, vertexArray.getNumElements(), GL_UNSIGNED_INT, 0);
			vertexArray.disable();
		}

		void free(){
			glDeleteProgram(objectId);
		}
	};
}
#endif //UPLOADBENCH_SHADER_H
