#ifndef SERVERC_UTILS_H
#define SERVERC_UTILS_H

#include <dirent.h>
#include <stdlib.h>
#include <string.h>

char **get_dir_file(char *path);
void free_result(char **to_free);
char **get_credentials(char *section);

#endif //SERVERC_UTILS_H