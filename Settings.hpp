#pragma once

#include <Geode/Geode.hpp>

class PlayLayer;

namespace yunze {
    inline constexpr char const* kStatusLabel   = "status-label";
    inline constexpr char const* kToasts        = "toasts";
    inline constexpr char const* kCompactButton = "compact-button";

    inline bool isOn(char const* key) {
        return geode::Mod::get()->getSavedValue<bool>(key, false);
    }

    inline void setOn(char const* key, bool value) {
        geode::Mod::get()->setSavedValue<bool>(key, value);
    }

    // PlayLayer içinde durum yazısını ayara göre ekler/kaldırır
    void applyStatusLabel(PlayLayer* pl);
}
