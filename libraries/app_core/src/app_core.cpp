#include "app_core/app_core.h"

#include <bar/bar.h>

#include <json/nlohmann/json.hpp>
using JSON = nlohmann::json;

//#define SOL_NO_EXCEPTIONS 1
//#define SOL_ALL_SAFETIES_ON 1
//#define SOL_PRINT_ERRORS 1
#include <sol/sol.hpp>

static constexpr int RESOLUTION_SCALE_FACTOR = 2;
static constexpr auto WINDOW_WIDTH = int(1920 / RESOLUTION_SCALE_FACTOR);
static constexpr auto WINDOW_HEIGHT = int(1080 / RESOLUTION_SCALE_FACTOR);

static void s_my_lua_panic(sol::optional<String> maybe_msg) {
    std::cerr << "Lua is in a panic state and will now abort() the application" << std::endl;
    if (maybe_msg) {
        const auto &msg = maybe_msg.value();
        std::cerr << "\terror message: " << msg << std::endl;
    }
    // When this function exits, Lua will exhibit default behavior and abort()
}

static void s_test_rtm() {
    PRINT_FUNCTION_NAME();

    {
        vector4f vec1 = vector_set(1.0f, 2.0f, 3.0f, 0.0f);
        vector4f vec2 = vector_set(4.0f, 5.0f, 6.0f, 0.0f);

        vector4f result = vector_add(vec1, vec2);
        float dot_product = vector_dot(vec1, vec2);
        float length = vector_length(vec1);

        float x = vector_get_x(result);
        float y = vector_get_y(result);
        float z = vector_get_z(result);
    }

    {
        matrix4x4f mat1 = matrix_identity();
        matrix4x4f mat2 = matrix_set(
            vector_set(1.0f, 2.0f, 3.0f, 4.0f),
            vector_set(5.0f, 6.0f, 7.0f, 8.0f),
            vector_set(9.0f, 10.0f, 11.0f, 12.0f),
            vector_set(13.0f, 14.0f, 15.0f, 16.0f)
        );

        matrix4x4f result_mul = matrix_mul(mat1, mat2);
        matrix4x4f transposed = matrix_transpose(mat2);
    }

    {
        vector4f xyzw0 = vector_set(1.0f, 2.0f, 3.0f, 20.0f);
        vector4f xyzw1 = vector_set(4.0f, 5.0f, 6.0f, 21.0f);
        vector4f xyzw2 = vector_set(7.0f, 8.0f, 9.0f, 22.0f);
        vector4f xyzw3 = vector_set(10.0f, 11.0f, 12.0f, 23.0f);

        vector4f xxxx;
        vector4f yyyy;
        vector4f zzzz;
        vector4f wwww;
        RTM_MATRIXF_TRANSPOSE_4X4(xyzw0, xyzw1, xyzw2, xyzw3, xxxx, yyyy, zzzz, wwww);
    }

    {
        quatf quat1 = quat_from_euler(scalar_deg_to_rad(45.0f), scalar_deg_to_rad(30.0f), scalar_deg_to_rad(60.0f));
        quatf normalized_quat = quat_normalize(quat1);

        quatf quat2 = quat_from_euler(scalar_deg_to_rad(90.0f), scalar_deg_to_rad(0.0f), scalar_deg_to_rad(0.0f));
        quatf result_mul = quat_mul(quat1, quat2);
        quatf interpolated = quat_lerp(quat1, quat2, 0.5f);
    }

    {
        qvf character_transform;
        character_transform.rotation = quat_from_euler(0.0f, scalar_deg_to_rad(90.0f), 0.0f);
        character_transform.translation = vector_set(1.0f, 2.0f, 3.0f);
    }

    {
        qvsf particle_transform;
        particle_transform.rotation = quat_from_euler(0.0f, scalar_deg_to_rad(45.0f), 0.0f);
        particle_transform.translation_scale = vector_set(1.0f, 2.0f, 3.0f, 0.5f);
    }

    {
        qvvf bone_transform;
        bone_transform.rotation = quat_from_euler(0.0f, scalar_deg_to_rad(30.0f), 0.0f);
        bone_transform.translation = vector_set(1.0f, 2.0f, 3.0f);
        bone_transform.scale = vector_set(1.0f, 2.0f, 0.5f);
    }
}

static void s_test_xmath() {
    PRINT_FUNCTION_NAME();

#if !defined(__APPLE__)
    const auto lam_print_xmvector = [](const char *tag, XMVECTOR value) {
        float x = XMVectorGetX(value), y = XMVectorGetY(value), z = XMVectorGetZ(value), w = XMVectorGetW(value);
        std::cout << tag << ": (" << x << ", " << y << ", " << z << ", " << w << ")" << std::endl;
    };
    
    {
        XMFLOAT3 v_tmp(1.0f, 2.0f, 3.0f);
        
        XMVECTOR v1 = XMLoadFloat3(&v_tmp);
        XMVECTOR v2 = XMVectorSet(4.0f, 5.0f, 6.0f, 0.0f);

        XMVECTOR v_add = XMVectorAdd(v1, v2);
        XMVECTOR v_dot = XMVector3Dot(v1, v2);
        XMVECTOR v_cross = XMVector3Cross(v1, v2);

        XMVECTOR v1_length = XMVector3Length(v1);
        XMVECTOR v1_normalized = XMVector3Normalize(v1);
        lam_print_xmvector("v1", v1);
        lam_print_xmvector("v1_normalized", v1_normalized);
        lam_print_xmvector("v2", v2);
        lam_print_xmvector("v_dot", v_dot);
        lam_print_xmvector("v_cross", v_cross);

        XMFLOAT3 v_result;
        XMStoreFloat3(&v_result, v_add);
    }

    {
        XMMATRIX mat_identity = XMMatrixIdentity();
        XMMATRIX mat_translation = XMMatrixTranslation(10.0f, 20.0f, 30.0f);
        XMMATRIX mat_rotation = XMMatrixRotationY(XMConvertToRadians(45.0f));
        XMMATRIX mat_scaling = XMMatrixScaling(2.0f, 2.0f, 2.0f);

        XMMATRIX mat_transform = (mat_scaling * mat_rotation * mat_translation);
        XMMATRIX mat_inverse = XMMatrixInverse(nullptr, mat_transform);

        XMVECTOR scale, rotation_quat, translation;
        XMMatrixDecompose(&scale, &rotation_quat, &translation, mat_transform);

        XMVECTOR point = XMVectorSet(1.0f, 2.0f, 3.0f, 1.0f);
        XMVECTOR transformed_point = XMVector3TransformCoord(point, mat_transform);

        XMVECTOR normal = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
        XMVECTOR transformed_normal = XMVector3TransformNormal(normal, mat_transform);
    }

    {
        XMVECTOR quat1 = XMQuaternionRotationAxis(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), XMConvertToRadians(45.0f));
        XMVECTOR quat2 = XMQuaternionRotationAxis(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), XMConvertToRadians(30.0f));
        XMVECTOR quat_result = XMQuaternionMultiply(quat1, quat2);
        XMVECTOR quat_slerp = XMQuaternionSlerp(quat1, quat2, 0.5f);
        XMMATRIX mat_rotation = XMMatrixRotationQuaternion(quat1);
    }

    {
        BoundingBox box(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f));
        BoundingSphere sphere(XMFLOAT3(1.5f, 0.0f, 0.0f), 1.0f);
        XMVECTOR plane = XMVectorSet(0.0f, 1.0f, 0.0f, 5.0f);
        
        bool intersection1 = box.Intersects(sphere);
        PlaneIntersectionType intersection2 = sphere.Intersects(plane);
    }
#endif
}

static void s_test_bar() {
    Bar<int> bar;
    bar.print(100);

    Bar<float> bar2;
    bar2.print(101.0f);

#if 0
    Bar<double> bar3; // LNK2019
    bar3.print(201.0);
#endif
}

static void s_test_foo() {
    foo_print(10.0);
    foo_printi(20);
    foo_printi64(30000123456789);

    Foo foo;
    foo.print(400);
}

static void s_test_json() {
    JSON j;
    j["foo"] = 0.12345;
    j["bar"] = true;
    j["name"] = "John";
    j["baz"] = nullptr;
    j["buzz"]["fizz"] = 30;
    j["tasks"] = { 100, 0, 150 };
    j["fruit"] = { {"name", "apple"}, {"price", 25.99} };

    std::cout << "j = " << j.dump(4) << "\n" << std::endl;
}

static void s_test_lua() {
    sol::state lua_state/*(sol::c_call<decltype(&s_my_lua_panic), s_my_lua_panic>)*/;
    lua_state.open_libraries(/*sol::lib::ffi, sol::lib::jit*/);

    {
        lua_state.new_usertype<GameObject>(
            "GameObject", sol::constructors<GameObject(int)>(),
            "get_id", &GameObject::get_id,
            "get_name", &GameObject::get_name,
            "set_name", &GameObject::set_name
        );
    }

    auto result = lua_state.script("print('1, <LUA>: hello')");
    result = lua_state.do_file("assets/scripts/main.lua");
    if (result.valid()) {
        sol::function hi_func = lua_state["hi"];

        auto go = GameObject::create();
        go->set_name("John");

        hi_func(go);
        lua_state["hi2"](go);
    }
    result = lua_state.script(R"(print('4, <LUA>: bye\n'))");
}

static void s_test_gfx() {
    {
        auto app_core_gfx = AppCoreGfx::create(GfxApi::D3D12);
        app_core_gfx->test();
    }

    {
        auto app_core_gfx = AppCoreGfx::create(GfxApi::Vulkan);
        app_core_gfx->test();
    }
}

static int s_test_app_core() {
    auto app_core = AppCore::create();
    app_core->preload();
    
    int ret = 0;
    if ((ret = app_core->init(WINDOW_WIDTH, WINDOW_HEIGHT, false)) != 0) {
        return ret;
    }
    ret = app_core->run();
    return ret;
}

int app_core_startup() {
    PRINT_FUNCTION_NAME();

    s_test_rtm();
    s_test_xmath();

    s_test_bar();
    s_test_foo();

    s_test_json();
    s_test_lua();
    s_test_gfx();
    return s_test_app_core();
}

std::unique_ptr<AppCore> AppCore::create() {
    #if TARGET_PLATFORM_ANDROID
    return AppCore::create_android();
    #elif TARGET_PLATFORM_PC
    return AppCore::create_pc();
    #elif TARGET_PLATFORM_UWP
    return AppCore::create_uwp();
    #elif TARGET_PLATFORM_WEB
    return AppCore::create_web();
    #else
    return nullptr;
    #endif
}

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