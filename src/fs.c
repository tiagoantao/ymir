#include <stdbool.h>
#include <sys/stat.h>


bool file_exists(const char *path) {
    struct stat st;
    return stat(path, &st) == 0;
}


int get_file_size(const char *path) {
    struct stat st;
    if (stat(path, &st) == 0) return st.st_size;
    return -1;
}
