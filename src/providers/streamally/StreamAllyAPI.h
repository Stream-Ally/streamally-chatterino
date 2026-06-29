//
// Created by Petr Pavlík on 19.11.2025.
//

#pragma once

#include "common/Aliases.hpp"
#include "StreamAllyBadge.h"
#include "StreamAllyUser.h"
#include "util/FunctionEventFilter.hpp"
#include "messages/Message.hpp"

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

    std::unordered_map<QString, StreamAllyBadge> _streamAllyBadges;

    std::unordered_map<StreamAllyUserId, StreamAllyUser> _streamAllyUsers;

    // References stream ally user ID
    std::unordered_map<UserId, StreamAllyUserId> _kickUsers;
    std::unordered_map<UserId, StreamAllyUserId> _twitchUsers;

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
    std::vector<StreamAllyBadge*> getBadges(const MessagePlatform platform, const UserId &id);
};

}