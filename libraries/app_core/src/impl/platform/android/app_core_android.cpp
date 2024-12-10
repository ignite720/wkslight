#include "app_core.h"

#if TARGET_PLATFORM_ANDROID

struct AppCoreAndroid final : public AppCore {
    virtual int init(int width, int height) override {
        PRINT_FUNCTION_NAME();
        return 0;
    }

    virtual int run() override {
        PRINT_FUNCTION_NAME();
        return 0;
    }
};

std::unique_ptr<AppCore> AppCore::create_android() {
    return std::make_unique<AppCoreAndroid>();
}

#endif