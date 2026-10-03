#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "Settings.hpp"

using namespace geode::prelude;

class $modify(YunzePlayLayer, PlayLayer) {
    struct Fields {
        float m_cpTimer = 0.f;
        bool m_forcedDebug = false;
    };

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
        yunze::applyStatusLabel(this);
        yunze::attachHud(this);
        return true;
    }

    void postUpdate(float dt) {
        PlayLayer::postUpdate(dt);

        // Otomatik checkpoint: sadece pratik modda, 3 saniyede bir
        if (m_isPracticeMode && yunze::isOn(yunze::kAutoCheckpoint)
            && m_player1 && !m_player1->m_isDead) {
            m_fields->m_cpTimer += dt;
            if (m_fields->m_cpTimer >= 3.f) {
                m_fields->m_cpTimer = 0.f;
                this->markCheckpoint();
            }
        } else {
            m_fields->m_cpTimer = 0.f;
        }

        yunze::tickHitboxes(this, m_fields->m_forcedDebug);
    }
};
