#include "shell.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        /*Interactive mode*/
        run_interactive_mode();
    } else if (argc == 2) {
        /* Non-interactive mode*/
        run_non_interactive_mode(argv[1]);
    } else {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
