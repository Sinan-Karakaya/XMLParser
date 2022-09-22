#include "core.h"

int main(int ac, char **av)
{
    XMLDocument doc;
    if (XMLDocument_load(&doc, av[1])) {
        printf("%s: %s\n", doc.root->tag, doc.root->content);

        XMLNode node = *doc.root;
        for (int i = 0; i < node.attributes.size; i++) {
            XMLAttribute attr = node.attributes.data[i];
            printf("%s => %s\n", attr.key,attr.value);
        }
        XMLDocument_free(&doc);
    }
    return 0;
}