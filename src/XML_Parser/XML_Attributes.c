#include "core.h"

void XMLAttribute_free(XMLAttribute *attr)
{
    if (attr->key)
        free(attr->key);
    if (attr->value)
        free(attr->value);
}

bool XMLAttributeList_init(XMLAttributeList *list)
{
    list->heap_size = 1;
    list->size = 0;
    list->data = calloc(sizeof(XMLAttribute), list->heap_size);
    if (!list->data)
        return false;
    return true;
}

void XMLAttributeList_add(XMLAttributeList *list, XMLAttribute *attr)
{
    while (list->size >= list->heap_size) {
        list->heap_size *= 2;
        list->data = realloc(list->data, sizeof(XMLAttribute) * list->heap_size);
    }
    list->data[list->size++] = *attr;
}

TagType XMLAttribute_parse(const char *source, int *i, char *lex, int *lexi, XMLNode *currentNode)
{
    XMLAttribute currAttr = {0, 0};
    while (source[*i] != '>') {
        lex[(*lexi)++] = source[(*i)++];

        // Tag Name
        if (source[*i] == ' ' && !currentNode->tag) {
            lex[*lexi] = '\0';
            currentNode->tag = strdup(lex);
            *lexi = 0;
            (*i)++;
            continue;
        }

        // Ignore spaces at end of tag
        if (lex[*lexi - 1] == ' ') {
            (*lexi)--;
        }

        // Get attribute key
        if (source[*i] == '=') {
            lex[*lexi] = '\0';
            currAttr.key = strdup(lex);
            *lexi = 0;
            continue;
        }

        // Get attribute value
        if (source[*i] == '"') {
            if (!currAttr.key) {
                fprintf(stderr, BOLDRED"Attribute value without key\n"RESET);
                exit(1);
            }
            *lexi = 0;
            (*i)++;

            while (source[*i] != '"')
                lex[(*lexi)++] = source[(*i)++];
            lex[*lexi] = '\0';
            currAttr.value = strdup(lex);
            XMLAttributeList_add(&currentNode->attributes, &currAttr);
            currAttr.key = NULL;
            currAttr.value = NULL;
            *lexi = 0;
            (*i)++;
            continue;
        }

        // Inline Node
        if (source[*i - 1] == '/' && source[*i] == '>') {
            lex[*lexi] = '\0';
            if (!currentNode->tag)
                currentNode->tag = strdup(lex);
            (*i)++;
            return TAG_INLINE;
        }
    }
    return TAG_START;
}
