//
// Created by 李政翰 on 2026/3/31.
//

#include "UI/Base/Button.hpp"


Button::Button(const std::string &ImagePath, const glm::vec2 &pos) : m_Callback(nullptr) {
    m_Drawable = std::make_shared<Util::Image>(ImagePath);
    m_Transform.translation = pos;
}

void Button::SetCallback(const std::function<void()> &callback) {
    m_Callback = callback;
}

bool Button::IsMouseHovering() const {
    glm::vec2 mousePos = Util::Input::GetCursorPosition(); // 滑鼠位置
    glm::vec2 pos = m_Transform.translation; // 圖片中心位置
    glm::vec2 size = GetSize(); // 圖片長寬

    return (mousePos.x >= pos.x - size.x / 2 &&
            mousePos.x <= pos.x + size.x / 2 &&
            mousePos.y >= pos.y - size.y / 2 &&
            mousePos.y <= pos.y + size.y / 2);
}

void Button::Update() {
    if (IsMouseHovering()) {
        // 如果想做懸停效果（例如按鈕變亮），可以寫在這裡

        if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB) ) {
            if (m_Callback) m_Callback();
        }
    }
}

glm::vec2 Button::GetSize() const {
    auto img = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
    return img ? glm::vec2(img->GetSize().x, img->GetSize().y) : glm::vec2(0.0);
}

void Button::SetImage(const std::string path) {
    auto img = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
    if (img) img -> SetImage(path);
}

void Button::SetVisualScaleFactor(float factor) {
    m_Transform.scale = m_BaseScale * factor;
}

// void Button::Lock() {m_Locked = true;}
// void Button::Unlock() {m_Locked = false;}
// bool Button::IsLocked() const {return m_Locked;}





