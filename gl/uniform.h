//
// Created by nikita on 2018-12-03.
//

#ifndef UPLOADBENCH_UNIFORM_H
#define UPLOADBENCH_UNIFORM_H

#define UNIFORM(type, name) gl::Uniform<type> name{#name, this};

#include <vector>
#include <iostream>
#include <glm/glm.hpp>

#include "base.h"

namespace gl {
	enum class UniformType {
		Float, Vec4, Mat4x4
	};

	class UniformBase;
	class Shader;

	class UniformData {
		friend class Shader;
	private:
		std::vector<UniformBase*> members;
	public:
		void addUniform(UniformBase* uniform){
			members.push_back(uniform);
		}
	};

	class UniformBase {
	public:
		UniformBase(std::string name, UniformData* data):name(name),attrId(0){
			data->addUniform(this);
		}
		GLint attrId;
		std::string name;

		virtual void assignData() = 0;

	};

	template <class T>
	class Uniform : public UniformBase {
	private:
		static void _assign(GLint attrId, const T& data){
			std::cerr<<"Not implemented"<<std::endl;
		}
	public:
		Uniform(std::string name, UniformData* ownerData):UniformBase(name, ownerData){}
		T data;

		void assignData(){
			_assign(attrId, data);
		}

		Uniform& operator=(const T& data){
			this->data = data;
			return *this;
		}
	};

//	template <>
//	void Uniform<glm::vec4>::_assign(GLint attrId, const glm::vec4& data){
//		glUniform4fv(attrId, 1, &data[0]);
//	}
//
//	template <>
//	void Uniform<glm::mat4>::_assign(GLint attrId, const glm::mat4& data){
//		glUniformMatrix4fv(attrId, 1, GL_FALSE, &data[0][0]);
//	}
}
#endif //UPLOADBENCH_UNIFORM_H
