#include "pch.h"

#include "app_core/app_core.h"

#if 0
class AppCoreAndroid : public AppCore {
public:
    virtual int init(const char *title, int width, int height, bool fullscreen, bool linear_filter, int auto_close_secs) override {
        PRINT_FUNCTION_NAME();

        do {
            if (AppCore::init(title, width, height, fullscreen, linear_filter, auto_close_secs) != 0) {
                break;
            }
    
            return 0;
        } while(false);
        return -1;
    }
};

std::unique_ptr<AppCore> AppCore::create_android() {
    return std::make_unique<AppCoreAndroid>();
}
#endif