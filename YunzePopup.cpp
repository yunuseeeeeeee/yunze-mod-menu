#include "YunzePopup.hpp"
#include "Settings.hpp"

#include <Geode/ui/Notification.hpp>

using namespace geode::prelude;

namespace {
    struct Feature {
        char const* key;
        char const* title;
    };

    // 2 sütun x 4 satır
    constexpr Feature kFeatures[] = {
        {yunze::kFps,            "FPS Counter"},
        {yunze::kCps,            "CPS Counter"},
        {yunze::kHitboxes,       "Show Hitboxes"},
        {yunze::kHideUi,         "Hide Game UI"},
        {yunze::kAutoCheckpoint, "Auto Checkpoint"},
        {yunze::kStatusLabel,    "Status Label"},
        {yunze::kToasts,         "Toast Messages"},
        {yunze::kCompactButton,  "Compact Button"},
    };
    constexpr int kFeatureCount = sizeof(kFeatures) / sizeof(kFeatures[0]);
}

void yunze::applyStatusLabel(PlayLayer* pl) {
    if (!pl || !pl->m_uiLayer) return;

    auto id = "status-label"_spr;
    auto existing = pl->m_uiLayer->getChildByID(id);

    if (yunze::isOn(yunze::kStatusLabel)) {
        if (existing) return;
        auto label = CCLabelBMFont::create("Yunze Mod Menu", "bigFont.fnt");
        label->setID(id);
        label->setScale(0.35f);
        label->setOpacity(150);
        auto win = CCDirector::get()->getWinSize();
        label->setPosition({win.width / 2.f, 12.f});
        pl->m_uiLayer->addChild(label, 50);
    } else if (existing) {
        existing->removeFromParent();
    }
}

YunzePopup* YunzePopup::create() {
    auto ret = new YunzePopup();
    if (ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool YunzePopup::init() {
    if (!Popup::init(440.f, 230.f)) return false;

    this->setTitle("Yunze Mod Menu");

    for (int i = 0; i < kFeatureCount; ++i) {
        int col = i / 4;
        int row = i % 4;
        float labelX = col == 0 ? -205.f : 15.f;
        float y = 50.f - row * 40.f;
        this->addRow(i, labelX, y);
    }

    auto footer = CCLabelBMFont::create("Hitboxes & Auto Checkpoint: practice mode only", "chatFont.fnt");
    footer->setScale(0.6f);
    footer->setOpacity(160);
    m_mainLayer->addChildAtPosition(footer, Anchor::Center, {0.f, -100.f});

    return true;
}

void YunzePopup::addRow(int index, float labelX, float y) {
    auto const& f = kFeatures[index];

    auto label = CCLabelBMFont::create(f.title, "bigFont.fnt");
    label->setScale(0.4f);
    label->setAnchorPoint({0.f, 0.5f});
    m_mainLayer->addChildAtPosition(label, Anchor::Center, {labelX, y});

    auto toggler = CCMenuItemToggler::createWithStandardSprites(
        this, menu_selector(YunzePopup::onToggle), 0.7f
    );
    toggler->setTag(index);
    toggler->toggle(yunze::isOn(f.key));
    m_buttonMenu->addChildAtPosition(toggler, Anchor::Center, {labelX + 180.f, y});
}

void YunzePopup::onToggle(CCObject* sender) {
    auto toggler = static_cast<CCMenuItemToggler*>(sender);
    auto const& f = kFeatures[toggler->getTag()];

    // GD, callback'i durum değişmeden ÖNCE çağırır -> yeni durum = tersi
    bool newState = !toggler->isToggled();
    yunze::setOn(f.key, newState);

    if (std::string_view(f.key) == yunze::kStatusLabel) {
        yunze::applyStatusLabel(PlayLayer::get());
    }

    if (yunze::isOn(yunze::kToasts)) {
        std::string msg = std::string(f.title) + (newState ? ": ON" : ": OFF");
        Notification::create(
            msg,
            newState ? NotificationIcon::Success : NotificationIcon::None,
            1.f
        )->show();
    }
}
