#include <stdio.h>
#include <string.h>

// Function prototypes
void no_args(const char *program_name);
void print_help(const char *program_name);
void print_version();
void handle_unknown(const char *arg);

// Main function
int main(int argc, char *argv[]) {
    if (argc < 2) {
        no_args(argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            print_help(argv[0]);
        } else if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0) {
            print_version();
        } else {
            handle_unknown(argv[i]);
        }
    }

    return 0;
}


// Function implementations
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