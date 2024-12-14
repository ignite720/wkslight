# wkslight
### What's this
> `wkslight` is the abbreviation of `workspace light`, a `lightweight` `project generation utility` based on [premake5](https://premake.github.io/).

![GitHub repo size](https://img.shields.io/github/repo-size/ignite720/wkslight?style=for-the-badge)
![GitHub last commit](https://img.shields.io/github/last-commit/ignite720/wkslight?style=for-the-badge)
---
<br />

#### CI
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/ignite720/wkslight/ci_android.yml?style=for-the-badge&label=Android)

![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/ignite720/wkslight/ci_pc.yml?style=for-the-badge&label=Linux%20macOS%20Windows)

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
> [Download premake](https://premake.github.io/)

> ```shell
> mkdir -p ~/work/work2 && cd ~/work/work2
> git clone --recursive https://github.com/ignite720/wkslight.git
> ```

#### Clean
> Double click `scripts\premake5-clean.bat`

> ```shell
> source scripts/0-premake5-clean.sh 
> ```

### 1. Android
> 1.1 install The `Android SDK`

> 1.2 `gradle`
> ```shell
> source scripts/11-premake5-generate-android.sh 
> source scripts/21-android-build.sh 
> ```
> => bin/apk-debug/app.apk

> 1.3 `cargo-apk`
>
> Note that folder `544xd5c4` may change, so pass it in as an argument.
> ```shell
> rustup target add aarch64-linux-android
> cargo install cargo-apk
> RUSTFLAGS="-L ../build/app/app/.cxx/Debug/544xd5c4/arm64-v8a" source scripts/cargo-apk.sh
> ```
> => bin/android-cargo-apk/app.apk

### 2. PC
#### 2.1 Linux
> 2.1.1 build
> ```shell
> source scripts/12-premake5-generate-pc.sh 
> source scripts/22-gmake-pc.sh 
> ```

> 2.1.2 run
> ```shell
> source scripts/32-tool-run-pc.sh 
> source scripts/cargo-run-pc.sh 
> ```

> 2.1.3 test(***optional***)
> ```shell
> scripts/42-tool-test.py
> ```

#### 2.2 macOS
> ```shell
> source scripts/12-premake5-generate-pc.sh 
> source scripts/22-gmake-pc.sh 
> source scripts/32-tool-run-pc.sh 
> ```

#### 2.3 Windows
> Double click `scripts\premake5-generate-windows.bat`

### 3. Windows UWP
> Double click `scripts\premake5-generate-windows-uwp.bat`

### 4. Web
> ```shell
> source scripts/14-premake5-generate-web.sh 
> source scripts/34-tool-run-web.sh 
> ```