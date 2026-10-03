#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "YunzePopup.hpp"
#include "Settings.hpp"

using namespace geode::prelude;

class $modify(YunzeMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto win = CCDirector::get()->getWinSize();

        auto item = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("Yunze"),
            this,
            menu_selector(YunzeMenuLayer::onYunze)
        );
        item->setScale(yunze::isOn(yunze::kCompactButton) ? 0.6f : 0.8f);
        item->setPosition({win.width - 50.f, win.height - 25.f});

        auto menu = CCMenu::create();
        menu->setPosition({0.f, 0.f});
        menu->addChild(item);
        this->addChild(menu, 100);

        return true;
    }

    void onYunze(CCObject*) {
        YunzePopup::create()->show();
    }
};
