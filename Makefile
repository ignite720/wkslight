UNAME := $(shell uname)
ifeq ($(UNAME),Linux)
	SHELL := /bin/bash
else ifeq ($(UNAME),Darwin)
	SHELL := /usr/local/bin/bash
endif

.PHONY: all clean install test rebuild deps

all: pc

pc:
	source scripts/premake5-generate-pc-gmake.sh
	source scripts/gmake-pc.sh

ninja: clean
	source scripts/premake5-generate-pc-ninja.sh
	source scripts/ninja-build.sh

xcode_run: clean
	source scripts/premake5-generate-pc-xcode.sh
	source scripts/xcode-build.sh
	source scripts/tool-run-pc-macos.sh $(argv)

android: clean
	ANDROID_NDK_ROOT=$ANDROID_NDK_LATEST_HOME
	source scripts/premake5-generate-android.sh
	source scripts/android-buildw.sh

web: clean
	source scripts/premake5-generate-web.sh
	source scripts/gmake-web.sh
	source scripts/tool-web-post-build.sh

run: pc
	source scripts/tool-run-pc.sh $(argv)

clean:
	source scripts/premake5-clean.sh

install:
	@echo install

test:
	source scripts/test-py.sh

rebuild:
	@echo rebuild

deps:
	@echo deps
	
tree:
	source scripts/tool-tree.sh

cargo_run: pc
	source scripts/cargo-run-pc.sh $(argv)