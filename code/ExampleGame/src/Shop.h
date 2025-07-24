#ifndef SHOP_H
#define SHOP_H

#include <vector>
#include <memory>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <imgui.h> // ImGui core
#include <imgui_internal.h>

#include "engine/rendering/Assets.h"
#include "engine/rendering/Texture.h"

namespace fs = std::filesystem;

struct ShopTurret {
    std::string name;
    int damage;
    int range;
    float cooldown;

    fs::path assetPath;
    bool selected = false;
    gl3::Texture texture;



    ShopTurret(const std::string& name, int damage, int range,float cooldown, const fs::path& assetPath)
        : name(name), damage(damage), range(range), cooldown(cooldown), assetPath(assetPath), selected(false)
    {
        texture = gl3::Texture(gl3::resolveAssetPath((assetPath)), false);
    }
};

class Shop {
private:
    std::vector<std::shared_ptr<ShopTurret>> turrets;
    int selectedTurretIndex = -1;
    ImVec4 bg_col = ImVec4(0, 0, 0, 0);
    ImVec4 bg_col_unsel = ImVec4(0, 0, 0, 0);
    ImVec4 bg_col_sel = ImVec4(0.5, 0.5, 0.6, 1);
    ImVec4 tint_col = ImVec4(1, 1, 1, 1);
    ImVec2 uv0 = ImVec2(0.0f, 0.0f);
    ImVec2 uv1 = ImVec2(1.0f, 1.0f);
    ImVec2 scale = ImVec2(100.0f, 100.0f);

public:
    void addTurret(const std::shared_ptr<ShopTurret>& turret) {
        turrets.push_back(turret);
    }

    void selectTurret(int index) {
        if (index < 0 || index >= static_cast<int>(turrets.size()))
            return;

        for (int i = 0; i < static_cast<int>(turrets.size()); ++i) {
            turrets[i]->selected = (i == index);
        }

        selectedTurretIndex = index;
    }

    std::shared_ptr<ShopTurret> getSelectedTurret() const {
        if (selectedTurretIndex >= 0 && selectedTurretIndex < static_cast<int>(turrets.size())) {
            return turrets[selectedTurretIndex];
        }
        return nullptr;
    }

    void unselectAll() {
        for (auto& turret : turrets) {
            turret->selected = false;
        }
        selectedTurretIndex = -1;
    }

    void draw() {
        ImGui::Begin("Turret Shop");
        ImGui::Text("Press T to Place a Turret");
        for (int i = 0; i < static_cast<int>(turrets.size()); ++i) {
            auto& turret = turrets[i];
            ImGui::PushID(i);
            if (ImGui::ImageButton(turret->name.c_str(),turret->texture.getID(), ImVec2(100, 100), uv0, uv1, bg_col, tint_col))
            {
                selectTurret(i);
            }

            // Draw details
            if (turret->selected) {
                ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "%s (Selected)", turret->name.c_str());
            } else {
                ImGui::Text("%s", turret->name.c_str());
            }

            ImGui::Text("Damage: %d", turret->damage);
            ImGui::Text("Range: %d", turret->range);
            ImGui::Text("Cooldown: %d", turret->cooldown);
            ImGui::Separator();

            ImGui::PopID();
        }

        ImGui::End();
    }
};

#endif // SHOP_H
