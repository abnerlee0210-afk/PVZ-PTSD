#include "UI/ShovelButton.hpp"

ShovelButton::ShovelButton(const std::string& imagePath, const glm::vec2& position)
    : Button(imagePath, position) { // 直接呼叫父類別建構子處理圖片與位置
    m_Selected = false;
}

void ShovelButton::SetSelected(bool selected) {
    m_Selected = selected;

    // 利用 Button 提供的視覺縮放 API
    if (m_Selected) {
        SetVisualScaleFactor(1.1f); // 選取時放大
    } else {
        SetVisualScaleFactor(1.0f); // 取消時恢復原狀
    }
}

void ShovelButton::Update() {
    // 必須呼叫父類別的 Update，才會執行 IsMouseHovering 偵測與 Callback
    Button::Update();

    // 如果你有額外的每幀邏輯（例如選取後的閃爍效果）可以寫在這裡
}