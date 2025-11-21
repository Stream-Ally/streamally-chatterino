//
// Created by Petr Pavlík on 19.11.2025.
//

#include "StreamAllyAPI.h"

#include "common/network/NetworkRequest.hpp"
#include "common/network/NetworkResult.hpp"
#include "StreamAllyBadge.h"
#include "messages/Emote.hpp"
#include "messages/Image.hpp"

#include <QUrl>

namespace  chatterino {

void StreamAllyAPI::FetchStreamAllyBadges()
{
    static QUrl url("https://streamally-production-f5e33d0e6f8f.herokuapp.com/api/public/badge");

    // 18, 36, 54, 72
    NetworkRequest(url)
        .concurrent()
        .onSuccess([this] (NetworkResult result) {
            auto jsonRoot = result.parseJson();

            auto jsonBadges = jsonRoot.value("data").toArray();

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



                // Load badge's owners
                std::vector<StreamAllyUser> owners;
                auto jsonOwnersObj = jsonBadgeObj.value("owners").toArray();
                for (const auto &jsonOwner : jsonOwnersObj)
                {
                    auto jsonOwnerObj = jsonOwner.toObject();

                    auto saUser = StreamAllyUser {
                        .streamAllyId = jsonOwnerObj["streamAllyId"].toString(),
                        .twitchId = UserId {jsonOwnerObj["twitchId"].toString()}
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
        })
    .execute();
}

StreamAllyAPI::StreamAllyAPI()
{
    FetchStreamAllyBadges();
}

std::optional<StreamAllyBadge*> StreamAllyAPI::getBadge(const UserId &id)
{
    if (!usersWithBadge.contains(id)) return std::nullopt;

    return &badges.at(usersWithBadge[id]);
}

}  // namespace chatterino
