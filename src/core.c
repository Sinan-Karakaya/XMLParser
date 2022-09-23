#include "core.h"

int main(int ac, char **av)
{
    XMLDocument doc;
    if (XMLDocument_load(&doc, av[1])) {
        XMLNode *more_node = XMLNode_getChild(XMLNode_getChild(doc.root, 0), 0);
        printf("%s : %s\n", more_node->tag, more_node->content);

        XMLNode *another_node = XMLNode_getChild(doc.root, 1);
        printf("%s : %s\n", another_node->tag, another_node->content);

        XMLDocument_free(&doc);
    }
    return 0;
}
