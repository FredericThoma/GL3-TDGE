#include "engine/ecs/systems/AudioSystem.h"

#include <iostream>

#include "engine/ecs/components/AudioClip.h"
#include "entt/entt.hpp"

AudioSystem::AudioSystem(entt::registry& registry) : registry(registry)
{
    audio.init();
    audio.setGlobalVolume(0.1f);
}

void AudioSystem::update() {
    auto view = registry.view<gl3::ecs::components::AudioClip>();
    for (auto entity : view) {
        auto& clip = view.get<gl3::ecs::components::AudioClip>(entity);
        if (clip.shouldPlay)
        {
            clip.sound->setVolume(clip.volume);
            if (clip.looping)
            {
                clip.sound->setLooping(true);
                audio.playBackground(*clip.sound);
            }
            else
            {
                clip.sound->setLooping(false);
                audio.play(*clip.sound);
            }
            clip.shouldPlay = false;
        }
    }
}
