#include <utils.h>
#include <stdio.h>

char **get_dir_file(char *path){
    DIR *d;
    struct dirent *dir;
    char **files = NULL;
    int n_files = 0;
    d = opendir(path);
    if(d){
        while((dir = readdir(d)) != NULL){
            if(dir->d_type == 8){
                files = realloc(files, sizeof(char *) * (n_files + 1));
                files[n_files] = malloc(strlen(dir->d_name) + 1);
                strcpy(files[n_files], dir->d_name);
                n_files++;
            }
        }
        closedir(d);
    }
    files = realloc(files, sizeof(char *) * (n_files + 1));
    files[n_files] = NULL;
    return files;
}

void free_result(char **to_free){
    int i = 0;
    while(to_free[i] != NULL){
        free(to_free[i]);
        ++i;
    }
    free(to_free);
}