#include <stdio.h>
#include <stdlib.h>

#include <check.h>

#include "graphics.h"

START_TEST(test_write_png) {
   int width = 100;
    int height = 100;

    // Allocate memory for the test image
    pixel_t **image = malloc(height * sizeof(pixel_t *));
    for (int y = 0; y < height; y++) {
        image[y] = malloc(width * sizeof(pixel_t));
        for (int x = 0; x < width; x++) {
            // Fill the image with a simple pattern, e.g., red gradient
            image[y][x].r = (uint8_t)((255 * y) / height);
            image[y][x].g = 0;
            image[y][x].b = 0;
        }
    }

    // Call the function to write the image to a PNG file
    write_png("test_image.png", image, height, width);

    // Free the allocated memory
    for (int y = 0; y < height; y++) {
        free(image[y]);
    }
    free(image);
}
END_TEST


Suite *graphics_suite(void) {
    Suite *s;
    TCase *tc_png;
    s = suite_create("Graphics");
    tc_png = tcase_create("PNG");
    tcase_add_test(tc_png, test_write_png);
    suite_add_tcase(s, tc_png);
    return s;
}


int main(void){
    int number_failed;
    Suite *s;
    SRunner *sr;
    s = graphics_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
