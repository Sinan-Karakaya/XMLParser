#include "core.h"

bool XMLDocument_load(XMLDocument *doc, const char *path)
{
    FILE *file = fopen(path, "r");
    int size = -1;

    if (!file) {
        fprintf(stderr, "Error: Could not open file '%s'.\n", path);
        return false;
    }
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer = calloc(sizeof(char), (size + 1));
    fread(buffer, sizeof(char), size, file);
    fclose(file);
    buffer[size] = '\0';

    doc->root = XMLNode_new(NULL);

    XMLNode_lexicalAnalysis(doc, buffer);

    return true;
}

void XMLDocument_free(XMLDocument *doc)
{
    free(doc->root);
}

XMLNode *XMLNode_new(XMLNode *parent)
{
    XMLNode *node = calloc(sizeof(XMLNode), 1);

    node->parent = parent;
    node->tag = NULL;
    node->content = NULL;
    return node;
}

void XMLNode_free(XMLNode *node)
{
    if (node->tag)
        free(node->tag);
    if (node->content)
        free(node->content);
    if (node)
        free(node);
}
