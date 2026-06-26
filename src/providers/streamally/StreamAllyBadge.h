//
// Created by Petr Pavlík on 20.11.2025.
//

#ifndef CHATTERINO_STREAMALLYBADGE_H
#define CHATTERINO_STREAMALLYBADGE_H

#include "messages/Emote.hpp"

#include <QString>

#include <cstddef>
#include <functional>

namespace chatterino {

struct StreamAllyBadge
{
    EmotePtr emote;

    bool operator==(const StreamAllyBadge &other) const
    {
        if (this->emote == other.emote)
        {
            return true;
        }
        if (!this->emote || !other.emote)
        {
            return false;
        }
        return this->emote->id == other.emote->id;
    }
};

}  // namespace chatterino

template <>
struct std::hash<chatterino::StreamAllyBadge>
{
    std::size_t operator()(const chatterino::StreamAllyBadge &badge) const noexcept
    {
        if (!badge.emote)
        {
            return 0;
        }
        return std::hash<QString>{}(badge.emote->id.string);
    }
};

#endif  //CHATTERINO_STREAMALLYBADGE_H