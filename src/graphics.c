#include <png.h>
#include <stdlib.h>
#include <stdio.h>

#include "ymir/graphics.h"


void read_png(const char *filename, pixel_t ***out_image, int *out_height, int *out_width) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) abort();

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) abort();

    png_infop info = png_create_info_struct(png);
    if (!info) abort();

    if (setjmp(png_jmpbuf(png))) abort();

    png_init_io(png, fp);
    png_read_info(png, info);

    int width = png_get_image_width(png, info);
    int height = png_get_image_height(png, info);
    png_byte color_type = png_get_color_type(png, info);

    if (color_type != PNG_COLOR_TYPE_RGB) {
        fprintf(stderr, "Only RGB images are supported\n");
        abort();
    }

    *out_width = width;
    *out_height = height;

    // Allocate memory for the output image
    pixel_t **image = (pixel_t **)malloc(height * sizeof(pixel_t *));
    for (int y = 0; y < height; y++) {
        image[y] = (pixel_t *)malloc(width * sizeof(pixel_t));
    }

    // Read the PNG into the image array
    for (int y = 0; y < height; y++) {
        png_read_row(png, (png_bytep)image[y], NULL);
    }

    fclose(fp);

    if (png && info) {
        png_destroy_read_struct(&png, &info, NULL);
    }

    *out_image = image;
}


void write_png(const char *filename, pixel_t **image, int height, int width) {
    FILE *fp = fopen(filename, "wb");
    if(!fp) abort();

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) abort();

    png_infop info = png_create_info_struct(png);
    if (!info) abort();

    if (setjmp(png_jmpbuf(png))) abort();

    png_init_io(png, fp);

    png_set_IHDR(
        png,
        info,
        width, height,
        8,
        PNG_COLOR_TYPE_RGB,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );
    png_write_info(png, info);

    for (int y = 0; y < height; y++) {
        png_write_row(png, (png_bytep)image[y]);
    }

    png_write_end(png, NULL);

    fclose(fp);

    if (png && info)
        png_destroy_write_struct(&png, &info);
}


pixel_t **alloc_image(int height, int width) {
    pixel_t **image = (pixel_t **)malloc(height * sizeof(pixel_t *));
    for (int y = 0; y < height; y++) {
        image[y] = (pixel_t *)malloc(width * sizeof(pixel_t));
    }
    return image;
}
