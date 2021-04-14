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

char **get_credentials(char *section){
    FILE *f = fopen("/etc/hyperion/xml_saver.conf", "rb");
    char **credentials = NULL;
    int line = 0;
    if(f == NULL){
        exit(1);
    }
    char buf[256];
    do{
        if(!fgets(buf, 255, f))
            break;
        buf[strlen(buf) - 1] = buf[strlen(buf) - 1] == '\n' ? 0 : buf[strlen(buf) - 1];
    }while(strcmp(buf, section) != 0);
    do{
        if(!fgets(buf, 255, f))
            break;
        buf[strlen(buf) - 1] = buf[strlen(buf) - 1] == '\n' ? 0 : buf[strlen(buf) - 1];
        line++;
        credentials = realloc(credentials, sizeof(char *) * line);
        credentials[line-1] = malloc(strlen(buf) + 1);
        strcpy(credentials[line-1], buf);
    }while(buf[0] != 0);
    free(credentials[line-1]);
    credentials[line-1] = NULL;
    return credentials;
}