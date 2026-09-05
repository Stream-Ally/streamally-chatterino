<img src="./StreamAlly.png" alt="drawing" width="80" style="padding-right: 1em"/> StreamAlly's Chatterino
============

StreamAlly's Chatterino is a fork of Chatterino 7. This fork contains support for StreamAlly integration.

<img height="500" alt="image" src="https://github.com/user-attachments/assets/97fbf7ee-edc0-4b3e-8c55-890cfcf93259" />

### StreamAlly's Chatterino features

- StreamAlly badges
- Improved Kick support - added subscription gifter badges along with correct subscriber badges
- Colored tabs by platform
- Platform's icon next to streamer's name
- Recommended default settings and hotkeys

### Downloads

Builds are available in the [Releases](https://github.com/Stream-Ally/streamally-chatterino/releases/latest) section.

### Issues

If you find any issues regarding the StreamAlly integration, please report them in the [Issues](https://github.com/Stream-Ally/streamally-chatterino/issues) section.

### Discord

Join StreamAlly's Discord server: https://discord.gg/5zsbAEdGfB

## Original Chatterino 7 Readme

### Features of Chatterino7

- 7TV Name Paints

- 7TV Personal Emotes

- 7TV Animated Profile Avatars

- 4x Images (7TV and FFZ)

### Screenshots

![Example of Personal Emotes](https://user-images.githubusercontent.com/27637025/227032811-837c56eb-7724-431b-b00e-b944c9289dff.png)
![Example of Paints](https://user-images.githubusercontent.com/27637025/227034147-cb1fcd76-dbae-4878-9551-96ffa64dd1a9.png)

### Downloads

**Stable builds** can be downloaded from the [releases section](https://github.com/SevenTV/chatterino7/releases/latest).

To test new features, you can download the **nighly build** [here](https://github.com/SevenTV/chatterino7/releases/tag/nightly-build).

Windows users can install Chatterino7 [from Chocolatey](https://chocolatey.org/packages/chatterino7).

### Issues

If you have issues such as crashes or weird behaviour regarding 7TV features, report them [in the issue-section](https://github.com/SevenTV/chatterino7/issues). If you have issues with other features, please report them [in the upstream issue-section](https://github.com/Chatterino/chatterino2/issues).

### Discord

If you don't have a GitHub account and want to report issues or want to join the community you can join the official 7TV Discord using the link here: <https://discord.com/invite/7tv>.

### AVIF Support

When building Chatterino 7, you might not have access to a static build of `libavif`. In that case, you can define `CHATTERINO_NO_AVIF_PLUGIN` in CMake. If you have `qavif.so` from [kimageformats](https://invent.kde.org/frameworks/kimageformats) installed on your system, Chatterino will pick it up and use AVIF images.

## Original Chatterino 2 Readme

Chatterino 2 is a chat client for [Twitch.tv](https://twitch.tv).
The Chatterino 2 wiki can be found [here](https://wiki.chatterino.com).
Contribution guidelines can be found [here](https://wiki.chatterino.com/Contributing%20for%20Developers).

## Download

Current releases are available at [https://chatterino.com](https://chatterino.com).
Windows users can also install Chatterino [from Chocolatey](https://chocolatey.org/packages/chatterino).

## Nightly build

You can download the latest Chatterino 2 build over [here](https://github.com/Chatterino/chatterino2/releases/tag/nightly-build)

You might also need to install the [VC++ Redistributables](https://aka.ms/vs/17/release/vc_redist.x64.exe) from Microsoft if you do not have it installed already.  
If you still receive an error about `MSVCR120.dll missing`, then you should install the [VC++ 2013 Restributable](https://download.microsoft.com/download/2/E/6/2E61CFA4-993B-4DD4-91DA-3737CD5CD6E3/vcredist_x64.exe).

## Building

To get source code with required submodules run:

```shell
git clone --recurse-submodules https://github.com/Chatterino/chatterino2.git
```

or

```shell
git clone https://github.com/Chatterino/chatterino2.git
cd chatterino2
git submodule update --init --recursive
```

- [Building on Windows](../master/BUILDING_ON_WINDOWS.md)
- [Building on Windows with vcpkg](../master/BUILDING_ON_WINDOWS_WITH_VCPKG.md)
- [Building on Linux](../master/BUILDING_ON_LINUX.md)
- [Building on macOS](../master/BUILDING_ON_MAC.md)
- [Building on FreeBSD](../master/BUILDING_ON_FREEBSD.md)

## Git blame

This project has big commits in the history which touch most files while only doing stylistic changes. To improve the output of git-blame, consider setting:

```shell
git config blame.ignoreRevsFile .git-blame-ignore-revs
```

This will ignore all revisions mentioned in the [`.git-blame-ignore-revs`
file](./.git-blame-ignore-revs). GitHub does this by default.

## Code style

The code is formatted using [clang-format](https://clang.llvm.org/docs/ClangFormat.html). Our configuration is found in the [.clang-format](.clang-format) file in the repository root directory.

For more contribution guidelines, take a look at [the wiki](https://wiki.chatterino.com/Contributing%20for%20Developers/).

## Doxygen

Doxygen is used to generate project information daily and is available [here](https://doxygen.chatterino.com).
