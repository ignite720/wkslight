# wkslight
![GitHub last commit](https://img.shields.io/github/last-commit/ignite720/wkslight?style=for-the-badge)

### CI Status
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/ignite720/wkslight/ci.yml?style=for-the-badge&label=Linux%20macOS%20Windows)

![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/ignite720/wkslight/ci_android.yml?style=for-the-badge&label=Android)

![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/ignite720/wkslight/ci_uwp.yml?style=for-the-badge&label=UWP)

![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/ignite720/wkslight/ci_web.yml?style=for-the-badge&label=Web)

### How to build

```shell
mkdir -p ~/work/work2
cd ~/work/work2/

git clone --recursive https://github.com/ignite720/wkslight.git
```

## 1. Linux
> 1.1 build
```shell
source premake5-generate-linux.sh 
source gmake-pc.sh 
```

> 1.2 run
```shell
source tool-app-run-pc.sh 
```

>> 1.2.2 cargo run
```shell
source cargo-run-pc.sh 
```

> 1.3 clean(***optional***)
```shell
source premake5-clean.sh 
```

> 1.4 test(***optional***)
```shell
./tool-pytest.py
```

## 2. macOS
```shell
source premake5-generate-macos.sh 
source gmake-pc.sh 
```

## 3. Windows
> Double click `premake5-generate-windows.bat`

## 4. Android
```shell
source premake5-generate-android.sh 
source android-build.sh 
```

## 5. Windows UWP
> Double click `premake5-generate-windows-uwp.bat`

## 6. Web
```shell
source premake5-generate-web.sh 
source gmake-web.sh 
```