#include <stdint.h>

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} pixel_t;

void read_png(const char *filename, pixel_t ***out_image, int *out_height, int *out_width);
void write_png(const char *filename, pixel_t **image, int height, int width);

pixel_t **alloc_image(int height, int width);
void free_image(pixel_t **image, int height);
