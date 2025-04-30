#include "app_core/app_core_gfx.h"

class AppCoreGfxVulkan : public AppCoreGfx {
public:
    virtual void test() const override {
        PRINT_FUNCTION_NAME();
    }
};

std::unique_ptr<AppCoreGfx> AppCoreGfx::create_vulkan() {
    return std::make_unique<AppCoreGfxVulkan>();
}