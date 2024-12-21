#include "app_core.h"

#if TARGET_PLATFORM_PC

class AppCorePC final : public AppCore {
public:
    virtual int init(int width, int height, bool linear_filter) override {
        PRINT_FUNCTION_NAME();
        
        AppCore::init(width, height, linear_filter);
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