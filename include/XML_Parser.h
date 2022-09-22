#pragma once

typedef struct t_XMLAttribute {
    char *key;
    char *value;
} XMLAttribute;

typedef struct t_XMLAttributeList {
    int heap_size;
    int size;
    XMLAttribute *data;
} XMLAttributeList;

typedef struct t_XMLNode {
    char *tag;
    char *content;
    struct t_XMLNode *parent;
    XMLAttributeList attributes;
} XMLNode;

typedef struct t_XMLDocument {
    XMLNode *root;
} XMLDocument;

bool XMLDocument_load(XMLDocument *doc, const char *path);
void XMLDocument_free(XMLDocument *doc);

XMLNode *XMLNode_new(XMLNode *parent);
void XMLNode_free(XMLNode *node);

void XMLAttribute_free(XMLAttribute *attr);

bool XMLNode_lexicalAnalysis(XMLDocument *doc, const char *source);

void XMLAttributesList_init(XMLAttributeList *list);
void XMLAttributesList_add(XMLAttributeList *list, XMLAttribute *attr);