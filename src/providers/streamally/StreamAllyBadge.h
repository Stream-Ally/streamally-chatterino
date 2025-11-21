//
// Created by Petr Pavlík on 20.11.2025.
//

#ifndef CHATTERINO_STREAMALLYBADGE_H
#define CHATTERINO_STREAMALLYBADGE_H

#include "messages/Emote.hpp"
#include "StreamAllyUser.h"

#include <QString>

namespace chatterino {

struct StreamAllyBadge
{
    EmotePtr emote;
    std::vector<StreamAllyUser> owners{};
};

} // namespace chatterino


#endif  //CHATTERINO_STREAMALLYBADGE_H
