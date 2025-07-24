#include "Texture.h"
#include <string>
#include <vector>
#include <functional>
#include <imgui.h>

struct UIImage
{
    gl3::Texture texture;

    UIImage() = default;
    ~UIImage() = default;

    UIImage(const UIImage&) = default;
    UIImage(UIImage&&) noexcept = default;
    UIImage& operator=(const UIImage&) = default;
    UIImage& operator=(UIImage&&) noexcept = default;
};

struct UIImageButton
{
    std::string id;
    gl3::Texture texture;
    std::function<void()> onClick;
    bool selected = false;
    ImVec4 bg_col = ImVec4(0, 0, 0, 0);
    ImVec4 bg_col_unsel = ImVec4(0, 0, 0, 0);
    ImVec4 bg_col_sel = ImVec4(0.5, 0.5, 0.6, 1);
    ImVec4 tint_col = ImVec4(1, 1, 1, 1);
    ImVec2 uv0 = ImVec2(0.0f, 0.0f);
    ImVec2 uv1 = ImVec2(1.0f, 1.0f);
    ImVec2 scale = ImVec2(100.0f, 100.0f);

    UIImageButton() = default;
    ~UIImageButton() = default;

    UIImageButton(const UIImageButton&) = default;
    UIImageButton(UIImageButton&&) noexcept = default;
    UIImageButton& operator=(const UIImageButton&) = default;
    UIImageButton& operator=(UIImageButton&&) noexcept = default;
};


struct UIText
{
    std::string text;

    UIText() = default;
    explicit UIText(const std::string& t) : text(t) {}
    ~UIText() = default;

    UIText(const UIText&) = default;
    UIText(UIText&&) noexcept = default;
    UIText& operator=(const UIText&) = default;
    UIText& operator=(UIText&&) noexcept = default;
};

struct UIElement
{
    std::string title;
    std::vector<UIText> texts;
    std::vector<UIImage> images;
    std::vector<std::shared_ptr<UIImageButton>> imageButtons;

    UIElement() = default;
    UIElement(const std::string& t) : title(t) {}
    ~UIElement() = default;

    UIElement(const UIElement&) = default;
    UIElement(UIElement&&) noexcept = default;
    UIElement& operator=(const UIElement&) = default;
    UIElement& operator=(UIElement&&) noexcept = default;
};

class UserInterface
{
public:
    std::vector<UIElement> elements;

    UserInterface() = default;
    ~UserInterface() = default;

    UserInterface(const UserInterface&) = default;
    UserInterface(UserInterface&&) noexcept = default;
    UserInterface& operator=(const UserInterface&) = default;
    UserInterface& operator=(UserInterface&&) noexcept = default;

    explicit UserInterface(std::vector<UIElement>&& elems) : elements(std::move(elems)) {}
};
