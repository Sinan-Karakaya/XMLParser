#include "core.h"

bool XMLDocument_load(XMLDocument *doc, const char *path)
{
    FILE *file = fopen(path, "r");
    int size = -1;

    if (!file) {
        perror(strcat("Could not load XML document: ", path));
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

static void node_out(FILE *file, XMLNode *node, int indent, int times)
{
    for (size_t i = 0; i < node->children.size; i++) {
        XMLNode *child = node->children.data[i];

        if (times > 0)
            fprintf(file, "%*s", indent * times, " ");

        fprintf(file, "<%s", child->tag);
        for (size_t i = 0; i < child->attributes.size; i++) {
            XMLAttribute attr = child->attributes.data[i];
            if (!strcmp(attr.value, ""))
                continue;
            fprintf(file, " %s=\"%s\"", attr.key, attr.value);
        }

        if (child->children.size == 0 && !child->content) {
            fprintf(file, " />\n");
        } else {
            fprintf(file, ">");
            if (child->children.size == 0)
                fprintf(file, "%s</%s>\n", child->content, child->tag);
            else {
                fprintf(file, "\n");
                node_out(file, child, indent, times + 1);
                if (times > 0)
                    fprintf(file, "%*s", indent * times, " ");
                fprintf(file, "</%s>\n", child->tag);
            }
        }
    }
}

bool XMLDocument_write(XMLDocument *doc, const char *path, unsigned int indent)
{
    FILE *file = fopen(path, "w");

    if (!file) {
        perror(strcat("Could not write XML document: ", path));
        return false;
    }
    fprintf(file, "<?xml version=\"%s\" encoding=\"%s\"?>\n",
    (doc->version) ? doc->version : "1.0",
    (doc->encoding) ? doc->encoding : "UTF-8");
    node_out(file, doc->root, indent, 0);
    fclose(file);
    return true;
}

bool ends_with(const char *str, const char *to_find)
{
    size_t s_len = strlen(str);
    size_t t_len = strlen(to_find);

    if (s_len < t_len)
        return false;
    for (size_t i = 0; i < t_len; i++) {
        if (str[s_len - t_len + i] != to_find[i])
            return false;
    }
    return true;
}
