//
// Created by Petr Pavlík on 19.11.2025.
//

#pragma once

#include "common/Aliases.hpp"

#include <memory>
#include <optional>

namespace chatterino {

struct Emote;
using EmotePtr = std::shared_ptr<const Emote>;

class StreamAllyAPI
{
    std::unordered_map<>

    void FetchStreamAllyBadges();

public:
    /**
     * Makes a request to StreamAlly API.
     */
    StreamAllyAPI();

    /**
     * Returns the Chatterino badge for the given user
     */
    std::optional<EmotePtr> getBadge(const UserId &id);
};

}
