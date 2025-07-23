#pragma once

namespace gl3::ecs::components
{
    struct Shooting {
        float damage;
        float bulletSpeed = 100.0f;
        float range;
        float cooldown;
        float countdownUntilNextShot;

        Shooting(float damage = 10.0f, float range = 150.0f, float cooldown = 5.0f)
            : damage(damage),
              range(range),
              cooldown(cooldown),
              countdownUntilNextShot(cooldown) {}
    };
}
