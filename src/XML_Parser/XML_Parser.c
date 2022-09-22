#include "core.h"

bool XMLNode_lexicalAnalysis(XMLDocument *doc, const char *source)
{
    char lex[256];
    int lexi = 0;
    int i = 0;

    XMLNode *currentNode = NULL;

    while (source[i]) {
        if (source[i] == '<') {
            lex[lexi] = '\0';

            // Inner text (content)
            if (lexi > 0) {
                if (!currentNode) {
                    fprintf(stderr, "Text outside of document\n");
                    return false;
                }
                currentNode->content = strdup(lex);
                lexi = 0;
            }

            // End of Node
            if (source[i + 1] == '/') {
                i += 2;
                while (source[i] != '>')
                    lex[lexi++] = source[i++];
                lex[lexi] = '\0';

                if (!currentNode) {
                    fprintf(stderr, "Already at the root\n");
                    return false;
                }
                if (strcmp(currentNode->tag, lex) != 0) {
                    fprintf(stderr, "Mismatched tags: %s != %s", currentNode->tag, lex);
                    return false;
                }

                currentNode = currentNode->parent;
                i++;
                continue;
            }

            // Set current node
            if (!currentNode)
                currentNode = doc->root;
            else
                currentNode = XMLNode_new(currentNode);

            // Get beginning of tag
            i++;
            XMLAttribute currAttr = {0, 0};
            while (source[i] != '>') {
                lex[lexi++] = source[i++];

                // Tag Name
                if (source[i] == ' ' && !currentNode->tag) {
                    lex[lexi] = '\0';
                    currentNode->tag = strdup(lex);
                    lexi = 0;
                    i++;
                    continue;
                }

                // Ignore spaces at end of tag
                if (lex[lexi - 1] == ' ') {
                    lexi--;
                    continue;
                }

                // Get attribute key
                if (source[i] == '=') {
                    lex[lexi] = '\0';
                    currAttr.key = strdup(lex);
                    lexi = 0;
                    continue;
                }

                // Get attribute value
                if (source[i] == '"') {
                    if (!currAttr.key) {
                        fprintf(stderr, "Attribute value without key\n");
                        return false;
                    }
                    lexi = 0;
                    i++;

                    while (source[i] != '"')
                        lex[lexi++] = source[i++];
                    lex[lexi] = '\0';
                    currAttr.value = strdup(lex);
                    XMLAttributesList_add(&currentNode->attributes, &currAttr);
                    currAttr.key = NULL;
                    currAttr.value = NULL;
                    lexi = 0;
                    i++;
                    continue;
                }
            }

            // Set tag name
            lex[lexi] = '\0';
            if (!currentNode->tag)
                currentNode->tag = strdup(lex);

            // Reset lexer
            lexi = 0;
            i++;
            continue;
        } else {
            lex[lexi++] = source[i++];
        }
    }
    return true;
}