# wkslight
### What's this
> `wkslight` is the abbreviation of `workspace light`, <br />
a lightweight `project generation utility` based on [premake5](https://premake.github.io/).

![GitHub repo size](https://img.shields.io/github/repo-size/ignite720/wkslight?style=for-the-badge)
![GitHub last commit](https://img.shields.io/github/last-commit/ignite720/wkslight?style=for-the-badge)
---
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/ignite720/wkslight/ci_android.yml?style=for-the-badge&label=Android)

![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/ignite720/wkslight/ci_pc.yml?style=for-the-badge&label=PC&nbsp;&nbsp;(Linux,%20macOS,%20Windows))

![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/ignite720/wkslight/ci_uwp.yml?style=for-the-badge&label=UWP)

![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/ignite720/wkslight/ci_web.yml?style=for-the-badge&label=Web)
---
<br />

## Demo
[<img alt="github" src="https://img.shields.io/badge/github-ignite720/wkslight?style=for-the-badge&color=505050&labelColor=b0f0f0&label=wkslight%20demo" height="30" />](https://ignite720.github.io/wkslight/)
---
<br />

## Examples
- <https://github.com/ignite720/Engine/tree/premake5>
- <https://github.com/wkslight/JoltPhysics-Samples>
---
<br />

## How to build
#### Prerequisites
> [Download premake](https://premake.github.io/), extract it to a folder and add it to the system PATH.

> ```shell
> mkdir -p ~/work/work2 && cd ~/work/work2
> git clone --recursive https://github.com/ignite720/wkslight.git
> ```

#### Clean
> ```shell
> make clean
> ```

> Double click `scripts\premake5-clean.bat`
---
<br />

### 1. Android
> 1.1 Install the `Android SDK`

> 1.2 `gradle`
> ```shell
> make android
> ```
> => bin/apk-debug/app.apk

> 1.3 `cargo-apk`
> ```shell
> make cargo-apk
> ```
> => bin/android-cargo-apk/app.apk

### 2. PC
#### 2.1 Linux & macOS
> ```shell
> # gmake
> make pc
> make run
> make test
>
> # ninja
> make ninja
>
> # cargo
> make cargo_run
> ```

#### 2.2 Windows
> Double click `scripts\premake5-generate-pc-vs.bat`

### 3. Windows UWP
> Double click `scripts\premake5-generate-uwp.bat`

### 4. Web
> ```shell
> make web
> ```
---
<br />

## Assets
#### Font
- [Press Start 2P](https://fonts.google.com/specimen/Press+Start+2P)
#### Sound
- [Insert Coin](https://opengameart.org/content/insert-coin)
- [Item Shop](https://opengameart.org/content/item-shop)