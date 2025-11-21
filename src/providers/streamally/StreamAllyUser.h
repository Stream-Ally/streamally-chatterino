//
// Created by Petr Pavlík on 21.11.2025.
//

#ifndef CHATTERINO_STREAMALLYUSER_H
#define CHATTERINO_STREAMALLYUSER_H
#include "common/Aliases.hpp"

#include <QString>

namespace chatterino {

struct StreamAllyUser
{
    QString streamAllyId;
    UserId twitchId;
};

} // namespace chatterino

#endif  //CHATTERINO_STREAMALLYUSER_H
