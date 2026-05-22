#include "Factory/AnimationFactory.hpp"

namespace {
std::shared_ptr<Util::Animation> CreateNumberedAnimation(
    const std::string& prefix,
    const std::string& suffix,
    int firstFrame,
    int lastFrame,
    bool play,
    std::size_t interval,
    bool looping,
    std::size_t cooldown = 0
) {
    std::vector<std::string> paths;
    paths.reserve(static_cast<std::size_t>(lastFrame - firstFrame + 1));

    for (int i = firstFrame; i <= lastFrame; ++i) {
        paths.push_back(prefix + std::to_string(i) + suffix);
    }

    return std::make_shared<Util::Animation>(paths, play, interval, looping, cooldown);
}
}

std::shared_ptr<Util::Animation> AnimationFactory::CreateBasicZombieWalk() {
    return CreateNumberedAnimation(
        RESOURCE_DIR "/graphics/Zombies/NormalZombie/Zombie/Zombie_",
        ".png",
        0,
        21,
        true,
        100,
        true
    );
}

std::shared_ptr<Util::Animation> AnimationFactory::CreatePeashooterIdle() {
    return CreateNumberedAnimation(
        RESOURCE_DIR "/graphics/Plants/Peashooter/Peashooter_",
        ".png",
        0,
        12,
        true,
        100,
        true
    );
}

std::shared_ptr<Util::Animation> AnimationFactory::CreateRepeaterPeaIdle() {
    return CreateNumberedAnimation(
        RESOURCE_DIR "/graphics/Plants/RepeaterPea/RepeaterPea_",
        ".png",
        0,
        14,
        true,
        100,
        true
    );
}

std::shared_ptr<Util::Animation> AnimationFactory::CreateSunflowerIdle() {
    return CreateNumberedAnimation(
        RESOURCE_DIR "/graphics/Plants/SunFlower/SunFlower_",
        ".png",
        0,
        17,
        true,
        100,
        true
    );
}

std::shared_ptr<Util::Animation> AnimationFactory::CreateSnowPeaIdle() {
    return CreateNumberedAnimation(
        RESOURCE_DIR "/graphics/Plants/SnowPea/SnowPea_",
        ".png",
        0,
        14,
        true,
        100,
        true
    );
}

std::shared_ptr<Util::Animation> AnimationFactory::CreateCherryBombExplode() {
    return CreateNumberedAnimation(
        RESOURCE_DIR "/graphics/Plants/CherryBomb/CherryBomb_",
        ".png",
        0,
        6,
        true,
        100,
        false
    );
}

std::shared_ptr<Util::Animation> AnimationFactory::CreateChomperIdle() {
    return CreateNumberedAnimation(
        RESOURCE_DIR "/graphics/Plants/Chomper/Chomper/Chomper_",
        ".png",
        0,
        12,
        true,
        100,
        true
    );
}

std::shared_ptr<Util::Animation> AnimationFactory::CreateChomperAttack() {
    return CreateNumberedAnimation(
        RESOURCE_DIR "/graphics/Plants/Chomper/ChomperAttack/ChomperAttack_",
        ".png",
        0,
        8,
        false,
        60,
        false
    );
}

std::shared_ptr<Util::Animation> AnimationFactory::CreateChomperDigest() {
    return CreateNumberedAnimation(
        RESOURCE_DIR "/graphics/Plants/Chomper/ChomperDigest/ChomperDigest_",
        ".png",
        0,
        5,
        true,
        140,
        true
    );
}

std::shared_ptr<Util::Animation> AnimationFactory::CreateZombieBoomDie() {
    return CreateNumberedAnimation(
        RESOURCE_DIR "/graphics/Zombies/NormalZombie/BoomDie/BoomDie_",
        ".png",
        0,
        19,
        true,
        60,
        false
    );
}
