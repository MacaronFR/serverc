#include <merge.h>

void merge(){
    char **files = get_dir_file("./xml");
    char *path;
    int i = 0;
    xmlDocPtr doc = xmlNewDoc(BAD_CAST"1.1");
    xmlNodePtr root, deposit;
    root = xmlNewNode(NULL, BAD_CAST"root");
    xmlDocSetRootElement(doc, root);
    while(files[i] != NULL){
        path = malloc(strlen(files[i]) + strlen("./xml/") + 1);
        strcpy(path, "./xml/");
        strcat(path, files[i]);
        deposit = newDeposit(files[i]);
        xmlAddChild(deposit, retrieveDocRoot(path));
        xmlAddChild(root, deposit);
        free(path);
        ++i;
    }
    xmlSaveFileEnc("-", doc, "UTF-8");
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