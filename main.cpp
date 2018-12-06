#include <utility>

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <fstream>
#include <vector>
#include <chrono>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/quaternion.hpp>
#include "glm/ext.hpp"

//#include "gl/util.h"
//#include "gl/buffer.h"
//#include "gl/texture.h"
//#include "gl/uniform.h"
#include "gl/shader.h"
#include "gl/texture.h"
#include "gl/vertex_array.h"

//	class MyShaderData: public UniformData{
//		Uniform<glm::vec4> foo{"foo", this};
//		UNIFORM(glm::vec4, foo1)
//	};
//



long long int nowMillis() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()
	).count();
}

void benchmarkFormat(const gl::uiVec2& dimensions, unsigned int pixelSize,
                     const gl::uiVec2& updateDimensions,
                     gl::TextureInternalFormat internalFormat, gl::TextureFormat format,
                     int numFrames) {
	auto texture = gl::Texture2D::create(internalFormat, dimensions);

	size_t pixelsLength = pixelSize * updateDimensions.width * updateDimensions.height;
	auto *pixels = new uint8_t[pixelsLength];
	memset(pixels, 0, pixelsLength);

	auto startMs = nowMillis();
	for (int i = 0; i < numFrames; i++) {
		texture.subImage(
			{0, 0},
			updateDimensions,
			format,
			pixels
		);
	}
	auto endMs = nowMillis();
	double framePerSecond = (double) numFrames / (endMs - startMs) * 1000;
	double bytesPerSecond = pixelsLength * framePerSecond;
	double gbPerSecond = bytesPerSecond / 1000000000;
	std::cout
			<< "Texture width: " << dimensions.width << ", texture height: " << dimensions.height
			<< ", update width: " << updateDimensions.width << ", update height: " << updateDimensions.height
			<< ", pixel size: " << pixelSize
			<< ", update length: " << pixelsLength
//			<< ", internal format: " << internalFormat
//			<< ", format: " << format
			<< std::endl;

	std::cout << "Frames/sec: " << framePerSecond << ", bytes/sec: " << bytesPerSecond << ", Gbytes/sec: "
	          << gbPerSecond << std::endl;

	texture.free();

}
//
//
//
//void benchmarkFormat3D(unsigned int textureWidth, unsigned int textureHeight, unsigned int textureDepth,
//                       unsigned int pixelSize,
//                       unsigned int updateWidth, unsigned int updateHeight,
//                       GLenum internalformat, GLenum format, int numFrames) {
//	GLuint textureID;
//
//	glGenTextures(1, &textureID);
//
//	glBindTexture(GL_TEXTURE_3D, textureID);
//	if (checkGlError()) {
//		return;
//	}
//
//	glTexStorage3D(GL_TEXTURE_3D, 1, internalformat, textureWidth, textureHeight, textureDepth);
//	if (checkGlError()) {
//		return;
//	}
//
//
//	size_t pixelsLength = pixelSize * updateWidth * updateHeight;
//	char *pixels = new char[pixelsLength];
//	memset(pixels, 0, pixelsLength);
//
//	auto startMs = nowMillis();
//	for (int i = 0; i < numFrames; i++) {
//		glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0,
//		                updateWidth, updateHeight, 1,
//		                format, GL_UNSIGNED_BYTE,
//		                pixels);
//		if (checkGlError()) {
//			return;
//		}
//	}
//	auto endMs = nowMillis();
//	double framePerSecond = (double) numFrames / (endMs - startMs) * 1000;
//	double bytesPerSecond = pixelsLength * framePerSecond;
//	double gbPerSecond = bytesPerSecond / 1000000000;
//	std::cout
//			<< "(3D) Texture width: " << textureWidth << ", texture height: " << textureHeight << ", depth: "
//			<< textureDepth
//			<< ", update width: " << updateWidth << ", update height: " << updateHeight
//			<< ", pixel size: " << pixelSize
//			<< ", update length: " << pixelsLength
//			<< ", internal format: " << internalformat
//			<< ", format: " << format
//			<< std::endl;
//
//	std::cout << "Frames/sec: " << framePerSecond << ", bytes/sec: " << bytesPerSecond << ", Gbytes/sec: "
//	          << gbPerSecond << std::endl << std::endl;
//
//	glDeleteTextures(1, &textureID);
//
//}
//
void benchmarkFormat2DArray(const gl::uiVec3& dimensions, unsigned int pixelSize,
                            const gl::uiVec3& updateDimensions,
                            gl::TextureInternalFormat internalFormat, gl::TextureFormat format,
                            int numFrames) {
	auto texture = gl::Texture2DArray::create(internalFormat, dimensions);

	size_t pixelsLength = pixelSize * updateDimensions.width * updateDimensions.height;
	char *pixels = new char[pixelsLength];
	memset(pixels, 0, pixelsLength);

	auto startMs = nowMillis();
	for (int i = 0; i < numFrames; i++) {
		texture.subImage(
				{0, 0, 0},
				updateDimensions,
				format,
				(uint8_t*)pixels
				);
	}
	auto endMs = nowMillis();
	double framePerSecond = (double) numFrames / (endMs - startMs) * 1000;
	double bytesPerSecond = pixelsLength * framePerSecond;
	double gbPerSecond = bytesPerSecond / 1000000000;
	std::cout
			<< "(GL_TEXTURE_2D_ARRAY) Texture size: " << dimensions
			<< ", update size: " << updateDimensions
			<< ", pixel size: " << pixelSize
			<< ", update length: " << pixelsLength
//			<< ", internal format: " << internalformat
//			<< ", format: " << format
			<< std::endl;

	std::cout << "Frames/sec: " << framePerSecond << ", bytes/sec: " << bytesPerSecond << ", Gbytes/sec: "
	          << gbPerSecond << std::endl << std::endl;

	texture.free();

}
//
//void benchmarkFormat3DInitalStorage(unsigned int textureWidth, unsigned int textureHeight, unsigned int textureDepth,
//                                    unsigned int pixelSize,
//                                    unsigned int updateWidth, unsigned int updateHeight,
//                                    GLenum internalFormat, GLenum format, int numFrames) {
//	size_t pixelsLength = pixelSize * updateWidth * updateHeight;
//	char *pixels = new char[pixelsLength];
//	memset(pixels, 0, pixelsLength);
//
//
//	GLuint textureID;
//	glGenTextures(1, &textureID);
//	if (checkGlError("glGenTextures")) {
//		return;
//	}
//
//	glBindTexture(GL_TEXTURE_3D, textureID);
//	if (checkGlError("glBindTexture")) {
//		return;
//	}
//
//	glTexImage3D(
//			GL_TEXTURE_3D,
//			0,
//			internalFormat, //GL_R8UI,
//			textureWidth,
//			textureHeight,
//			textureDepth,
//			0,
//			format, //GL_RED_INTEGER,
//			GL_UNSIGNED_BYTE,
//			pixels
//	);
//	if (checkGlError("glTexImage3D")) {
//		return;
//	}
//
//
//
////	glTexStorage3D(GL_TEXTURE_3D, 1, internalFormat, textureWidth, textureHeight, textureDepth);
////	if(checkGlError()){
////		return;
////	}
//
//
//
//	auto startMs = nowMillis();
//	for (int i = 0; i < numFrames; i++) {
//		glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0,
//		                updateWidth, updateHeight, 1,
//		                format, GL_UNSIGNED_BYTE,
//		                pixels);
//		if (checkGlError("glTexSubImage3D")) {
//			return;
//		}
//	}
//	auto endMs = nowMillis();
//	double framePerSecond = (double) numFrames / (endMs - startMs) * 1000;
//	double bytesPerSecond = pixelsLength * framePerSecond;
//	double gbPerSecond = bytesPerSecond / 1000000000;
//	std::cout
//			<< "(3D1) Texture width: " << textureWidth << ", texture height: " << textureHeight << ", depth: "
//			<< textureDepth
//			<< ", update width: " << updateWidth << ", update height: " << updateHeight
//			<< ", pixel size: " << pixelSize
//			<< ", update length: " << pixelsLength
//			<< ", internal format: " << internalFormat
//			<< ", format: " << format
//			<< std::endl;
//
//	std::cout << "Frames/sec: " << framePerSecond << ", bytes/sec: " << bytesPerSecond << ", Gbytes/sec: "
//	          << gbPerSecond << std::endl << std::endl;
//
//	glDeleteTextures(1, &textureID);
//
//}

class MyUniforms : public gl::UniformData{

};
int main() {
	int windowWidth = 1280;
	int windowHeight = 720;
	if (!glfwInit()) {
		fprintf(stderr, "Ошибка при инициализации GLFWn");
		return -1;
	}
//    glfwSetErrorCallback(error_callback);

//    glfwWindowHint(GLFW_SAMPLES, 4); // 4x Сглаживание
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Мы хотим использовать OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Мы не хотим старый OpenGL

	GLFWwindow *window; // (В сопроводительном исходном коде эта переменная является глобальной)
	window = glfwCreateWindow(windowWidth, windowHeight, "VvV", nullptr, nullptr);
	if (window == nullptr) {

		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	printf("glfwMakeContextCurrent: %d\n", glGetError());
	// Инициализируем GLEW
	glewExperimental = GL_TRUE; // Флаг необходим в Core-режиме OpenGL
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Невозможно инициализировать GLEW\n");
		return -1;
	}
	printf("glewInit: %d\n", glGetError());
	printf("after : %d\n", glGetError());
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

//	gl::OwnerExtended o;
//	o.data = 42;
//	std::cout<<o.data<<" "<<o.b.owner->data;

//	benchmarkFormat3DInitalStorage(2048, 16384 / 16, 16, 1, 2018, 1024, GL_R8UI, GL_RED_INTEGER, 1000);
//
//	benchmarkFormat(2048, 16384, 4, 2048, 1024, GL_RGBA8, GL_BGRA, 1000);
	try{
//		benchmarkFormat2DArray({2048, 16384 / 16, 16}, 1, {2018, 1024, 1 }, gl::TextureInternalFormat::R8ui, gl::TextureFormat::RedInteger, 1000);
//		benchmarkFormat2DArray({2048, 16384 / 16, 16}, 4, {2018, 1024, 1 }, gl::TextureInternalFormat::RGBA8, gl::TextureFormat::BGRA, 1000);
		benchmarkFormat({2048, 16384}, 4, {2048, 1024}, gl::TextureInternalFormat::RGBA8, gl::TextureFormat::BGRA, 1000);
//		benchmarkFormat({2048, 16384}, 1, {2018, 1024}, gl::TextureInternalFormat::R8ui, gl::TextureFormat::RedInteger, 1000);

		const char* vertexCode = "#version 330 core\n"
		                         "\n"
		                         "// Input vertex data, different for all executions of this shader.\n"
		                         "layout(location = 0) in vec2 pos;\n"
		                         "\n"
		                         "// Values that stay constant for the whole mesh.\n"
		                         "\n"
		                         "void main(){\n"
		                         "\n"
		                         "\t// Output position of the vertex, in clip space : MVP * position\n"
		                         "\tgl_Position = vec4(pos, 0.0f, 1.0f);\n"
		                         "\n"
		                         "}";

		const char* fragmentCode = ""
							 "#version 330 core\n"
					        "out vec4 Target0;\n"
	                        "void main() {\n"
						   "   Target0 = vec4(1.0f, 0.0f, 0.0f, 1.0f);"
						   "}";
		gl::Shader s = gl::Shader::createShader(vertexCode, fragmentCode);
		std::vector<glm::vec2> vertices = {{1.0f, 1.0f}};
		std::vector<int> elements = {0};

		gl::VertexArray<glm::vec2, int> vertexArray = \
				gl::VertexArray<glm::vec2, int>::create(vertices, elements);

		auto positionsId = s.getAttribute("pos");
		vertexArray.addAttrib(positionsId, 1, 0);
		MyUniforms u;
		s.render(u, vertexArray);
		s.free();
	}catch(gl::Exception& e){
		std::cerr<<e.message<<std::endl;
		glfwTerminate();
		return -1;
	}
//	benchmarkFormat3D(2048, 16384 / 16, 16, 1, 2018, 1024, GL_R8UI, GL_RED_INTEGER, 1000);


	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	return 0;
}