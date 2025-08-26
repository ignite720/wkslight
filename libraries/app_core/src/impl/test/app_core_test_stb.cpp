#include "pch.h"

#include "app_core/app_core.h"

#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

#define __TEST_PNG_PATH "logs/test.png"
#define __TEST_PNG_WIDTH 4
#define __TEST_PNG_HEIGHT 3
#define __TEST_PNG_COMP 3
#define __TEST_PNG_STRIDE_IN_BYTES (__TEST_PNG_WIDTH * __TEST_PNG_COMP)

void app_core_test_stb(void) {
    PRINT_FUNCTION_NAME();
    
    unsigned char pixels[__TEST_PNG_WIDTH * __TEST_PNG_HEIGHT * __TEST_PNG_COMP] = {0};

    const int y = 1;
    for (int x = 1; x <= 2; ++x) {
        int index = (y * __TEST_PNG_STRIDE_IN_BYTES + x * __TEST_PNG_COMP);
        for (int z = 0; z < __TEST_PNG_COMP; ++z) {
            pixels[index + z] = 0xff;
        }
    }
    if (stbi_write_png(__TEST_PNG_PATH, __TEST_PNG_WIDTH, __TEST_PNG_HEIGHT, __TEST_PNG_COMP, pixels, __TEST_PNG_STRIDE_IN_BYTES) == 0) {
        assert(!"Failed to write the PNG file");
    }

    int w, h, channels;
    stbi_uc *data = stbi_load(__TEST_PNG_PATH, &w, &h, &channels, 0);
    if (data) {
        assert(memcmp(pixels, data, sizeof(pixels)) == 0);

        stbi_image_free(data);
    } else {
        assert(!"Failed to read the PNG file");
    }
}