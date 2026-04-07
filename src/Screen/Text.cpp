//
// Created by 李政翰 on 2026/4/7.
//
#include "Screen//Text.hpp"

Text::Text(const std::string& content, int fontSize)
    : m_Content(content), m_FontSize(fontSize) {
    UpdateDrawable();
}

void Text::SetText(const std::string& text) {
    if (m_Content == text) return; // 避免重複渲染
    m_Content = text;
    UpdateDrawable();
}

void Text::UpdateDrawable() {
    // 這裡是最關鍵的步驟：將文字轉為 Image 貼圖
    // 假設 Util::Text 能產生一個能被 GameObject 使用的 Drawable
    m_Drawable = std::make_shared<Util::Text>(m_FontDir, m_FontSize, m_Content, m_Color);
}

void Text::SetColor(const Util::Color& color) {
    m_Color = color;
    UpdateDrawable();
}