//
// Created by LAB1223 on 2026/6/5.
//

#ifndef WAVEPROGRESSBAR_HPP
#define WAVEPROGRESSBAR_HPP

#include "pch.hpp"

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Renderer.hpp"

class WaveProgressBar {
public:
    explicit WaveProgressBar(const glm::vec2& position);

    void Create(Util::Renderer& root);
    void Destroy(Util::Renderer& root);

    void SetProgress(float progress);

private:
    int ProgressToFrameIndex(float progress) const;
    void UpdateZombieHeadPosition(float progress);

private:
    glm::vec2 m_Position;

    std::shared_ptr<Util::GameObject> m_BackBarObject;
    std::shared_ptr<Util::GameObject> m_FrontBarObject;
    std::shared_ptr<Util::GameObject> m_ZombieHeadObject;

    std::vector<std::string> m_BarFramePaths;

    float m_Progress = 0.0f;
    int m_CurrentFrameIndex = -1;

    float m_HeadMinX = -75.0f;
    float m_HeadMaxX = 75.0f;
    float m_HeadY = -10.0f;

    bool m_Created = false;
};

#endif
