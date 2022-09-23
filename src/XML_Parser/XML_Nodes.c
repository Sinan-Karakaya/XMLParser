#include "core.h"

XMLNode *XMLNode_new(XMLNode *parent)
{
    XMLNode *node = calloc(sizeof(XMLNode), 1);

    node->parent = parent;
    node->tag = NULL;
    node->content = NULL;
    XMLAttributeList_init(&node->attributes);
    XMLNodeList_init(&node->children);
    if (parent)
        XMLNodeList_add(&parent->children, node);
    return node;
}

void XMLNode_free(XMLNode *node)
{
    if (node->tag)
        free(node->tag);
    if (node->content)
        free(node->content);
    for (int i = 0; i < node->attributes.size; i++)
        XMLAttribute_free(&node->attributes.data[i]);
    if (node)
        free(node);
}

XMLNode *XMLNode_getChild(XMLNode *node, const unsigned int index)
{
    if (index >= node->children.size)
        return NULL;
    return node->children.data[index];
}

void XMLNodeList_init(XMLNodeList *list)
{
    list->heap_size = 1;
    list->size = 0;
    list->data = calloc(sizeof(XMLNode*), list->heap_size);
}

void XMLNodeList_add(XMLNodeList *list, XMLNode *node)
{
    while (list->size >= list->heap_size) {
        list->heap_size *= 2;
        list->data = realloc(list->data, sizeof(XMLNode*) * list->heap_size);
    }
    list->data[list->size++] = node;
}
