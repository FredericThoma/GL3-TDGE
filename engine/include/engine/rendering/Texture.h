#pragma once

#include <filesystem>

namespace gl3 {

    class Texture {
    public:
        explicit Texture(const std::filesystem::path& path, bool flipVertically = true);
        ~Texture();

        void bind(unsigned int slot = 0) const;
        void unbind() const;

    private:
        unsigned int textureID = 0;
        int width = 0;
        int height = 0;
        int channels = 0;
    };

}
