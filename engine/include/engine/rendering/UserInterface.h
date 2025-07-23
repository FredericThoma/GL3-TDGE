#include "Texture.h"
#include <string>
#include <vector>

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
