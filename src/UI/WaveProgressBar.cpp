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

    m_BarFrameImages.clear();
    for (const auto& path : m_BarFramePaths) {
        m_BarFrameImages.push_back(std::make_shared<Util::Image>(path));
    }

    auto backImage = std::make_shared<Util::Image>(
        RESOURCE_DIR "/graphics/UI/WaveProgressBar/Progress_9.png"
    );
    m_BackBarWidth = backImage->GetSize().x;
    m_BackBarObject = std::make_shared<Util::GameObject>(backImage, 9.0f);
    m_BackBarObject->m_Transform.translation = m_Position;

    auto frontImage = m_BarFrameImages[0];
    m_FrontBarWidth = frontImage->GetSize().x;
    m_FrontBarObject = std::make_shared<Util::GameObject>(frontImage, 10.0f);
    UpdateFrontBarPosition();

    root.AddChild(m_BackBarObject);
    root.AddChild(m_FrontBarObject);

    m_CurrentFrameIndex = -1;
    SetProgress(0.0f);
    m_Created = true;
}

void WaveProgressBar::Destroy(Util::Renderer& root) {
    if (m_BackBarObject) {
        root.RemoveChild(m_BackBarObject);
        m_BackBarObject = nullptr;
    }

    if (m_FrontBarObject) {
        root.RemoveChild(m_FrontBarObject);
        m_FrontBarObject = nullptr;
    }

    m_BarFrameImages.clear();
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

        // 當 m_CurrentFrameIndex 等於 9 (陣列大小) 時，代表進度完全達到 1.0f，才隱藏 FrontBar
        if (m_CurrentFrameIndex >= static_cast<int>(m_BarFrameImages.size())) {
            m_FrontBarObject->SetVisible(false);
        }
        else {
            m_FrontBarObject->SetVisible(true);

            auto frontImage = m_BarFrameImages[m_CurrentFrameIndex];
            m_FrontBarWidth = frontImage->GetSize().x;

            m_FrontBarObject->SetDrawable(frontImage);
            UpdateFrontBarPosition();
        }
    }
}

int WaveProgressBar::ProgressToFrameIndex(float progress) const {
    progress = std::clamp(progress, 0.0f, 1.0f);

    // 修正核心：如果進度百分之百，直接回傳 9 (陣列大小) 來隱藏前端條
    if (progress >= 1.0f) {
        return static_cast<int>(m_BarFrameImages.size());
    }

    // 乘以 9.0f (圖片張數) 而不是 10.0f
    // 這樣 0.88 ~ 0.999 的進度都會被精準分配在 index 8 (Progress_8.png)
    int index = static_cast<int>(progress * static_cast<float>(m_BarFrameImages.size()));

    return index;
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