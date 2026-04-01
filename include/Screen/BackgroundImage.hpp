//
// Created by 李政翰 on 2026/3/31.
//

#ifndef BACKGROUNDIMAGE_HPP
#define BACKGROUNDIMAGE_HPP

#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "Util/GameObject.hpp"
#include <string>
#include <vector>

class BackgroundImage : public Util::GameObject {

public:
    BackgroundImage();

    void Set_Background(const std::string path);
    void SetPosition(const glm::vec2& Position);

};

#endif //BACKGROUNDIMAGE_HPP
