#include <Geode/Geode.hpp>
#include "Settings.hpp"

using namespace geode::prelude;

// Hitbox gösterimi SADECE pratik modda açılır.
// Derleme hatası verirse bu dosyadaki fonksiyon gövdesini boşaltmak yeterli.
void yunze::tickHitboxes(PlayLayer* pl, bool& forced) {
    bool want = yunze::isOn(yunze::kHitboxes) && pl->m_isPracticeMode;

    if (want) {
        pl->m_isDebugDrawEnabled = true;
        pl->updateDebugDraw();
        forced = true;
    } else if (forced) {
        pl->m_isDebugDrawEnabled = false;
        pl->updateDebugDraw();
        forced = false;
    }
}
