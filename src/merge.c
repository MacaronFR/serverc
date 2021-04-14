#include <merge.h>

void merge(){
    char **dir = get_credentials("[XML]");
    char **files = get_dir_file(dir[0]);
    char *path;
    int i = 0;
    char folder[9];
    char file[7];
    struct tm *local;
    char *savePath;
    time_t now;
    time(&now);
    local = localtime(&now);
    sprintf(folder, "year%d", local->tm_year + 1900);
    sprintf(file, "%02d.xml", local->tm_mon);
    savePath = malloc(strlen(dir[1]) + 16);
    strcpy(savePath, dir[1]);
    strcat(savePath, folder);
    strcat(savePath, "/");
    mkdir(savePath, S_IRWXU | S_IRWXG | S_IRWXO);
    strcat(savePath, file);
    xmlDocPtr doc = xmlNewDoc(BAD_CAST"1.1");
    xmlNodePtr root, deposit;
    root = xmlNewNode(NULL, BAD_CAST"deposits");
    xmlDocSetRootElement(doc, root);
    while(files[i] != NULL){
        path = malloc(strlen(files[i]) + strlen(dir[0]) + 1);
        strcpy(path, dir[0]);
        strcat(path, files[i]);
        deposit = newDeposit(files[i]);
        xmlAddChild(deposit, retrieveDocRoot(path));
        xmlAddChild(root, deposit);
        free(path);
        ++i;
    }
    xmlSaveFileEnc(savePath, doc, "UTF-8");
    xmlFreeDoc(doc);
    free_result(files);
    xmlCleanupParser();
    xmlMemoryDump();
}

xmlNodePtr newDeposit(char *file){
    size_t len = strlen(file);
    xmlNodePtr deposit = xmlNewNode(NULL, BAD_CAST"deposit");
    char id[3];
    char *name = malloc(len - (len - 10) + 1);
    strncpy(id, file, 2);
    strncpy(name, file + 2, len - 10);
    id[2] = 0;
    name[len - 10] = 0;
    xmlNewProp(deposit, BAD_CAST"id", BAD_CAST id);
    xmlNewProp(deposit, BAD_CAST"name", BAD_CAST name);
    free(name);
    return deposit;
}

xmlNodePtr retrieveDocRoot(char *file){
    xmlDocPtr doc = xmlReadFile(file, NULL, 0);
    xmlNodePtr root = xmlDocGetRootElement(doc);
    xmlNodePtr result = xmlCopyNode(root, 1);
    xmlFreeDoc(doc);
    return result;
}