#pragma once

#include <Geode/Geode.hpp>

class YunzePopup : public geode::Popup {
public:
    static YunzePopup* create();

protected:
    bool init();
    void addRow(int index, float y);
    void onToggle(cocos2d::CCObject* sender);
};
