//
// Created by Petr Pavlík on 19.11.2025.
//

#include "StreamAllyAPI.h"

#include "Application.hpp"
#include "common/network/NetworkRequest.hpp"
#include "common/network/NetworkResult.hpp"
#include "messages/Emote.hpp"
#include "messages/Image.hpp"
#include "singletons/WindowManager.hpp"
#include "StreamAllyAPIConfidential.h"
#include "StreamAllyBadge.h"
#include "StreamAllyEnv.h"
#include "widgets/Window.hpp"

#include <QUrl>

#include <vector>

namespace  chatterino {

void StreamAllyAPI::FetchStreamAllyBadges()
{
    // 18, 36, 54, 72
    NetworkRequest(STREAMALLY_API_BADGE_URL)
        .concurrent()
        .onSuccess([this] (NetworkResult result) {
            // Clear current data
            _streamAllyUsers.clear();
            _kickUsers.clear();

            // Root
            auto jsonRoot = result.parseJson();

            // Load subjects (users)
            auto jsonSubjects = jsonRoot.value("subjects").toArray();

            for (const auto &jsonSubject : jsonSubjects)
            {
                auto jsonSubjectObj = jsonSubject.toObject();
                auto jsonIdentities = jsonSubjectObj["identities"].toArray();
                auto subjectId = jsonSubjectObj["id"].toString();

                std::unordered_map<QString, StreamAllyIdentity> identities;

                for (const auto &jsonIdentity : jsonIdentities)
                {
                    auto jsonIdentityObj = jsonIdentity.toObject();

                    auto identity = StreamAllyIdentity {
                        .platform = jsonIdentityObj["platform"].toString(),
                        .login = jsonIdentityObj["login"].toString(),
                        .displayName = jsonIdentityObj["displayName"].toString(),
                        .providerUserId = {jsonIdentityObj["providerUserId"].toString()},
                    };

                    if (identity.platform == "kick")
                    {
                        _kickUsers[{identity.providerUserId}] = {subjectId};
                    }
                    else if (identity.platform == "twitch")
                    {
                        _twitchUsers[{identity.providerUserId}] = {subjectId};
                    }

                    identities[jsonIdentityObj["platform"].toString()] = std::move(identity);
                }

                auto saUser = StreamAllyUser {
                    .streamAllyId = subjectId,
                    .identities = std::move(identities),
                };

                _streamAllyUsers[{saUser.streamAllyId}] = std::move(saUser);
            }

            auto jsonGrants = jsonRoot["grants"].toArray();

            for (const auto &jsonGrant : jsonGrants)
            {
                auto jsonGrantObj = jsonGrant.toObject();

                _streamAllyUsers[{jsonGrantObj["subjectId"].toString()}].ownedBadges.emplace(jsonGrantObj["badgeDefinitionId"].toString());
            }

            auto jsonBadges = jsonRoot["badgeDefinitions"].toArray();
            constexpr QSize baseImgSize(18, 18);

            for (const auto &jsonBadge : jsonBadges)
            {
                auto jsonBadgeObj = jsonBadge.toObject();
                auto jsonImagesObj = jsonBadgeObj["assets"].toObject();

                auto emote = Emote{
                    .name = EmoteName{jsonBadgeObj["name"].toString()},
                    .images = ImageSet {
                        Image::fromUrl(
                            Url{jsonImagesObj["18"].toString()}, 1.0, baseImgSize),
                        Image::fromUrl(
                            Url{jsonImagesObj["36"].toString()}, 0.5, baseImgSize * 2),
                        Image::fromUrl(
                            Url{jsonImagesObj["72"].toString()}, 0.25, baseImgSize * 4)
                    },
                    .tooltip = Tooltip{jsonBadgeObj["description"].toString()},
                    .homePage = Url{}
                };

                auto jsonEnvObj = jsonBadgeObj["environment"].toObject();

                auto saEnv = StreamAllyEnv {
                    .id = jsonEnvObj["id"].toString(),
                    .slug = jsonEnvObj["slug"].toString()
                };

                auto saBadge = StreamAllyBadge {
                    .id = jsonBadgeObj["id"].toString(),
                    .emote = std::make_shared<const Emote>(emote),
                    .env = std::move(saEnv)
                };

                _badges[saBadge.id] = std::move(saBadge);
            }

            QString test;

            /*

            auto jsonBadges = jsonRoot.value("badgeDefinitions").toArray();

            constexpr QSize baseImgSize(18, 18);

            // Load badges
            for (const auto &jsonBadge : jsonBadges)
            {
                auto jsonBadgeObj = jsonBadge.toObject();
                auto jsonImagesObj = jsonBadgeObj.value("source").toObject();

                // Load badge's emote data
                auto emote = Emote{
                    .name = EmoteName{jsonBadgeObj["name"].toString()},
                    .images = ImageSet {
                        Image::fromUrl(
                            Url{jsonImagesObj.value("18").toString()}, 1.0, baseImgSize),
                        Image::fromUrl(
                            Url{jsonImagesObj.value("36").toString()}, 0.5, baseImgSize * 2),
                        Image::fromUrl(
                            Url{jsonImagesObj.value("72").toString()}, 0.25, baseImgSize * 4)
                    },
                    .tooltip = Tooltip{jsonBadgeObj["description"].toString()},
                    .homePage = Url{}
                };
                auto jsonSubjectsObj = json

                // Load badge's owners
                std::vector<StreamAllyUser> owners;
                auto jsonOwnersObj = jsonBadgeObj.value("owners").toArray();
                for (const auto &jsonOwner : jsonOwnersObj)
                {
                    auto jsonOwnerObj = jsonOwner.toObject();

                    auto saUser = StreamAllyUser {
                        .streamAllyId = jsonOwnerObj["streamAllyId"].toString(),
                        .providerUserId = UserId {jsonOwnerObj["twitchId"].toString()}
                    };

                    owners.push_back(std::move(saUser));
                }

                auto saBadge = StreamAllyBadge {
                    .emote = std::make_shared<const Emote>(std::move(emote)),
                    .owners = std::move(owners)
                };

                // Add the new badge to badges
                badges.push_back(std::move(saBadge));

                // Add data to the usersWithBadge map for faster access
                for (const auto &jsonOwner : jsonOwnersObj)
                {
                    auto jsonOwnerObj = jsonOwner.toObject();

                    usersWithBadge[UserId{jsonOwnerObj["twitchId"].toString()}] = badges.size() - 1;
                }
            }
            */
        })
    .execute();
}

void StreamAllyAPI::StartFetchTimer()
{
    // 3. Initialize the timer
    _fetchTimer = new QTimer(this);

    // 4. Connect the timeout signal to your slot
    connect(_fetchTimer, &QTimer::timeout, this, &StreamAllyAPI::FetchStreamAllyBadges);

    // 5. Start the timer (e.g., every 1000ms = 1 second)
    _fetchTimer->start(1000 * 60 * 15); // 1000 * 60 (minute) * 15 (15 minutes)
}

StreamAllyAPI::StreamAllyAPI()
{
    FetchStreamAllyBadges();

    StartFetchTimer();
}

std::vector<StreamAllyBadge*> StreamAllyAPI::getBadges(const MessagePlatform platform, const UserId &id, const QString &environment)
{
    std::vector<StreamAllyBadge*> badges;

    StreamAllyUser *saUser;

    saUser = &_streamAllyUsers[platform == MessagePlatform::Kick ? _kickUsers[id] : _twitchUsers[id]];

    for (const auto &badge : saUser->ownedBadges)
    {
        auto saBadge = &_badges[badge];

        if (saBadge->env.slug == environment || saBadge->env.slug == "streamally")
        {
            badges.push_back(saBadge);
        }
    }

    return badges;
}

}  // namespace chatterino
