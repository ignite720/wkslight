#include "app_core.h"

class AppCoreGfxVulkan final : public AppCoreGfx {
public:
    virtual void test() const override {
        PRINT_FUNCTION_NAME();
    }
};

std::unique_ptr<AppCoreGfx> AppCoreGfx::create_vulkan() {
    return std::make_unique<AppCoreGfxVulkan>();
}