#pragma once

#include <foo/foo.h>

#include "app_core/app_core_api.h"

enum class GfxApi {
    Unknown = 0,
    D3D12,
    Vulkan,
    Count
};

class APP_CORE_API AppCoreGfx {
public:
    static std::unique_ptr<AppCoreGfx> create(GfxApi api);
    
private:
    static std::unique_ptr<AppCoreGfx> create_d3d12();
    static std::unique_ptr<AppCoreGfx> create_vulkan();

public:
    virtual ~AppCoreGfx() = default;

    virtual void test() const = 0;
};