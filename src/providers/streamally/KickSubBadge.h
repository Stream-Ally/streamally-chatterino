//
// Created by Petr Pavlík on 30.06.2026.
//

#pragma once

namespace chatterino {

using EmotePtr = std::shared_ptr<const Emote>;

struct KickSubBadge {
    int months;
    int monthTreshold;
    EmotePtr emote;
};

}