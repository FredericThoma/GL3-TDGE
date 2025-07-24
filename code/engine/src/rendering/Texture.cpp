#include "engine/rendering/Texture.h"
#include "tiny_gltf/stb_image.h"
#include <stdexcept>
#include <filesystem>
#include <iostream>

#include "glad/glad.h"

namespace fs = std::filesystem;

namespace gl3 {

    Texture::Texture(const fs::path& path, bool flipVertically) {
        stbi_set_flip_vertically_on_load(flipVertically);

        std::string pathStr = path.string();
        unsigned char* data = stbi_load(pathStr.c_str(), &width, &height, &channels, 0);
        if (!data) {
            throw std::runtime_error("Failed to load texture: " + pathStr);
        }

        GLenum format = GL_RGB;
        if (channels == 1)
            format = GL_RED;
        else if (channels == 3)
            format = GL_RGB;
        else if (channels == 4)
            format = GL_RGBA;

        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        // PIXEL ART SETTINGS:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        stbi_image_free(data);
    }



    void Texture::bind(unsigned int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

    void Texture::unbind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    unsigned int Texture::getID() const {
        return textureID;
    }

    gl3::Texture::Texture(Texture&& other) noexcept
    : textureID(other.textureID),
      width(other.width),
      height(other.height),
      channels(other.channels)
    {
        other.textureID = 0;
        other.width = 0;
        other.height = 0;
        other.channels = 0;
    }

    gl3::Texture& gl3::Texture::operator=(Texture&& other) noexcept
    {
        if (this != &other) {
            if (textureID != 0)
                glDeleteTextures(1, &textureID);

            textureID = other.textureID;
            width = other.width;
            height = other.height;
            channels = other.channels;

            other.textureID = 0;
            other.width = 0;
            other.height = 0;
            other.channels = 0;
        }
        return *this;
    }

    gl3::Texture::~Texture()
    {
        if (textureID != 0)
            glDeleteTextures(1, &textureID);
    }

}
