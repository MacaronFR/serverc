#ifndef SERVERC_MERGE_H
#define SERVERC_MERGE_H

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <utils.h>

void merge();
xmlNodePtr newDeposit(char *file);
xmlNodePtr retrieveDocRoot(char *file);

#endif //SERVERC_MERGE_H
