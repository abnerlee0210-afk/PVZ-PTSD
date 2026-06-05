//
// Created by LAB1223 on 2026/6/5.
//
#include "UI/WaveProgressBar.hpp"

#include <algorithm>

WaveProgressBar::WaveProgressBar(const glm::vec2& position)
    : m_Position(position) {

    m_BarFramePaths = {
        RESOURCE_DIR "/graphics/UI/WaveProgressBar/Progress_0.png",
        RESOURCE_DIR "/graphics/UI/WaveProgressBar/Progress_1.png",
        RESOURCE_DIR "/graphics/UI/WaveProgressBar/Progress_2.png",
        RESOURCE_DIR "/graphics/UI/WaveProgressBar/Progress_3.png",
        RESOURCE_DIR "/graphics/UI/WaveProgressBar/Progress_4.png",
        RESOURCE_DIR "/graphics/UI/WaveProgressBar/Progress_5.png",
        RESOURCE_DIR "/graphics/UI/WaveProgressBar/Progress_6.png",
        RESOURCE_DIR "/graphics/UI/WaveProgressBar/Progress_7.png",
        RESOURCE_DIR "/graphics/UI/WaveProgressBar/Progress_8.png"
    };
}

void WaveProgressBar::Create(Util::Renderer& root) {
    if (m_Created || m_BarFramePaths.empty()) {
        return;
    }

    auto backImage = std::make_shared<Util::Image>(
        RESOURCE_DIR "/graphics/UI/WaveProgressBar/Progress_9.png"
    );

    m_BackBarWidth = backImage->GetSize().x;

    m_BackBarObject = std::make_shared<Util::GameObject>(
        backImage,
        9.0f
    );

    m_BackBarObject->m_Transform.translation = m_Position;

    auto frontImage = std::make_shared<Util::Image>(
        m_BarFramePaths[0]
    );

    m_FrontBarWidth = frontImage->GetSize().x;

    m_FrontBarObject = std::make_shared<Util::GameObject>(
        frontImage,
        10.0f
    );

    UpdateFrontBarPosition();

    m_ZombieHeadObject = std::make_shared<Util::GameObject>(
        std::make_shared<Util::Image>(
            RESOURCE_DIR "/graphics/UI/WaveProgressBar/ZombieHead.png"
        ),
        11.0f
    );
    m_ZombieHeadObject->m_Transform.translation = {
        m_Position.x + m_HeadMinX,
        m_Position.y
    };

    root.AddChild(m_ZombieHeadObject);

    root.AddChild(m_BackBarObject);
    root.AddChild(m_FrontBarObject);
    m_Created = true;
}

void WaveProgressBar::Destroy(Util::Renderer& root) {
    if (m_BackBarObject) {
        root.RemoveChild(m_BackBarObject);
        m_BackBarObject = nullptr;
    }

    if (m_ZombieHeadObject) {
        root.RemoveChild(m_ZombieHeadObject);
        m_ZombieHeadObject = nullptr;
    }

    m_Created = false;
    m_CurrentFrameIndex = -1;
}

void WaveProgressBar::SetProgress(float progress) {
    if (!m_FrontBarObject) {
        return;
    }

    m_Progress = std::clamp(progress, 0.0f, 1.0f);

    int frameIndex = ProgressToFrameIndex(m_Progress);

    if (frameIndex != m_CurrentFrameIndex) {
        m_CurrentFrameIndex = frameIndex;

        auto frontImage = std::make_shared<Util::Image>(
            m_BarFramePaths[m_CurrentFrameIndex]
        );

        m_FrontBarWidth = frontImage->GetSize().x;

        m_FrontBarObject->SetDrawable(frontImage);
        UpdateFrontBarPosition();
    }

    UpdateZombieHeadPosition(m_Progress);
}

int WaveProgressBar::ProgressToFrameIndex(float progress) const {
    if (m_BarFramePaths.empty()) {
        return 0;
    }

    int maxIndex = static_cast<int>(m_BarFramePaths.size()) - 1;
    int index = static_cast<int>(progress * maxIndex + 0.5f);

    return std::clamp(index, 0, maxIndex);
}

void WaveProgressBar::UpdateZombieHeadPosition(float progress) {
    if (!m_ZombieHeadObject) {
        return;
    }

    float x = m_HeadMaxX - (m_HeadMaxX - m_HeadMinX) * progress;

    m_ZombieHeadObject->m_Transform.translation = {
        m_Position.x + x,
        m_Position.y
    };
}

void WaveProgressBar::UpdateFrontBarPosition() {
    if (!m_FrontBarObject) {
        return;
    }

    float backLeftX = m_Position.x - m_BackBarWidth / 2.0f;
    float frontCenterX = backLeftX + m_FrontBarWidth / 2.0f;

    m_FrontBarObject->m_Transform.translation = {
        frontCenterX,
        m_Position.y
    };
}