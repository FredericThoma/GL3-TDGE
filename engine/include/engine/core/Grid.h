#include <vector>

#include "engine/ecs/systems/RenderSystem.h"
#include "entt/entt.hpp"

class Grid {
public:
    struct Cell {
        std::vector<entt::entity> entities;
    };

    Grid(int width, int height);

    const Cell& at(int x, int y) const;
    void addEntity(entt::entity e, int x, int y);
    void removeEntity(entt::entity e, int x, int y);
    void draw(gl3::ecs::systems::RenderSystem& rendersystem) const;

    int width() const;   // in cells
    int height() const;  // in cells

private:
    int width_, height_;           // original screen width/height in pixels
    int gridWidth_, gridHeight_;   // computed grid dimensions in cells
    std::vector<std::vector<Cell>> grid_;
};
