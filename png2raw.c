
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define STBI_NO_THREAD_LOCALS
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// _CRT_SECURE_NO_WARNINGS  // Put this to project settings->C/C++->Preprocessor->Preprocessor Definitions to avoid the warning of unsafe function on fopen

int main(int argc, char** argv)
{
    if (argc < 4 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
    {
        printf("Usage: ./png2raw file.png output.raw rgb|rgba\n");
        return 1;
    }

    const char* input = argv[1];
    const char* output = argv[2];
    int want_channels = 3;

    // Determine desired channels
    if (strcmp(argv[3], "rgba") == 0)
    {
        want_channels = 4;
    }
    else if (strcmp(argv[3], "rgb") == 0)
    {
        want_channels = 3;
    }
    else
    {
        printf("The last argument must be 'rgb' or 'rgba'.\n");
        return 1;
    }

    // Load image data
    int w, h, channels;
    unsigned char* data = stbi_load(input, &w, &h, &channels, want_channels);
    if (!data)
    {
        printf("Failure on loading image %s\n", input);
        printf("Failure reason: %s\n", stbi_failure_reason());
        return 1;
    }

    // Validate dimensions and calculate image size safely.
    if (w <= 0 || h <= 0 ||
        (size_t)w > SIZE_MAX / (size_t)h)
    {
        fprintf(stderr, "Invalid or oversized image dimensions.\n");
        stbi_image_free(data);
        return 1;
    }

    size_t pixel_count = (size_t)w * (size_t)h;

    if (pixel_count > SIZE_MAX / (size_t)want_channels)
    {
        fprintf(stderr, "Image size exceeds the supported limit.\n");
        stbi_image_free(data);
        return 1;
    }

    size_t img_size = pixel_count * (size_t)want_channels;

    // Write to raw file
    FILE* f = fopen(output, "wb");
    if (f == NULL)
    {
        fprintf(stderr, "Failure on creating file %s\n", output);
        stbi_image_free(data);
        return 1;
    }

    // Write image data and check for incomplete writes.
    size_t bytes_written = fwrite(data, 1, img_size, f);
    int write_error = ferror(f);
    int close_result = fclose(f);

    stbi_image_free(data);

    if (bytes_written != img_size || write_error || close_result != 0)
    {
        fprintf(stderr, "Failed to write complete RAW image: %s\n", output);
        return 1;
    }

    printf("Successfully converted: %s -> %s (%dx%d, %s)\n",
           input, output, w, h,
           want_channels == 3 ? "RGB" : "RGBA");

    return 0;
}
