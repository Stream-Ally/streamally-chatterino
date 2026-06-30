//
// Created by Petr Pavlík on 19.11.2025.
//

#pragma once

#include "common/Aliases.hpp"
#include "StreamAllyBadge.h"
#include "StreamAllyUser.h"
#include "util/FunctionEventFilter.hpp"
#include "messages/Message.hpp"
#include "KickSubBadge.h"

#include <memory>
#include <optional>
#include <QTimer>
#include <vector>
#include <unordered_map>

namespace chatterino {

struct Emote;
using EmotePtr = std::shared_ptr<const Emote>;

class StreamAllyAPI : public QObject
{
    Q_OBJECT

    QTimer *_fetchTimer = nullptr;

    // Badge GUID -> StreamAllyBadge
    std::unordered_map<QString, StreamAllyBadge> _badges;

    // StreamAllyUserID -> StreamAllyUser
    std::unordered_map<StreamAllyUserId, StreamAllyUser> _streamAllyUsers;

    // Platform UserID -> StreamAllyUserID
    std::unordered_map<UserId, StreamAllyUserId> _kickUsers;
    std::unordered_map<UserId, StreamAllyUserId> _twitchUsers;

    // --- Kick specific ---

    // Channel slug -> Sub badges
    std::unordered_map<QString, std::vector<KickSubBadge>> _kickStreamerSubBadges;

    void FetchStreamAllyBadges();

    void StartFetchTimer();

    const KickSubBadge* getKickChannelSubBadgeNoFetch(const QString &channel, const int month);

public:
    /**
     * Makes a request to StreamAlly API.
     */
    StreamAllyAPI();

    /**
     * Returns the Chatterino badge for the given user
     */
    std::vector<StreamAllyBadge*> getBadges(MessagePlatform platform, const UserId &id, const QString &environment);

    const KickSubBadge* getKickChannelSubBadge(const QString &channel, int month);
};

}