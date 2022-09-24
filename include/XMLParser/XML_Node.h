#pragma once

#include "core.h"

/**
 * @brief Structure which represents a node of the XLM file, holds a parent,
 * a list of children, the tag name, a list of its attributes and the content
 * of the tag (the text between the opening and closing tags).
 * 
 */
typedef struct t_XMLNode XMLNode;

/**
 * @brief A list of Nodes, similar to a std::vector in cpp. Easier to handle
 * than a simple array.
 * 
 */
typedef struct t_XMLNodeList XMLNodeList;

#ifndef __GNUC__
#pragma region Typedefs
#endif

typedef struct t_XMLDocument XMLDocument;
typedef struct t_XMLAttribute XMLAttribute;
typedef struct t_XMLAttributeList XMLAttributeList;

#ifndef __GNUC__
#pragma endregion
#endif

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

/**
 * @brief Create a new Node from a parent (can use NULL as a parent for root,
 * not advised to use outside of the lib inside use).
 * 
 * @param parent Parent node (NULLable)
 * @return XMLNode* => pointer to a memory allocated Node.
 */
XMLNode *XMLNode_new(XMLNode *parent);

/**
 * @brief Free a node to prevent memory leaks
 * 
 * @param node Node to free
 */
void XMLNode_free(XMLNode *node);

/**
 * @brief Get a child Node from a Node using its index (starts at 0).
 * 
 * @param node Node to look into
 * @param index Index of the child node
 * @return XMLNode* - Pointer to the child node
 */
XMLNode *XMLNode_getChild(XMLNode *node, const size_t index);

/**
 * @brief Get the attribute value of a Node using the key of the attribute
 * (e.g key="value")
 * 
 * @param node Node to look into
 * @param key Name of the key of the attribute
 * @return const char* - Value of the attribute
 */
const char *XMLNode_getAttributeValue(XMLNode *node, const char *key);

/**
 * @brief Warning: Called by XMLDocument_load /!\
 * Lexical analysis of the document, this is where most of the parsing is done.
 * 
 * @param doc Document loaded with a file
 * @param source Buffer of the xml file
 * @return true if parsed without errors
 * @return false if something went wrong with the parsing. An error will be
 * displayed in the console.
 */
bool XMLNode_lexicalAnalysis(XMLDocument *doc, const char *source);

/**
 * @brief Return a Node from a NodeList using the index.
 * 
 * @param list NodeList to look into
 * @param index Index of the wanted Node
 * @return XMLNode* returns NULL if index was invalid
 */
XMLNode *XMLNode_getAt(XMLNodeList *list, const int index);

/**
 * @brief Returns a list of all the children with a certain tag in a Node.
 * 
 * @param parent Node to look into
 * @param tag Tag to look for
 * @return XMLNodeList* returns NULL if none were found
 */
XMLNodeList *XMLNode_getChildrenByTag(XMLNode *parent, const char *tag);

/**
 * @brief Get the attribute of a Node using a key
 * 
 * @param node Node to look into
 * @param key Key of the attribute to look for
 * @return XMLAttribute* returns NULL if none were found
 */
XMLAttribute *XMLNode_getAttribute(XMLNode *node, const char *key);

/**
 * @brief Memory allocate a NodeList
 * 
 * @param list NodeList to init
 */
void XMLNodeList_init(XMLNodeList *list);

/**
 * @brief Add a node to a NodeList
 * 
 * @param list List to add the node to
 * @param node Node to add to the list 
 */
void XMLNodeList_add(XMLNodeList *list, XMLNode *node);

/**
 * @brief Free a NodeList to prevent memory leaks
 * 
 * @param list List to free
 */
void XMLNodeList_free(XMLNodeList *list);
