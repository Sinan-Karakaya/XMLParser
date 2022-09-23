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
