#include "core.h"

int main(int ac, char **av)
{
    XMLDocument doc;
    if (XMLDocument_load(&doc, av[1])) {
        printf("%s %s\n\n", doc.version, doc.encoding);

        XMLNode *root = XMLNode_getChild(doc.root, 0);
        printf("%s (%s = %s)\n", root->tag, root->attributes.data[0].key, root->attributes.data[0].value);

        XMLNode *text = XMLNode_getChild(root, 0);
        printf("%s : %s (%s = %s)\n", text->tag, text->content, text->attributes.data[0].key, text->attributes.data[0].value);
        XMLDocument_free(&doc);
    }
    return 0;
}
