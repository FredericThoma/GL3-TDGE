#include "engine/ecs/Components.h"

class ShootingSystem {
public:
    explicit ShootingSystem(entt::registry& registry) : registry(registry) {};
    ~ShootingSystem();
    void update();

private:
    entt::registry& registry;

};

