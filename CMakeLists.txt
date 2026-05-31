cmake_minimum_required(VERSION 3.16)
project(REPLACE_WITH_YOUR_PROJECT_NAME)

set(CMAKE_CXX_STANDARD 17)

cmake_policy(SET CMP0135 NEW)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    ptsd

    URL         https://github.com/ntut-open-source-club/practical-tools-for-simple-design/archive/refs/tags/v0.2.zip

    # Or alternatively if you want to use a specific git commit instead of a release:
    # GIT_REPOSITORY  https://github.com/ntut-open-source-club/practical-tools-for-simple-design.git
    # GIT_TAG         <git_tag>

    SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/PTSD
)

FetchContent_MakeAvailable(ptsd)

include(files.cmake)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
list(TRANSFORM SRC_FILES PREPEND ${SRC_DIR}/)
list(TRANSFORM INCLUDE_FILES PREPEND ${INCLUDE_DIR}/)

# file(GLOB_RECURSE SRC_FILES src/*)
# file(GLOB_RECURSE HEADER_FILES include/*)

add_executable(${PROJECT_NAME}
    ${SRC_DIR}/main.cpp
    ${SRC_FILES}
    ${HEADER_FILES}
        include/Scene/MenuScene.hpp
        include/UI/Base/Button.hpp
        src/UI/Base/Button.cpp
        src/Scene/MenuScene.cpp
        include/Scene/Scene.hpp
        include/Screen/BackgroundImage.hpp
        src/Screen/BackgroundImage.cpp
        include/Scene/LevelSelectScene.hpp
        src/Scene/LevelSelectScene.cpp
        include/UI/LevelCard.hpp
        src/UI/LevelCard.cpp
        include/Manager/SceneManager.hpp
        src/Manager/SceneManager.cpp
        include/Board/GameBoard.hpp
        src/Board/GameBoard.cpp
        include/Entity/Zombie/BasicZombie.hpp
        "include/Entity/Zombie/ConeheadZombie.hpp"
        include/Entity/Object/LawnMower.hpp
        include/Entity/Projectile/Pea.hpp
        include/Entity/Plant/Peashooter.hpp
        include/Entity/Plant/Plant.hpp
        include/Entity/Projectile/Projectile.hpp
        include/Entity/Object/Sun.hpp
        include/Entity/Plant/Sunflower.hpp
        include/Entity/Zombie/Zombie.hpp
        include/Level/LevelConfig.hpp
        include/Level/LevelRepository.hpp
        include/Level/LevelTypes.hpp
        include/UI/SeedCard.hpp
        include/UI/ShovelButton.hpp
        include/Scene/BowlingLevelScene.hpp
        include/Scene/NormalLevelScene.hpp
        src/Entity/Zombie/BasicZombie.cpp
        src/Entity/Zombie/ConeheadZombie.cpp
        src/Entity/Object/LawnMower.cpp
        src/Entity/Projectile/Pea.cpp
        src/Entity/Plant/Peashooter.cpp
        src/Entity/Plant/Plant.cpp
        src/Entity/Projectile/Projectile.cpp
        src/Entity/Object/Sun.cpp
        src/Entity/Plant/Sunflower.cpp
        src/Entity/Zombie/Zombie.cpp
        src/Level/LevelRepository.cpp
        src/Scene/BowlingLevelScene.cpp
        src/Scene/NormalLevelScene.cpp
        src/UI/SeedCard.cpp
        src/UI/ShovelButton.cpp
        include/Screen/Text.hpp
        src/Screen/Text.cpp
        include/Factory/SeedCardFactory.hpp
        src/Factory/SeedCardFactory.cpp
        include/UI/SeedChooser.hpp
        src/UI/SeedChooser.cpp
        include/Factory/PlantFactory.hpp
        src/Factory/PlantFactory.cpp
        include/Factory/ZombieFactory.hpp
        src/Factory/ZombieFactory.cpp
        include/Board/BoardLayout.hpp
        include/Board/BoardPresets.hpp
        src/Board/BoardPresets.cpp
        include/Factory/ProjectileFactory.hpp
        src/Factory/ProjectileFactory.cpp
        include/Animation/AnimationStateController.hpp
        include/Factory/AnimationFactory.hpp
        src/Factory/AnimationFactory.cpp
        include/Entity/Plant/CherryBomb.hpp
        src/Entity/Plant/CherryBomb.cpp
        include/Entity/Zombie/PoleVaultingZombie.hpp
        src/Entity/Zombie/PoleVaultingZombie.cpp
        include/Entity/Plant/WallNut.hpp
        src/Entity/Plant/WallNut.cpp
        include/Entity/Plant/PotatoMine.hpp
        src/Entity/Plant/PotatoMine.cpp
        include/Entity/Projectile/SnowPea.hpp
        src/Entity/Projectile/SnowPea.cpp
        src/Entity/Plant/SnowPeashooter.cpp
        include/Entity/Plant/SnowPeashooter.hpp
        include/Render/RenderLayer.hpp
        include/UI/ChoosePlantPanel.hpp
        src/UI/ChoosePlantPanel.cpp
        include/Entity/Plant/RepeaterPea.hpp
        src/Entity/Plant/RepeaterPea.cpp
        include/Entity/Zombie/BucketheadZombie.hpp
        src/Entity/Zombie/BucketheadZombie.cpp
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Resources")
else()
    message(FATAL_ERROR "relative RESOURCE_DIR is WIP, Please use `-DCMAKE_BUILD_TYPE=Debug` build for now.")
    # target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCE_DIR="${CMAKE_INSTALL_PREFIX}/Resources")
endif()

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${DEPENDENCY_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/PTSD/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}
    SDL2::SDL2main
    PTSD
)
