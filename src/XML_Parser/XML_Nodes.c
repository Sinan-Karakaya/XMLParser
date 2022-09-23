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
    for (size_t i = 0; i < node->attributes.size; i++)
        XMLAttribute_free(&node->attributes.data[i]);
    if (node)
        free(node);
}

XMLNode *XMLNode_getChild(XMLNode *node, const size_t index)
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

void XMLNodeList_free(XMLNodeList *list)
{
    if (list)
        free(list);
}

void XMLNodeList_add(XMLNodeList *list, XMLNode *node)
{
    while (list->size >= list->heap_size) {
        list->heap_size *= 2;
        list->data = realloc(list->data, sizeof(XMLNode*) * list->heap_size);
    }
    list->data[list->size++] = node;
}

XMLAttribute *XMLNode_getAttribute(XMLNode *node, char *key)
{
    for (size_t i = 0; i < node->attributes.size; i++) {
        XMLAttribute *attr = &node->attributes.data[i];
        if (strcmp(attr->key, key) == 0)
            return attr;
    }
    return NULL;
}

const char *XMLNode_getAttributeValue(XMLNode *node, const char *key)
{
    for (size_t i = 0; i < node->attributes.size; i++) {
        XMLAttribute attr = node->attributes.data[i];
        if (strcmp(attr.key, key) == 0)
            return attr.value;
    }
    return NULL;
}

XMLNode *XMLNode_getAt(XMLNodeList *list, const int index)
{
    if ((size_t)index >= list->size)
        return NULL;
    return list->data[index];
}

XMLNodeList *XMLNode_getChildrenByTag(XMLNode *parent, const char *tag)
{
    XMLNodeList *list = calloc(sizeof(XMLNodeList), 1);

    XMLNodeList_init(list);
    for (size_t i = 0; i < parent->children.size; i++) {
        XMLNode *child = parent->children.data[i];
        if (strcmp(child->tag, tag) == 0)
            XMLNodeList_add(list, child);
    }
    return list;
}
