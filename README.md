# wkslight
### What's this
> `wkslight` is the abbreviation of `workspace light`, a `lightweight` `project generation utility` based on [premake5](https://premake.github.io/).

![GitHub repo size](https://img.shields.io/github/repo-size/ignite720/wkslight?style=for-the-badge)
![GitHub last commit](https://img.shields.io/github/last-commit/ignite720/wkslight?style=for-the-badge)
---
<br />

#### CI
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/ignite720/wkslight/ci_pc.yml?style=for-the-badge&label=Linux%20macOS%20Windows)

![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/ignite720/wkslight/ci_android.yml?style=for-the-badge&label=Android)
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
<br />

#### Clean(***optional***)
> Double click `premake5-clean.bat`

> ```shell
> source premake5-clean.sh 
> ```

### 1. Linux
> 1.1 build
> ```shell
> source premake5-generate-linux.sh 
> source gmake-pc.sh 
> ```

> 1.2 run
> ```shell
> source tool-run-pc.sh 
> source cargo-run-pc.sh 
> ```

> 1.3 test(***optional***)
> ```shell
> ./tool-py-test.py
> ```
<br />

### 2. macOS
> ```shell
> source premake5-generate-macos.sh 
> source gmake-pc.sh 
> ```
<br />

### 3. Windows
> Double click `premake5-generate-windows.bat`
<br />

### 4. Android
> 4.1 install The Android SDK

> 4.2 gradle => `bin/apk-debug/app.apk`
> ```shell
> source premake5-generate-android.sh 
> source android-build.sh 
> ```

> 4.3 cargo-apk => `bin/android-cargo-apk/app.apk`
>
> Note that folder `544xd5c4` may change, so pass it in as an argument.
> ```shell
> rustup target add aarch64-linux-android
> cargo install cargo-apk
> RUSTFLAGS="-L ../build/app/app/.cxx/Debug/544xd5c4/arm64-v8a" source cargo-apk.sh
> ```
<br />

### 5. Windows UWP
> Double click `premake5-generate-windows-uwp.bat`
<br />

### 6. Web
> ```shell
> source premake5-generate-web.sh 
> source tool-run-web.sh 
> ```
<br />