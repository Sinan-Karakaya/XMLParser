#pragma once

#include "core.h"

/**
 * @brief Struct that holds the attribute of a Node.
 * 
 */
typedef struct t_XMLAttribute XMLAttribute;

/**
 * @brief List that holds attributes. This is similar to std::vector, it makes
 * it easier to use rather than using standard arrays.
 * 
 */
typedef struct t_XMLAttributeList XMLAttributeList;

#ifndef __GNUC__
#pragma region Typedefs
#endif

typedef struct t_XMLNode XMLNode;
typedef enum TagType TagType;

#ifndef __GNUC__
#pragma endregion
#endif

struct t_XMLAttribute {
    char *key;
    char *value;
};

struct t_XMLAttributeList {
    size_t heap_size;
    size_t size;
    XMLAttribute *data;
};

/**
 * @brief Parse attributes of a node. This is used internally for writing
 * out the result, and isn't suited for external use.
 * 
 * @param source 
 * @param i 
 * @param lex 
 * @param lexi 
 * @param currentNode 
 * @return TagType Used to identify if the tag is self-closed. 
 */
TagType XMLAttribute_parse(const char *source, int *i, char *lex, int *lexi, XMLNode *currentNode);

/**
 * @brief Free an atribute to prevent memory leaks.
 * 
 * @param attr Attribute to free
 */
void XMLAttribute_free(XMLAttribute *attr);

/**
 * @brief Initialise a list of Attributes.
 * 
 * @param list List to initialise
 * @return true if allocation was successfull
 * @return false if allocation failed
 */
bool XMLAttributeList_init(XMLAttributeList *list);

/**
 * @brief Add an attribute to a list
 * 
 * @param list List to add the attribute
 * @param attr Attribute to add the list to
 */
void XMLAttributeList_add(XMLAttributeList *list, XMLAttribute *attr);
