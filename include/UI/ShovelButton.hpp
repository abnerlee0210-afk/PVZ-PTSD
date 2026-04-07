//
// Created by 李政翰 on 2026/3/18.
//

#ifndef SHOVELBUTTON_HPP
#define SHOVELBUTTON_HPP

#include "UI/Base/Button.hpp" // 確保路徑正確引用到你的 Button.hpp

// 繼承 Button，自動獲得圖片顯示、座標轉換、滑鼠偵測與 Callback 功能
class ShovelButton : public Button {
public:
    ShovelButton(const std::string& imagePath, const glm::vec2& position);

    // 覆寫 Update 以加入選取狀態的視覺邏輯
    void Update();

    void SetSelected(bool selected);
    bool IsSelected() const { return m_Selected; }

private:
    bool m_Selected = false;
};

#endif //SHOVELBUTTON_HPP
