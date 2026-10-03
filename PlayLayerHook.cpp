#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "Settings.hpp"

using namespace geode::prelude;

class $modify(YunzePlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
        yunze::applyStatusLabel(this);
        return true;
    }
};
