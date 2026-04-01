//
// Created by 李政翰 on 2026/3/31.
//

#ifndef SCENE_HPP
#define SCENE_HPP

#include "Util/Renderer.hpp"

#include <memory>
#include "Util/GameObject.hpp"
#include "Util/Renderer.hpp"

class Scene : public Util::GameObject
{
public:
    Scene() : m_Root(std::vector<std::shared_ptr<GameObject>>{}) {}
    virtual ~Scene() = default;
    virtual void on_enter() = 0;
    virtual void on_update() = 0;
    virtual void on_render() = 0;
    virtual void on_exit() = 0;
protected:
    std::vector<std::shared_ptr<GameObject>> m_Objects;
    Util::Renderer m_Root;
};

#endif //SCENE_HPP
