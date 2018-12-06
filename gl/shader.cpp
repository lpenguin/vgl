//
// Created by nikita on 2018-12-03.
//
#include "shader.h"
#include "util.h"

void gl::Shader::bindAttribs(UniformData &data) {
	for(auto* member: data.members){
		member->attrId = getAttribute(member->name);
	}
	isBindedAttribs = true;
}

gl::Shader gl::Shader::create(const std::string &vertexShaderCode,
                              const std::string &fragmentShaderCode) {
	auto objectId = gl::load_shaders_str(vertexShaderCode, fragmentShaderCode);
	return gl::Shader(objectId);
}


GLint gl::Shader::getAttribute(const std::string &name) const{
	return glGetUniformLocation(objectId, name.c_str());
}

void gl::Shader::addTexture(gl::ITexture& texture, const std::string &name) {
	auto textureAttribute = getAttribute(name);
	textureAttributes.emplace_back(TextureAttribute(textureAttribute, texture));
}
