//
// Created by Petr Pavlík on 20.11.2025.
//

#ifndef CHATTERINO_STREAMALLYBADGE_H
#define CHATTERINO_STREAMALLYBADGE_H

#include "messages/Emote.hpp"
#include "StreamAllyEnv.h"

#include <QString>

#include <cstddef>
#include <functional>

namespace chatterino {

struct StreamAllyBadge
{
    QString id;
    EmotePtr emote;
    StreamAllyEnv env;
};

}  // namespace chatterino

#endif  //CHATTERINO_STREAMALLYBADGE_H