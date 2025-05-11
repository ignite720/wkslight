#include "pch.h"

#include "app_core/app_core.h"

void app_core_test_xmath(void) {
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