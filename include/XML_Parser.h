#pragma once

typedef struct t_XMLAttribute XMLAttribute;
typedef struct t_XMLAttributeList XMLAttributeList;
typedef struct t_XMLNode XMLNode;
typedef struct t_XMLNodeList XMLNodeList;
typedef struct t_XMLDocument XMLDocument;

struct t_XMLAttribute {
    char *key;
    char *value;
};

struct t_XMLAttributeList {
    int heap_size;
    int size;
    XMLAttribute *data;
};

struct t_XMLNodeList {
    int heap_size;
    int size;
    XMLNode **data;
};

struct t_XMLNode {
    char *tag;
    char *content;
    XMLNode *parent;
    XMLNodeList children;
    XMLAttributeList attributes;
};

struct t_XMLDocument {
    XMLNode *root;
};

bool XMLDocument_load(XMLDocument *doc, const char *path);
void XMLDocument_free(XMLDocument *doc);

XMLNode *XMLNode_new(XMLNode *parent);
void XMLNode_free(XMLNode *node);
XMLNode *XMLNode_getChild(XMLNode *node, const unsigned int index);

void XMLAttribute_free(XMLAttribute *attr);

bool XMLNode_lexicalAnalysis(XMLDocument *doc, const char *source);

void XMLAttributeList_init(XMLAttributeList *list);
void XMLAttributeList_add(XMLAttributeList *list, XMLAttribute *attr);

void XMLNodeList_init(XMLNodeList *list);
void XMLNodeList_add(XMLNodeList *list, XMLNode *attr);