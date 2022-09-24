#pragma once

#include "core.h"

typedef struct t_XMLDocument XMLDocument;
typedef struct t_XMLNode XMLNode;
typedef struct t_XMLNodeList XMLNodeList;
typedef struct t_XMLAttribute XMLAttribute;
typedef struct t_XMLAttributeList XMLAttributeList;
typedef enum TagType TagType;

struct t_XMLAttribute {
    char *key;
    char *value;
};

struct t_XMLAttributeList {
    size_t heap_size;
    size_t size;
    XMLAttribute *data;
};

TagType XMLAttribute_parse(const char *source, int *i, char *lex, int *lexi, XMLNode *currentNode);
void XMLAttribute_free(XMLAttribute *attr);

void XMLAttributeList_init(XMLAttributeList *list);
void XMLAttributeList_add(XMLAttributeList *list, XMLAttribute *attr);
