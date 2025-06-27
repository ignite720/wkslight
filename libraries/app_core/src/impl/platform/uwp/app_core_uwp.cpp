#include "pch.h"

#include "app_core/app_core.h"

class AppCoreUWP : public AppCore {
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

    virtual int run() override {
        PRINT_FUNCTION_NAME();

        int ret = 0;
        //ret = AppCore::run();
        return ret;
    }
};

std::unique_ptr<AppCore> AppCore::create_uwp() {
    return std::make_unique<AppCoreUWP>();
}