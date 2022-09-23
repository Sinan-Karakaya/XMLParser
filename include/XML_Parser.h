#pragma once

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

typedef struct t_XMLAttribute XMLAttribute;
typedef struct t_XMLAttributeList XMLAttributeList;
typedef struct t_XMLNode XMLNode;
typedef struct t_XMLNodeList XMLNodeList;
typedef struct t_XMLDocument XMLDocument;

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

struct t_XMLDocument {
    XMLNode *root;
    const char *version;
    const char *encoding;
};

enum TagType {
    TAG_START,
    TAG_INLINE,
};

bool XMLDocument_load(XMLDocument *doc, const char *path);
void XMLDocument_free(XMLDocument *doc);
bool XMLDocument_write(XMLDocument *doc, const char *path, int indent);

bool ends_with(const char *str, const char *to_find);

XMLNode *XMLNode_new(XMLNode *parent);
void XMLNode_free(XMLNode *node);
XMLNode *XMLNode_getChild(XMLNode *node, const size_t index);
const char *XMLNode_getAttributeValue(XMLNode *node, const char *key);

TagType XMLAttribute_parse(const char *source, int *i, char *lex, int *lexi, XMLNode *currentNode);
void XMLAttribute_free(XMLAttribute *attr);

bool XMLNode_lexicalAnalysis(XMLDocument *doc, const char *source);
XMLNode *XMLNode_getAt(XMLNodeList *list, const int index);
XMLNodeList *XMLNode_getChildrenByTag(XMLNode *parent, const char *tag);
XMLAttribute *XMLNode_getAttribute(XMLNode *node, char *key);

void XMLAttributeList_init(XMLAttributeList *list);
void XMLAttributeList_add(XMLAttributeList *list, XMLAttribute *attr);

void XMLNodeList_init(XMLNodeList *list);
void XMLNodeList_add(XMLNodeList *list, XMLNode *attr);
void XMLNodeList_free(XMLNodeList *list);
