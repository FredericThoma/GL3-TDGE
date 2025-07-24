#pragma once

#include <filesystem>

namespace gl3 {

    class Texture {
    public:
        Texture() = default;
        explicit Texture(const std::filesystem::path& path, bool flipVertically = true);
        ~Texture();

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        Texture(Texture&& other) noexcept;
        Texture& operator=(Texture&& other) noexcept;

        void bind(unsigned int slot = 0) const;
        void unbind() const;
        unsigned int getID() const;

    private:
        unsigned int textureID = 0;
        int width = 0;
        int height = 0;
        int channels = 0;
    };

}
