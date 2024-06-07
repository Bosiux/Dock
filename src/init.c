#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int dir_exists(const char *path) {
    struct stat stats;
    stat(path, &stats);
    if (S_ISDIR(stats.st_mode)) {
        return 1;
    }
    return 0;
}

void create_dir(const char *path) {
    if (mkdir(path, 0777) != 0) {
        perror("mkdir");
        exit(EXIT_FAILURE);
    }
}

void create_file(const char *path, const char *content) {
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    if (content != NULL) {
        fprintf(file, "%s", content);
    }
    fclose(file);
}

void init_project(const char *project_name) {
    char project_path[256];

    snprintf(project_path, sizeof(project_path), "./%s", project_name);
    if (dir_exists(project_path)) {
        printf("project already initialized\n");
        return;
    }

    // Create the project directory
    create_dir(project_path);

    // Create the build directory
    snprintf(project_path, sizeof(project_path), "./%s/build", project_name);
    create_dir(project_path);

    

    // Create the src directory
    snprintf(project_path, sizeof(project_path), "./%s/src", project_name);
    create_dir(project_path);

    // Create the src/header directory
    snprintf(project_path, sizeof(project_path), "./%s/src/header", project_name);
    create_dir(project_path);

    // Create the src/header/main.h file
    snprintf(project_path, sizeof(project_path), "./%s/src/header/main.h", project_name);
    create_file(project_path, 
            "#ifndef MAIN_H\n"
            "#define MAIN_H\n\n"
            "#endif  // MAIN_H\n");

    // Create the src/main.c file
    snprintf(project_path, sizeof(project_path), "./%s/src/main.c", project_name);
    create_file(project_path, 
            "#include <stdio.h>\n"
            "#include \"header/main.h\"\n\n"
            "int main() {\n"
            "   printf(\"Hello Dock!\\n\");\n"
            "    return 0;\n"
            "}\n"
    );
}
