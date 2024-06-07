#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// Function declarations
int dir_exists(const char *path);
void create_dir(const char *path);

char folder_name[256];

void get_current_folder_name(char *buffer, size_t size) {
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        char *last_slash = strrchr(cwd, '/');
        if (last_slash != NULL) {
            strncpy(buffer, last_slash + 1, size - 1);
        } else {
            strncpy(buffer, cwd, size - 1);
            buffer[size - 1] = '\0'; 
        }
    } else {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }
}

void run_project(void) { // add parameters
    
    system("clear");
    printf("\033[44m ➜ Testing:  Running tests \033[0m\n");
    char command[512];
    strcpy(command, "./build/");
    strcat(command, folder_name);
    system(command);
}

void build_project(const char *project_path) {
    char command[8192];  // Increase buffer size
    char build_path[512];  
    char src_path[512];  

    get_current_folder_name(folder_name, sizeof(folder_name));

    snprintf(build_path, sizeof(build_path), "%s/build", project_path);
    snprintf(src_path, sizeof(src_path), "%s/src", project_path);

    if (!dir_exists(project_path)) {
        fprintf(stderr, "Error: Project directory '%s' does not exist.\n", project_path);
        exit(EXIT_FAILURE);
    }

    if (!dir_exists(build_path)) {
        create_dir(build_path);
    }

    struct dirent *entry;
    DIR *dp = opendir(src_path);
    struct stat file_stats;

    if (dp == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    // Compile .c files to .o files
    while ((entry = readdir(dp))) {
        char file_path[2048];  
        char obj_file[2048]; 

        snprintf(file_path, sizeof(file_path), "%s/%s", src_path, entry->d_name);

        if (stat(file_path, &file_stats) == 0 && S_ISREG(file_stats.st_mode) && strstr(entry->d_name, ".c")) {
            snprintf(obj_file, sizeof(obj_file), "%s/%.*s.o", build_path, (int)(strlen(entry->d_name) - 2), entry->d_name);
            snprintf(command, sizeof(command), "gcc -Wall -Wextra -std=c99 -c %s -o %s", file_path, obj_file);
            printf("\033[42m ✔ Compiling: %s \033[0m\n", entry->d_name); 
            system(command);
        }
    }

    closedir(dp);

    // Link .o files to create the executable
    snprintf(command, sizeof(command), "gcc -Wall -Wextra -std=c99 %s/*.o -o %s/%s", build_path, build_path, folder_name);
    system(command);

    printf("\033[42m ✔ Build complete: Executable created at %s/%s \033[0m\n", build_path, folder_name);
}
