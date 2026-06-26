//
// Created by Petr Pavlík on 19.11.2025.
//

#pragma once

#include "common/Aliases.hpp"
#include "StreamAllyBadge.h"
#include "StreamAllyUser.h"
#include "util/FunctionEventFilter.hpp"

#include <memory>
#include <optional>
#include <QTimer>
#include <unordered_map>

namespace chatterino {

struct Emote;
using EmotePtr = std::shared_ptr<const Emote>;

class StreamAllyAPI : public QObject
{
    Q_OBJECT

    QTimer *_fetchTimer = nullptr;

    std::unordered_map<StreamAllyUserId, StreamAllyUser> streamAllyUsers;

    // References stream ally user ID
    std::unordered_map<UserId, StreamAllyUserId> kickUsers;

    void FetchStreamAllyBadges();

    void StartFetchTimer();

public:
    /**
     * Makes a request to StreamAlly API.
     */
    StreamAllyAPI();

    /**
     * Returns the Chatterino badge for the given user
     */
    std::optional<StreamAllyBadge*> getBadge(const UserId &id);
};

}