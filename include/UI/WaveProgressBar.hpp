//
// Created by LAB1223 on 2026/6/5.
//

#ifndef WAVEPROGRESSBAR_HPP
#define WAVEPROGRESSBAR_HPP

#include "pch.hpp"

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Renderer.hpp"
#include <vector>
#include <string>
#include <memory>

class WaveProgressBar {
public:
    explicit WaveProgressBar(const glm::vec2& position);

    void Create(Util::Renderer& root);
    void Destroy(Util::Renderer& root);

    void SetProgress(float progress);
    void UpdateFrontBarPosition();

private:
    int ProgressToFrameIndex(float progress) const;

private:
    glm::vec2 m_Position;

    std::shared_ptr<Util::GameObject> m_BackBarObject;
    std::shared_ptr<Util::GameObject> m_FrontBarObject;

    std::vector<std::string> m_BarFramePaths;
    std::vector<std::shared_ptr<Util::Image>> m_BarFrameImages;

    float m_Progress = 0.0f;
    int m_CurrentFrameIndex = -1;

    float m_BackBarWidth = 0.0f;
    float m_FrontBarWidth = 0.0f;

    bool m_Created = false;
};

#endif