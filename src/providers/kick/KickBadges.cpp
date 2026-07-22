#include "providers/kick/KickBadges.hpp"

#include "debug/AssertInGuiThread.hpp"

#include <magic_enum/magic_enum.hpp>

namespace {

using namespace chatterino;
using namespace Qt::Literals;

enum class BadgeID : uint8_t {
    bot,
    broadcaster,
    founder,
    moderator,
    og,
    sidekick,
    staff,
    sub_gifter,
    subscriber,
    trainwreckstv,
    verified,
    vip
};

struct BadgeNameData {
    QString friendlyName;
    QStringView pathSegment;
    MessageElementFlag flag{};
};

BadgeNameData nameDataFor(BadgeID id)
{
    switch (id)
    {
        case BadgeID::bot:
            return {
                .friendlyName = u"Bot"_s,
                .pathSegment = u"bot",
                .flag = MessageElementFlag::BadgeVanity,
            };
        case BadgeID::broadcaster:
            return {
                .friendlyName = u"Broadcaster"_s,
                .pathSegment = u"broadcaster",
                .flag = MessageElementFlag::BadgeChannelAuthority,
            };
        case BadgeID::founder:
            return {.friendlyName = u"Founder"_s,
                    .pathSegment = u"founder",
                    .flag = MessageElementFlag::BadgeSubscription};
        case BadgeID::moderator:
            return {
                .friendlyName = u"Moderator"_s,
                .pathSegment = u"moderator",
                .flag = MessageElementFlag::BadgeChannelAuthority,
            };
        case BadgeID::og:
            return {
                .friendlyName = u"OG"_s,
                .pathSegment = u"og",
                .flag = MessageElementFlag::BadgeVanity,
            };
        case BadgeID::sidekick:
            return {
                .friendlyName = u"Sidekick"_s,
                .pathSegment = u"sidekick",
                .flag = MessageElementFlag::BadgeVanity,
            };
        case BadgeID::staff:
            return {
                .friendlyName = u"Staff"_s,
                .pathSegment = u"staff",
                .flag = MessageElementFlag::BadgeGlobalAuthority,
            };
        case BadgeID::sub_gifter:
            return {
                .friendlyName = u"Sub Gifter"_s,
                .pathSegment = u"sub_gifter",
                .flag = MessageElementFlag::BadgeVanity,
            };
        case BadgeID::subscriber:
            return {
                .friendlyName = u"Subscriber"_s,
                .pathSegment = u"subscriber",
                .flag = MessageElementFlag::BadgeSubscription,
            };
        case BadgeID::trainwreckstv:
            return {
                .friendlyName = u"TrainwrecksTV"_s,
                .pathSegment = u"trainwreckstv",
                .flag = MessageElementFlag::BadgeVanity,
            };
        case BadgeID::verified:
            return {
                .friendlyName = u"Verified"_s,
                .pathSegment = u"verified",
                .flag = MessageElementFlag::BadgeVanity,
            };
        case BadgeID::vip:
            return {
                .friendlyName = u"VIP"_s,
                .pathSegment = u"vip",
                .flag = MessageElementFlag::BadgeChannelAuthority,
            };
    }
    return {};
}

using CacheData = std::pair<EmotePtr, MessageElementFlag>;

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
std::array<CacheData, magic_enum::enum_count<BadgeID>()> CACHE{};

}  // namespace

namespace chatterino {

std::pair<EmotePtr, MessageElementFlag> KickBadges::lookup(
    std::string_view name)
{
    assertInGuiThread();

    auto id = magic_enum::enum_cast<BadgeID>(name);
    if (!id)
    {
        return {nullptr, {}};
    }

    auto idx = static_cast<uint8_t>(*id);
    if (idx >= CACHE.size())
    {
        assert(false);
        return {nullptr, {}};
    }

    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index) -- see above
    auto &entry = CACHE[idx];
    if (!entry.first)
    {
        auto data = nameDataFor(*id);

        entry.first = std::make_shared<const Emote>(Emote{
            .name = {data.friendlyName},
            .images =
                ImageSet{
                    Image::fromUrl(
                        {u":/kick/badges/" % data.pathSegment % u"-18.webp"},
                        1.0, {18, 18}),
                    Image::fromUrl(
                        {u":/kick/badges/" % data.pathSegment % u"-36.webp"},
                        .5, {36, 36}),
                },
            .tooltip = Tooltip{data.friendlyName},
        });
        entry.second = data.flag;
    }

    return entry;
}

ImageSet KickBadges::getSubGifterBadgeByGiftCount(int count)
{
    static const std::array<std::pair<int, QString>, 28> tiers = {{
        {5000, QStringLiteral(":/kick/badges/gifter-5000.svg")},
        {4000, QStringLiteral(":/kick/badges/gifter-4000.svg")},
        {3000, QStringLiteral(":/kick/badges/gifter-3000.svg")},
        {2000, QStringLiteral(":/kick/badges/gifter-2000.svg")},
        {1000, QStringLiteral(":/kick/badges/gifter-1000.svg")},
        {950,  QStringLiteral(":/kick/badges/gifter-0950.svg")},
        {900,  QStringLiteral(":/kick/badges/gifter-0900.svg")},
        {850,  QStringLiteral(":/kick/badges/gifter-0850.svg")},
        {800,  QStringLiteral(":/kick/badges/gifter-0800.svg")},
        {750,  QStringLiteral(":/kick/badges/gifter-0750.svg")},
        {700,  QStringLiteral(":/kick/badges/gifter-0700.svg")},
        {650,  QStringLiteral(":/kick/badges/gifter-0650.svg")},
        {600,  QStringLiteral(":/kick/badges/gifter-0600.svg")},
        {550,  QStringLiteral(":/kick/badges/gifter-0550.svg")},
        {500,  QStringLiteral(":/kick/badges/gifter-0500.svg")},
        {450,  QStringLiteral(":/kick/badges/gifter-0450.svg")},
        {400,  QStringLiteral(":/kick/badges/gifter-0400.svg")},
        {350,  QStringLiteral(":/kick/badges/gifter-0350.svg")},
        {300,  QStringLiteral(":/kick/badges/gifter-0300.svg")},
        {250,  QStringLiteral(":/kick/badges/gifter-0250.svg")},
        {200,  QStringLiteral(":/kick/badges/gifter-0200.svg")},
        {150,  QStringLiteral(":/kick/badges/gifter-0150.svg")},
        {100,  QStringLiteral(":/kick/badges/gifter-0100.svg")},
        {50,   QStringLiteral(":/kick/badges/gifter-0050.svg")},
        {25,   QStringLiteral(":/kick/badges/gifter-0025.svg")},
        {10,   QStringLiteral(":/kick/badges/gifter-0010.svg")},
        {5,    QStringLiteral(":/kick/badges/gifter-0005.svg")},
        {1,    QStringLiteral(":/kick/badges/gifter-0001.svg")},
    }};

    QString file = QStringLiteral(":/kick/badges/gifter-0001.svg");  // fallback
    for (const auto &[min, path] : tiers)
    {
        if (count >= min)
        {
            file = path;
            break;
        }
    }

    return ImageSet{Image::fromUrl({file}, 0.6, {36, 36})};
}
}  // namespace chatterino
