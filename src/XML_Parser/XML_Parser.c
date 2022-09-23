#include "core.h"

bool XMLNode_lexicalAnalysis(XMLDocument *doc, const char *source)
{
    char lex[256];
    int lexi = 0;
    int i = 0;

    XMLNode *currentNode = doc->root;

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
                    fprintf(stderr, BOLDRED"Already at the root\n"RESET);
                    return false;
                }
                if (strcmp(currentNode->tag, lex) != 0) {
                    fprintf(stderr, BOLDRED"Mismatched tags:%s %s != %s\n", RESET, currentNode->tag, lex);
                    return false;
                }

                currentNode = currentNode->parent;
                i++;
                continue;
            }

            // Special nodes
            if (source[i + 1] == '!') {
                while (source[i] != ' ' && source[i] != '>' )
                    lex[lexi++] = source[i++];
                lex[lexi] = '\0';

                // Comments
                if (!strcmp(lex, "<!--")) {
                    lex[lexi] = '\0';
                    while (!ends_with(lex, "-->")) {
                        lex[lexi++] = source[i++];
                        lex[lexi] = '\0';
                    }
                    continue;
                }
            }

            // Declaration tag
            if (source[i + 1] == '?') {
                while (source[i] != ' ' && source[i] != '>' )
                    lex[lexi++] = source[i++];
                lex[lexi] = '\0';

                // XML Declaration
                if (!strcmp(lex, "<?xml")) {
                    lexi = 0;
                    XMLNode *decl = XMLNode_new(NULL);
                    XMLAttribute_parse(source, &i, lex, &lexi, decl);

                    doc->version = XMLNode_getAttributeValue(decl, "version");
                    doc->encoding = XMLNode_getAttributeValue(decl, "encoding");
                    continue;
                }
            }

            // Set current node
           currentNode = XMLNode_new(currentNode);

            // Parse in tag
            i++;
            XMLAttribute_parse(source, &i, lex, &lexi, currentNode);

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