#include "app_core/app_core.h"

class AppCoreAndroid : public AppCore {
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

std::unique_ptr<AppCore> AppCore::create_android() {
    return std::make_unique<AppCoreAndroid>();
}