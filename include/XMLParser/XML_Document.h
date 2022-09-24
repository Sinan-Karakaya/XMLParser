#pragma once

#include "core.h"

typedef struct t_XMLDocument XMLDocument;
typedef struct t_XMLNode XMLNode;
typedef struct t_XMLNodeList XMLNodeList;
typedef struct t_XMLAttribute XMLAttribute;
typedef struct t_XMLAttributeList XMLAttributeList;

struct t_XMLDocument {
    XMLNode *root;
    const char *version;
    const char *encoding;
};

bool XMLDocument_load(XMLDocument *doc, const char *path);
void XMLDocument_free(XMLDocument *doc);
bool XMLDocument_write(XMLDocument *doc, const char *path, int indent);
