#include "pch.h"

#include "app_core/app_core_gfx.h"

std::unique_ptr<AppCoreGfx> AppCoreGfx::create(GfxApi api) {
    switch (api) {
        case GfxApi::D3D12: {
            return AppCoreGfx::create_d3d12();
        } break;
        case GfxApi::Vulkan: {
            return AppCoreGfx::create_vulkan();
        } break;
        default: {
            assert(false);
            return nullptr;
        } break;
    }
}