#pragma once

#include <Geode/Geode.hpp>

class PlayLayer;

namespace yunze {
    // Ayar anahtarları
    inline constexpr char const* kFps            = "fps";
    inline constexpr char const* kCps            = "cps";
    inline constexpr char const* kHitboxes       = "hitboxes";
    inline constexpr char const* kHideUi         = "hide-ui";
    inline constexpr char const* kAutoCheckpoint = "auto-checkpoint";
    inline constexpr char const* kStatusLabel    = "status-label";
    inline constexpr char const* kToasts         = "toasts";
    inline constexpr char const* kCompactButton  = "compact-button";

    inline bool isOn(char const* key) {
        return geode::Mod::get()->getSavedValue<bool>(key, false);
    }

    inline void setOn(char const* key, bool value) {
        geode::Mod::get()->setSavedValue<bool>(key, value);
    }

    // YunzePopup.cpp
    void applyStatusLabel(PlayLayer* pl);

    // YunzeHud.cpp
    void attachHud(PlayLayer* pl);
    void registerClick();

    // HitboxFeature.cpp (sadece pratik modda çalışır)
    void tickHitboxes(PlayLayer* pl, bool& forced);
}
