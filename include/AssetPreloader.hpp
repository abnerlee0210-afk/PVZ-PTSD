//
// Created by LAB1223 on 2026/6/12.
//

#ifndef ASSETPRELOADER_HPP
#define ASSETPRELOADER_HPP

#include <memory>
#include <vector>
#include "Util/Animation.hpp"

class AssetPreloader {
public:
    static void PreloadAllAnimations();

private:
    static std::vector<std::shared_ptr<Util::Animation>> s_Animations;
};

#endif
