#include "core.h"

void XMLAttribute_free(XMLAttribute *attr)
{
    if (attr->key)
        free(attr->key);
    if (attr->value)
        free(attr->value);
}

void XMLAttributesList_init(XMLAttributeList *list)
{
    list->heap_size = 1;
    list->size = 0;
    list->data = calloc(sizeof(XMLAttribute), list->heap_size);
}

void XMLAttributesList_add(XMLAttributeList *list, XMLAttribute *attr)
{
    while (list->size >= list->heap_size) {
        list->heap_size *= 2;
        list->data = realloc(list->data, sizeof(XMLAttribute) * list->heap_size);
    }
    list->data[list->size++] = *attr;
}
