//
// Created by 李政翰 on 2026/4/11.
//

#ifndef BOARDPRESETS_HPP
#define BOARDPRESETS_HPP

#include "Board/BoardLayout.hpp"
#include "Level/LevelTypes.hpp"

class BoardPresets {
public:
    static BoardLayout GetLayout(BoardTypes type);

};

#endif //BOARDPRESETS_HPP
