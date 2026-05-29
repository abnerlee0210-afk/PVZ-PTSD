//
// Created by 李政翰 on 2026/3/31.
//

#include "Screen/BackgroundImage.hpp"
#include "Render/RenderLayer.hpp"

BackgroundImage::BackgroundImage(std::string& path)
    : GameObject(
        std::make_unique<Util::Image>(path),
        RenderLayer::BACKGROUND
    )
{
}

void BackgroundImage::Set_Background(const std::string path) {
    auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
    if (temp) {
        temp->SetImage(path);
        LOG_DEBUG("Set Background!");
    } else {
        LOG_DEBUG("BackgroundImage: m_Drawable is not Util::Image!");
    }
}


