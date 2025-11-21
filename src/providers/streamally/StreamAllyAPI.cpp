//
// Created by Petr Pavlík on 19.11.2025.
//

#include "StreamAllyAPI.h"

#include "common/network/NetworkRequest.hpp"

#include <QUrl>

namespace  chatterino {

void StreamAllyAPI::FetchStreamAllyBadges()
{
    static QUrl url("null");

    NetworkRequest(url)
        .concurrent()
        .onSuccess([this](auto result) {
            auto jsonRoot = result.parseJson();

            std::unique_lock lock(this->mutex_);

            int index = 0;
            for (const auto &jsonBadgeValue :
                 jsonRoot.value("badges").toArray())
            {
                auto jsonBadge = jsonBadgeValue.toObject();
                // The sizes for the images are only an estimation, there might
                // be badges with different sizes.
                constexpr QSize baseSize(18, 18);
                auto emote = Emote{
                    .name = EmoteName{},
                    .images =
                        ImageSet{
                            Image::fromUrl(
                                Url{jsonBadge.value("image1").toString()}, 1.0,
                                baseSize),
                            Image::fromUrl(
                                Url{jsonBadge.value("image2").toString()}, 0.5,
                                baseSize * 2),
                            Image::fromUrl(
                                Url{jsonBadge.value("image3").toString()}, 0.25,
                                baseSize * 4),
                        },
                    .tooltip = Tooltip{jsonBadge.value("tooltip").toString()},
                    .homePage = Url{},
                };

                emotes.push_back(
                    std::make_shared<const Emote>(std::move(emote)));

                for (const auto &user : jsonBadge.value("users").toArray())
                {
                    badgeMap[user.toString()] = index;
                }
                ++index;
            }
        })
        .execute();
}
StreamAllyAPI::StreamAllyAPI()
{
    FetchStreamAllyBadges();
}

}  // namespace chatterino
