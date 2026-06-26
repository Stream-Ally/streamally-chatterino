//
// Created by Petr Pavlík on 26.06.2026.
//

#pragma once
#include "common/Aliases.hpp"

#include <QString>

namespace chatterino {

struct StreamAllyIdentity
{
    QString platform;
    QString login;
    QString displayName;
    UserId providerUserId;
};

} // namespace chatterino