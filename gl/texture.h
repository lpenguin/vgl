//
// Created by nikita on 2018-12-03.
//

#ifndef UPLOADBENCH_TEXTURE_H
#define UPLOADBENCH_TEXTURE_H

#include "util.h"
#include "buffer.h"
#include "vec.h"

namespace gl {
	enum class TextureType : GLenum {
		Texture2D = GL_TEXTURE_2D,
		Texture2DArray = GL_TEXTURE_2D_ARRAY
	};

	GLenum toGlTarget(TextureType textureType) {
		return static_cast<GLenum>(textureType);
	}


	enum class TextureInternalFormat : GLenum {

	};

	GLenum toGlInternalFormat(TextureInternalFormat internalFormat) {
		return static_cast<GLenum>(internalFormat);
	}

	enum class TextureFormat : GLenum {

	};

	GLenum toGlFormat(TextureFormat format) {
		return static_cast<GLenum>(format);
	}


	template<class T, GLenum textureType>
	class Texture {
	private:
		GLuint textureId;
		TextureInternalFormat internalFormat;

		T dimensions;



	private:
		static void TexStorage(GLenum internalFormat, const T &dimensions) {
			throw "Unimplemented";
		}

		static void TexSubImage(const T &offset, const T &dimensions, GLenum format, GLenum type, GLvoid *data) {
			throw "Unimplemented";
		}

	public:
		Texture(GLuint textureId, TextureInternalFormat internalFormat, const T &dimensions)
				: textureId(textureId), internalFormat(internalFormat), dimensions(dimensions) {}

		static std::shared_ptr<Texture<T, textureType>>
		create(TextureInternalFormat internalFormat, const T &dimensions) {
			auto glInternalFormat = toGlInternalFormat(internalFormat);

			GLuint textureId;

			glGenTextures(1, &textureId);
			checkErrorAndThrow("glGenTextures");

			glBindTexture(textureType, textureId);
			checkErrorAndThrow("glGenTextures");

			TexStorage(glInternalFormat, dimensions);
			return std::make_shared<Texture<T, textureType>>(textureId, internalFormat, dimensions);
		}

		void subImage(const T &offset, const T &dimensions, TextureFormat format, const Buffer &buffer) {
			glBindTexture(GL_TEXTURE_2D, textureId);
			checkErrorAndThrow("glBindTexture");

			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffer.getBufferId());
			checkErrorAndThrow("glBindBuffer");

			auto glFormat = toGlFormat(format);
			TexSubImage(offset, dimensions, glFormat, GL_UNSIGNED_BYTE, 0);
		}

		void subImage(const T &offset, const T &dimensions, TextureFormat format, uint8_t *data) {
			glBindTexture(GL_TEXTURE_2D, textureId);
			checkErrorAndThrow("glBindTexture");

			auto glFormat = toGlFormat(format);
			TexSubImage(offset, dimensions, glFormat, GL_UNSIGNED_BYTE, data);
		}

		static void bindToZero() {
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
		}

		void free() {
			glDeleteTextures(1, &textureId);
		}


	};

	template <>
	void Texture<uiVec2, GL_TEXTURE_2D>::TexStorage(GLenum internalFormat, const uiVec2 &dimensions) {
		glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat, dimensions.width, dimensions.height);
		checkErrorAndThrow("glTexStorage2D");
	}

	template <>
	void Texture<uiVec2, GL_TEXTURE_2D>::TexSubImage(const uiVec2 &offset, const uiVec2 &dimensions, GLenum format, GLenum type, GLvoid *data) {
		glTexSubImage2D(
				GL_TEXTURE_2D, 0,
				offset.x, offset.y,
				dimensions.width, dimensions.width,
				format, type, data);
		checkErrorAndThrow("glTexSubImage2D");
	}

	template <>
	void Texture<uiVec3, GL_TEXTURE_2D_ARRAY>::TexStorage(GLenum internalFormat, const uiVec3 &dimensions) {
		glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, internalFormat, dimensions.width, dimensions.height,
		               dimensions.depth);
		checkErrorAndThrow("glTexStorage3D");
	}

	template <>
	void Texture<uiVec3, GL_TEXTURE_2D_ARRAY>::TexSubImage(const uiVec3 &offset, const uiVec3 &dimensions, GLenum format, GLenum type, GLvoid *data) {
		glTexSubImage3D(
				GL_TEXTURE_2D, 0,
				offset.x, offset.y, offset.z,
				dimensions.width, dimensions.width, dimensions.height,
				format, type, data);
		checkErrorAndThrow("glTexSubImage2D");
	}

	typedef Texture<uiVec2, GL_TEXTURE_2D> Texture2D;
	typedef Texture<uiVec3, GL_TEXTURE_2D_ARRAY> Texture2DArray;
}

#endif //UPLOADBENCH_TEXTURE_H
