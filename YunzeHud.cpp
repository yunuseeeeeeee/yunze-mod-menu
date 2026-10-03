#include "YunzeHud.hpp"
#include "Settings.hpp"

using namespace geode::prelude;

YunzeHud* YunzeHud::create() {
    auto ret = new YunzeHud();
    if (ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool YunzeHud::init() {
    if (!CCNode::init()) return false;

    this->setID("hud"_spr);

    auto win = CCDirector::get()->getWinSize();

    m_fpsLabel = CCLabelBMFont::create("FPS: --", "bigFont.fnt");
    m_fpsLabel->setScale(0.4f);
    m_fpsLabel->setOpacity(190);
    m_fpsLabel->setAnchorPoint({0.f, 1.f});
    m_fpsLabel->setPosition({30.f, win.height - 20.f});
    this->addChild(m_fpsLabel);

    m_cpsLabel = CCLabelBMFont::create("CPS: 0", "bigFont.fnt");
    m_cpsLabel->setScale(0.4f);
    m_cpsLabel->setOpacity(190);
    m_cpsLabel->setAnchorPoint({0.f, 1.f});
    m_cpsLabel->setPosition({30.f, win.height - 40.f});
    this->addChild(m_cpsLabel);

    this->scheduleUpdate();
    return true;
}

void YunzeHud::registerClick() {
    m_clicks.push_back(m_time);
}

void YunzeHud::update(float dt) {
    if (dt <= 0.f) return;

    m_time += dt;
    m_textTimer += dt;

    float inst = 1.f / dt;
    m_fps = (m_fps <= 0.f) ? inst : (m_fps * 0.95f + inst * 0.05f);

    while (!m_clicks.empty() && m_time - m_clicks.front() > 1.f) {
        m_clicks.pop_front();
    }

    bool showFps = yunze::isOn(yunze::kFps);
    bool showCps = yunze::isOn(yunze::kCps);
    m_fpsLabel->setVisible(showFps);
    m_cpsLabel->setVisible(showCps);

    // Yazıyı saniyede ~4 kez güncelle
    if (m_textTimer >= 0.25f) {
        m_textTimer = 0.f;
        if (showFps) {
            m_fpsLabel->setString(("FPS: " + std::to_string(static_cast<int>(m_fps + 0.5f))).c_str());
        }
        if (showCps) {
            m_cpsLabel->setString(("CPS: " + std::to_string(m_clicks.size())).c_str());
        }
    }

    this->applyHideUi(PlayLayer::get());
}

void YunzeHud::applyHideUi(PlayLayer* pl) {
    bool want = yunze::isOn(yunze::kHideUi);
    if (want == m_uiHidden) return;
    if (!pl || !pl->m_uiLayer) return;

    if (want) {
        auto status = pl->m_uiLayer->getChildByID("status-label"_spr);
        m_hiddenNodes.clear();
        if (auto kids = pl->m_uiLayer->getChildren()) {
            for (auto child : CCArrayExt<CCNode*>(kids)) {
                if (child == this || child == status) continue;
                if (child->isVisible()) {
                    m_hiddenNodes.push_back(child);
                    child->setVisible(false);
                }
            }
        }
    } else {
        for (auto& node : m_hiddenNodes) {
            node->setVisible(true);
        }
        m_hiddenNodes.clear();
    }
    m_uiHidden = want;
}

void yunze::attachHud(PlayLayer* pl) {
    if (!pl || !pl->m_uiLayer) return;
    if (pl->m_uiLayer->getChildByID("hud"_spr)) return;
    pl->m_uiLayer->addChild(YunzeHud::create(), 60);
}

void yunze::registerClick() {
    auto pl = PlayLayer::get();
    if (!pl || !pl->m_uiLayer) return;
    if (auto hud = typeinfo_cast<YunzeHud*>(pl->m_uiLayer->getChildByID("hud"_spr))) {
        hud->registerClick();
    }
}
