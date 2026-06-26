//
// Created by Petr Pavlík on 21.11.2025.
//

#ifndef CHATTERINO_STREAMALLYUSER_H
#define CHATTERINO_STREAMALLYUSER_H
#include "common/Aliases.hpp"
#include "StreamAllyIdentity.h"

#include <QString>
#include <unordered_set>
#include <unordered_map>

QStringAlias(StreamAllyUserId);

namespace chatterino {
struct StreamAllyBadge;

struct StreamAllyUser
{
    QString streamAllyId;
    std::unordered_map<QString, StreamAllyIdentity> identities;
    std::unordered_set<StreamAllyBadge> ownedBadges;
};

} // namespace chatterino

#endif  //CHATTERINO_STREAMALLYUSER_H
