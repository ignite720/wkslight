#include "app_core.h"

class AppCoreGfxD3D12 : public AppCoreGfx {
public:
    virtual void test() const override {
        PRINT_FUNCTION_NAME();
    }
};

std::unique_ptr<AppCoreGfx> AppCoreGfx::create_d3d12() {
    return std::make_unique<AppCoreGfxD3D12>();
}