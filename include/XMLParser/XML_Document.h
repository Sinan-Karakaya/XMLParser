#pragma once

#include "core.h"

/**
 * @brief This structure represents a XML document, it holds
 * an imaginary root (useful for declaration nodes) and some basic infos.
 * 
 */
typedef struct t_XMLDocument XMLDocument;

#ifndef __GNUC__
#pragma region Typedefs
#endif

typedef struct t_XMLNode XMLNode;

#ifndef __GNUC__
#pragma endregion
#endif

struct t_XMLDocument {
    XMLNode *root;
    const char *version;
    const char *encoding;
};

/**
 * @brief Load an XML document, returns false if loading failed.
 * 
 * @param doc The structure which will hold the content of the file.
 * @param path Path to the file to be loaded.
 * @return true if succesfully loaded
 * @return false if couldn't load file
 */
bool XMLDocument_load(XMLDocument *doc, const char *path);

/**
 * @brief Free the structure to prevent memory leaks
 * 
 * @param doc Structure to free.
 */
void XMLDocument_free(XMLDocument *doc);

/**
 * @brief Write to a file the state of the XMLDocument. Useful for debugging.
 * 
 * @param doc Structure which holds the data to print.
 * @param path Path to write to.
 * @param indent Number of spaces for indentation
 * @return true if written to path successfully
 * @return false if we couldn't write to a file
 */
bool XMLDocument_write(XMLDocument *doc, const char *path, unsigned int indent);
