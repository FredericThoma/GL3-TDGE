#include "engine/ecs/Components.h"

class TargetingSystem {
public:
    explicit TargetingSystem(entt::registry& registry) : registry(registry) {};
    ~TargetingSystem() = default;
    void update();
    entt::entity getNearestEnemy(entt::entity entity) const;
    entt::entity getLowestEnemy() const;
    entt::entity getFurthestEnemy() const;


private:
    entt::registry& registry;

};

