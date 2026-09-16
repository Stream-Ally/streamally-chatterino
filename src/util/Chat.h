//
// Created by Petr Pavlík on 30.08.2026.
//

#pragma once
#include "common/Channel.hpp"

#include <QString>

namespace chatterino {
enum class Platform : uint8_t;
}

struct Chat
{
    QString channelName;
    chatterino::Platform platform;
    chatterino::ChannelPtr channel;
};