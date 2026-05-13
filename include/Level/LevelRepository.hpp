//
// Created by hankl on 2026/4/5.
//

#ifndef LEVELREPOSITORY_HPP
#define LEVELREPOSITORY_HPP

#include "Level/LevelConfig.hpp"

class LevelRepository {
public:
    static LevelConfig GetLevel(int levelId);

private:
    static LevelConfig CreateLevel1();
    static LevelConfig CreateLevel2();
    static LevelConfig CreateLevel3();
};

#endif //LEVELREPOSITORY_HPP
