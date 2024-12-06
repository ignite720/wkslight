#include "app_core.h"

#if TARGET_PLATFORM_PC

struct AppCorePC final : public AppCore {
    virtual int init(int width, int height) override {
        PRINT_FUNCTION_NAME();
        return 0;
    }

    virtual int run() override {
        PRINT_FUNCTION_NAME();
        return 0;
    }
};

std::unique_ptr<AppCore> AppCore::create_pc() {
    return std::make_unique<AppCorePC>();
}

#endif