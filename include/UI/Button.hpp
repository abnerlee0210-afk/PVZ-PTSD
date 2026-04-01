//
// Created by 李政翰 on 2026/3/31.
//

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "functional"
#include <iostream>

class Button : public Util::GameObject {
public:
    Button(const std::string& ImagePath, const glm::vec2& pos);

    void SetCallback(const std::function<void()>& callback);
    bool IsMouseHovering() const; // 偵測鼠標是否在Button範圍內
    void Update();
    glm::vec2 GetSize() const;
    void SetImage(const std::string path);// 設定Button圖片
    void SetVisualScaleFactor(float factor); // 將Button顯示縮放乘上一個因子（例如 0.9 / 1.1），做為Button視覺回饋

    // 鎖定相關API(之後可能用的到)
    //void Lock();
    //void Unlock();
    //bool IsLocked() const;

private:
    std::function<void()> m_Callback;
    glm::vec2 m_BaseScale {1.0f, 1.0f};
    //bool m_Locked = false;
};

#endif //BUTTON_HPP
