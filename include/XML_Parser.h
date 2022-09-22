#pragma once

typedef struct t_XMLNode {
    char *tag;
    char *content;
    struct t_XMLNode *parent;
} XMLNode;

typedef struct t_XMLDocument {
    XMLNode *root;
} XMLDocument;

bool XMLDocument_load(XMLDocument *doc, const char *path);
void XMLDocument_free(XMLDocument *doc);

XMLNode *XMLNode_new(XMLNode *parent);
void XMLNode_free(XMLNode *node);

bool XMLNode_lexicalAnalysis(XMLDocument *doc, const char *source);
