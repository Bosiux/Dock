#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void init_project(const char *project_name);
void build_project(const char *project_name);
void run_project(void);

int main(int argc, char *argv[]) {
    if (argc < 2 || (strcmp(argv[1], "init") != 0 && strcmp(argv[1], "build") != 0 && strcmp(argv[1], "test") != 0)) {
        fprintf(stderr, "Usage: %s <init|build|test> [project_name]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *command = argv[1];

    if (strcmp(command, "init") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Usage: %s init <project_name>\n", argv[0]);
            return EXIT_FAILURE;
        }
        const char *project_name = argv[2];
        init_project(project_name);
    } else if (strcmp(command, "build") == 0) {
        char cwd[512];
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("getcwd");
            return EXIT_FAILURE;
        }
        build_project(cwd);
    } else if (strcmp(command, "test") == 0) {
        char cwd[512];
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("getcwd");
            return EXIT_FAILURE;
        }
        build_project(cwd);
        run_project();
    }

    return EXIT_SUCCESS;
}
