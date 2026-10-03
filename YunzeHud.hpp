#pragma once

#include <Geode/Geode.hpp>
#include <deque>
#include <vector>

// PlayLayer'ın UI katmanına eklenen: FPS/CPS göstergesi + "UI gizle" yöneticisi
class YunzeHud : public cocos2d::CCNode {
public:
    static YunzeHud* create();
    void registerClick();

protected:
    bool init() override;
    void update(float dt) override;
    void applyHideUi(PlayLayer* pl);

    cocos2d::CCLabelBMFont* m_fpsLabel = nullptr;
    cocos2d::CCLabelBMFont* m_cpsLabel = nullptr;

    std::deque<float> m_clicks;
    float m_time = 0.f;
    float m_fps = 0.f;
    float m_textTimer = 0.f;

    bool m_uiHidden = false;
    std::vector<geode::Ref<cocos2d::CCNode>> m_hiddenNodes;
};
