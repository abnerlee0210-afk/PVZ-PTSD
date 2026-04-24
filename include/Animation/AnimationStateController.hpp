//
// Created by hankl on 2026/4/24.
//

#ifndef ANIMATION_STATE_CONTROLLER_HPP
#define ANIMATION_STATE_CONTROLLER_HPP

#include "pch.hpp"

#include <unordered_map>
#include <memory>

#include "Util/Animation.hpp"

template<typename StateEnum>
class AnimationStateController {
public:
    void AddAnimation(StateEnum state, const std::shared_ptr<Util::Animation>& animation) {
        m_Animations[state] = animation;
    }

    void SetState(StateEnum state) {
        if (m_HasState && m_CurrentState == state) {
            return;
        }

        m_CurrentState = state;
        m_HasState = true;

        auto it = m_Animations.find(state);
        if (it != m_Animations.end() && it->second) {
            it->second->Play();
            m_CurrentAnimation = it->second;
        } else {
            m_CurrentAnimation = nullptr;
        }
    }

    std::shared_ptr<Util::Animation> GetCurrentAnimation() const {
        return m_CurrentAnimation;
    }

    StateEnum GetState() const {
        return m_CurrentState;
    }

private:
    std::unordered_map<StateEnum, std::shared_ptr<Util::Animation>> m_Animations;
    std::shared_ptr<Util::Animation> m_CurrentAnimation = nullptr;
    StateEnum m_CurrentState{};
    bool m_HasState = false;
};

#endif
