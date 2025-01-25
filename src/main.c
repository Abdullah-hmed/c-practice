#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <getopt.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

// Function prototypes
void no_args(const char *program_name);
void print_help(const char *program_name);
void print_version();
void handle_unknown(const char *arg);
void handle_directory(const char *path, int new_width, int colored);

int compare(const char *s1, const char *s2);
int args_equal(const char *input, const char *full_arg, const char *short_arg);
void render_media(const char *directory, int new_width, int colored);
void list_directory(const char *path);
int is_directory(const char *path);
int file_exists(const char *path);
int directory_exists(const char *path);
void image_ascii(const char *path, int new_width, int colored);


// Main function
int main(int argc, char *argv[]) {
    
    int new_width = 80;  // Default value for new_width
    char *path = NULL;   // Default path is NULL
    int colored = 0;
    int opt;


    if (argc < 2) {
        no_args(argv[0]);
        return 1;
    }

    while ((opt = getopt(argc, argv, "hvcw:d:")) != -1) {
        switch (opt) {
            case 'h':  // Help flag
                print_help(argv[0]);
                return 0;
            case 'v':  // Version flag
                print_version();
                return 0;
            case 'w':  // Width argument
                new_width = atoi(optarg);  // Set new_width to the passed value
                break;
            case 'd':  // Directory argument
                path = optarg;  // Set the directory path
                break;
            case 'c':  // Colored argument
                colored = 1;
                break;
            default:  // Unknown option
                handle_unknown(argv[optind - 1]);
                return 1;
        }
    }

    if (path != NULL) {
        handle_directory(path, new_width, colored);
    } else {
        no_args(argv[0]);
    }
    return 0;
}

/* -------------------------------------------------------------------------- */
/*                                    utils                                   */
/* -------------------------------------------------------------------------- */
int args_equal(const char *input, const char *arg1, const char *arg2) {
    return compare(input, arg1) || compare(input, arg2);
}

int compare(const char *s1, const char *s2) {
    return strcmp(s1, s2) == 0;
}

int is_directory(const char *path) {
    struct stat sb;
    return stat(path, &sb) == 0 && S_ISDIR(sb.st_mode);
}

int file_exists(const char *path) {
    struct stat buffer;
    return (stat(path, &buffer) == 0);
}

int directory_exists(const char *path) {
    struct stat buffer;
    return (stat(path, &buffer) == 0 && S_ISDIR(buffer.st_mode));
}


void color_pixel(unsigned int r, unsigned int g, unsigned int b) {
    printf("\x1b[38;2;%d;%d;%dm█\033[0m", r, g, b);
}

char map_pixel(int pixel_value) {
    const char ascii_chars[] = " .:-=+*#%@";
    int index = pixel_value / 32 % (sizeof(ascii_chars) - 1);
    printf("%c", ascii_chars[index]);
}

char high_res_color_pixel(int pixel_value) {}


void image_ascii(const char *path, int new_width, int colored) {
    int width, height, channels;
    int new_height;
    char ascii_char;
    unsigned char *image = stbi_load(path, &width, &height, &channels, 0);

    if (image == NULL) {
        printf("Failed to load image: %s\n", path);
        return;
    }

    float aspect_ratio = (float) height / width;
    new_height = (int) (new_width * aspect_ratio * 0.55);

    if (colored) {
        for (int y = 0; y < new_height; ++y) {
            for (int x = 0; x < new_width; ++x) {
                // Colored
                int pixel_index = ((y * height / new_height) * width + (x * width / new_width)) * channels;
                

                unsigned char r = image[pixel_index + 0]; // Red
                unsigned char g = channels > 1 ? image[pixel_index + 1] : r; // Green
                unsigned char b = channels > 2 ? image[pixel_index + 2] : r; // Blue

                color_pixel(r, g, b);
            }
            printf("\n");
        }
    } else {
        for (int y = 0; y < new_height; ++y) {
            for (int x = 0; x < new_width; ++x) {
                // ASCII
                int pixel_index = (y * width / new_height) * width + (x * width / new_width);
                int pixel_value = image[pixel_index * channels]; // Assuming grayscale or RGB
                
                map_pixel(pixel_value);
            }
            printf("\n");
        }
    }
    stbi_image_free(image);
}

/* -------------------------------------------------------------------------- */
/*                          Function implementations                          */
/* -------------------------------------------------------------------------- */
void no_args(const char *program_name) {
    printf("No arguments provided.\n");
    printf("Use '%s --help' for usage information.\n", program_name);
}

void print_help(const char *program_name) {
    printf("Usage: %s [options]\n", program_name);
    printf("Options:\n");
    printf("  --help       Show this help message\n");
    printf("  --version    Show version information\n");
}

void print_version() {
    printf("Version 1.0\n");
}

void handle_unknown(const char *arg) {
    printf("Unknown argument: %s\n", arg);
    printf("Use '--help' for usage information.\n");
}

void handle_directory(const char *path, int new_width, int colored) {
    if(is_directory(path) && directory_exists(path)) {
        list_directory(path);
    } else if (!is_directory(path) && file_exists(path)) {
        render_media(path, new_width, colored);
    } else {
        printf("Invalid path: %s\n", path);
    }
}

void render_media(const char *directory, int new_width, int colored) {
    printf("Rendering media from directory: %s\n", directory);
    image_ascii(directory, new_width, colored);
}

void list_directory(const char *path) {
    struct dirent *entry;
    DIR *dir = opendir(path);

    if (dir == NULL) {
        perror("Invalid directory");
        return;
    }

    printf("Contents of directory: %s\n", path);
    while ((entry = readdir(dir)) != NULL) {
        printf("\x1b[1;37m%s\x1b[0m\n", entry->d_name);
    }

    closedir(dir);
}