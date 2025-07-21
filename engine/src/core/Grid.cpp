#include "engine/core/Grid.h"
#include "engine/ecs/systems/RenderSystem.h"
#include <stdexcept>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

constexpr int TILE_SIZE = 128;

Grid::Grid(int width, int height)
    : width_(width), height_(height),
      gridWidth_(width / TILE_SIZE), gridHeight_(height / TILE_SIZE),
      grid_(gridHeight_, std::vector<Cell>(gridWidth_)) {
    // Nothing else needed
}

void Grid::draw(gl3::ecs::systems::RenderSystem& rendersystem) const {
    const float tileSize = static_cast<float>(TILE_SIZE);

    glm::mat4 viewProj = rendersystem.GetProjection() * rendersystem.GetView();
    gl3::renderer::Renderer& renderer = rendersystem.getRenderer();

    for (int y = 0; y < gridHeight_; ++y) {
        for (int x = 0; x < gridWidth_; ++x) {
            const auto& cell = grid_[y][x];

            glm::vec4 color;
            if (cell.entities.empty()) {
                bool isLightSquare = (x + y) % 2 == 0;
                color = isLightSquare
                    ? glm::vec4(0.9f, 0.9f, 0.9f, 1.0f)
                    : glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
            } else {
                color = glm::vec4(0.8f, 0.3f, 0.3f, 1.0f);
            }

            glm::mat4 model = glm::translate(glm::mat4(1.0f),
                                             glm::vec3(x * tileSize, y * tileSize, 0.0f));
            model = glm::scale(model, glm::vec3(tileSize, tileSize, 1.0f));
            glm::mat4 mvp = viewProj * model;

            renderer.drawQuad(mvp, color);
        }
    }
}

const Grid::Cell& Grid::at(int x, int y) const {
    return grid_[y][x];
}

void Grid::addEntity(entt::entity e, int x, int y) {
    grid_[y][x].entities.push_back(e);
}

void Grid::removeEntity(entt::entity e, int x, int y) {
    auto& entities = grid_[y][x].entities;
    entities.erase(std::remove(entities.begin(), entities.end(), e), entities.end());
}

int Grid::width() const {
    return gridWidth_;
}

int Grid::height() const {
    return gridHeight_;
}
