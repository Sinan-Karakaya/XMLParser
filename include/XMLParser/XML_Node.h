#pragma once

#include "core.h"

typedef struct t_XMLDocument XMLDocument;
typedef struct t_XMLNode XMLNode;
typedef struct t_XMLNodeList XMLNodeList;
typedef struct t_XMLAttribute XMLAttribute;
typedef struct t_XMLAttributeList XMLAttributeList;

struct t_XMLNodeList {
    size_t heap_size;
    size_t size;
    XMLNode **data;
};

struct t_XMLNode {
    char *tag;
    char *content;
    XMLNode *parent;
    XMLNodeList children;
    XMLAttributeList attributes;
};

XMLNode *XMLNode_new(XMLNode *parent);
void XMLNode_free(XMLNode *node);
XMLNode *XMLNode_getChild(XMLNode *node, const size_t index);
const char *XMLNode_getAttributeValue(XMLNode *node, const char *key);

bool XMLNode_lexicalAnalysis(XMLDocument *doc, const char *source);
XMLNode *XMLNode_getAt(XMLNodeList *list, const int index);
XMLNodeList *XMLNode_getChildrenByTag(XMLNode *parent, const char *tag);
XMLAttribute *XMLNode_getAttribute(XMLNode *node, char *key);

void XMLNodeList_init(XMLNodeList *list);
void XMLNodeList_add(XMLNodeList *list, XMLNode *attr);
void XMLNodeList_free(XMLNodeList *list);
