#include "pch.h"

#include "app_core/app_core.h"

void app_core_test_rtm(void) {
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