#pragma once

#include "soloud_wav.h"
#include <filesystem>

#include "engine/rendering/Assets.h"

namespace gl3::ecs::components
{
    struct AudioClip {
        std::filesystem::path relativeAssetPath;
        std::unique_ptr<SoLoud::Wav> sound = std::make_unique<SoLoud::Wav>();
        float volume;
        bool shouldPlay = false;
        bool looping = false;

        AudioClip(std::filesystem::path relativeAssetPath, float vol = 1.0f, bool loop = false)
            : relativeAssetPath(std::move(relativeAssetPath)), volume(vol), shouldPlay(false), looping(loop)
        {
            sound->load(gl3::resolveAssetPath(this->relativeAssetPath).string().c_str());
        }

        void Play()
        {
            sound->setLooping(false);
            looping = false;
            shouldPlay = true;
        }

        void PlayLooping()
        {
            sound->setLooping(true);
            looping = true;
            shouldPlay = true;
        }

    };
}
