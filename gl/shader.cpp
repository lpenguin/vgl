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

std::shared_ptr<gl::Shader> gl::Shader::createShader(const std::string &vertexShaderCode,
                                                          const std::string &fragmentShaderCode) {
	auto objectId = gl::load_shaders_str(vertexShaderCode, fragmentShaderCode);
	return std::make_shared<gl::Shader>(objectId);
}


GLint gl::Shader::getAttribute(const std::string &name) const{
	return glGetUniformLocation(objectId, name.c_str());
}
