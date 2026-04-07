//
// Created by 李政翰 on 2026/4/7.
//

#ifndef TEXT_HPP
#define TEXT_HPP

#include "Util/GameObject.hpp"
#include "Util/Text.hpp" // 假設框架有提供這個
#include "Util/Color.hpp"
#include <string>
#include <vector>

class Text : public Util::GameObject {

public:
    Text(const std::string& content, int fontSize);

    void SetText(const std::string& text);
    void SetSize(int size);
    void SetColor(const Util::Color& color);

private:
    void UpdateDrawable(); // 核心：當文字、大小、顏色改變時，重新產生圖片

private:
    std::string m_Content;
    int m_FontSize;
    Util::Color m_Color = Util::Color::FromName(Util::Colors::BLACK);
    std::string m_FontDir = RESOURCE_DIR "/font.ttf";

};

#endif //TEXT_HPP
