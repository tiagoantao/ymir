#include <stdio.h>
#include <stdlib.h>

#include <check.h>

#include "ymir/fs.h"
#include "ymir/graphics.h"

START_TEST(test_write_png) {
    int width = 100;
    int height = 100;

    pixel_t **image = malloc(height * sizeof(pixel_t *));
    for (int y = 0; y < height; y++) {
        image[y] = malloc(width * sizeof(pixel_t));
        for (int x = 0; x < width; x++) {
            // Fill the image with a red gradient
            image[y][x].r = (uint8_t)((255 * y) / height);
            image[y][x].g = 0;
            image[y][x].b = 0;
        }
    }

    write_png("test_image.png", image, height, width);

    for (int y = 0; y < height; y++) {
        free(image[y]);
    }
    free(image);

    ck_assert(file_exists("test_image.png"));
    ck_assert(get_file_size("test_image.png") > 0);
}
END_TEST


START_TEST(test_read_png){
    pixel_t **image = NULL;
    int height = 0;
    int width = 0;

    read_png("../tests/rt.png", &image, &height, &width);

    // Assertions to check if the function succeeded
    ck_assert(image != NULL);
    ck_assert(height == 1000);
    ck_assert(width == 2000);

    // Add more checks here if necessary, for example, inspecting some pixel values

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
    tcase_add_test(tc_png, test_read_png);
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
