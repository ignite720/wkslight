#include "pch.h"

#include "app_core/app_core.h"

#if !(TARGET_PLATFORM_ANDROID || TARGET_PLATFORM_WEB)
PRAGMA_WARNING_PUSH
PRAGMA_WARNING_IGNORE_CLANG("-Woverflow")
PRAGMA_WARNING_IGNORE_GCC("-Woverflow")
PRAGMA_WARNING_IGNORE_MSVC(4616)
#include <FastNoise/FastNoise.h>
PRAGMA_WARNING_POP
#endif

#include <FastNoiseLite/FastNoiseLite.h>

void app_core_test_noise(void) {
    PRINT_FUNCTION_NAME();

    {
        FastNoiseLite noise;
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

        std::vector<float> noiseData(128 * 128);

        int index = 0;
        for (int y = 0; y < 128; y++) {
            for (int x = 0; x < 128; x++) {
                noiseData[index++] = noise.GetNoise(static_cast<float>(x), static_cast<float>(y));
            }
        }
    }

    {
        #if !(TARGET_PLATFORM_ANDROID || TARGET_PLATFORM_WEB)
        auto simplex = FastNoise::New<FastNoise::Simplex>();
        auto fractal = FastNoise::New<FastNoise::FractalFBm>();

        fractal->SetSource(simplex);
        fractal->SetOctaveCount(5);

        std::vector<float> noise(16 * 16);
        fractal->GenUniformGrid2D(noise.data(), 0, 0, 16, 16, 0.02f, 1337);

        int index = 0;
        for (int y = 0; y < 16; y++) {
            for (int x = 0; x < 16; x++) {
                std::cout << "x " << x << "\ty " << y << "\t: " << noise[index++] << std::endl;
            }
        }
        #endif
    }
}