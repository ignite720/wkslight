#include "app_core.h"

struct AppCoreGfxD3D12 final : public AppCoreGfx {
    virtual void test() const override {
        PRINT_FUNCTION_NAME();
    }
};

std::unique_ptr<AppCoreGfx> AppCoreGfx::create_d3d12() {
    return std::make_unique<AppCoreGfxD3D12>();
}