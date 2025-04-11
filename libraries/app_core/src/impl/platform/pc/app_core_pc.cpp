#include "app_core/app_core.h"

class AppCorePC : public AppCore {
public:
    #if 0
    virtual int init(int width, int height, bool linear_filter) override {
        PRINT_FUNCTION_NAME();
        
        AppCore::init(width, height, linear_filter);
        return 0;
    }

    virtual int run() override {
        PRINT_FUNCTION_NAME();
        return 0;
    }
    #endif
};

std::unique_ptr<AppCore> AppCore::create_pc() {
    return std::make_unique<AppCorePC>();
}