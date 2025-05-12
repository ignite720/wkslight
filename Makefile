UNAME := $(shell uname)
ifeq ($(UNAME),Linux)
	SHELL := /bin/bash
else ifeq ($(UNAME),Darwin)
	SHELL := /usr/local/bin/bash
endif

.PHONY: all clean install test rebuild deps

all: pc

android: clean
	ANDROID_NDK_ROOT=$ANDROID_NDK_LATEST_HOME
	source scripts/premake5-generate-android.sh
	source scripts/android-buildw.sh

pc:
	source scripts/premake5-generate-pc-gmake.sh $(ARGV)
	source scripts/gmake-pc.sh

ninja: clean
	source scripts/premake5-generate-pc-ninja.sh $(ARGV)
	source scripts/ninja-build.sh

cmake: clean
	source scripts/premake5-generate-pc-cmake.sh $(ARGV)
	source scripts/cmake-build.sh

xcode: clean
	source scripts/premake5-generate-pc-xcode.sh $(ARGV)
	source scripts/xcode-build.sh
	
web: clean
	source scripts/premake5-generate-web.sh
	source scripts/gmake-web.sh
	source scripts/tool-web-post-build.sh

run: pc
	source scripts/tool-run-pc.sh $(ARGV)

run_macos: xcode
	source scripts/tool-run-pc-macos.sh $(ARGV)

clean:
	source scripts/premake5-clean.sh

install:
	@echo install

install_deps:
	source scripts/tool-install-deps.sh

test:
	source scripts/test-py.sh

rebuild:
	@echo rebuild

deps:
	@echo deps
	
tree:
	source scripts/tool-tree.sh

cargo_run: pc
	source scripts/cargo-run-pc.sh $(ARGV)

cargo-apk: android
	source scripts/cargo-apk.sh