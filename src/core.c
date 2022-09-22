#include "core.h"

int main(int ac, char **av)
{
    XMLDocument doc;
    if (XMLDocument_load(&doc, av[1])) {
        printf("%s: %s", doc.root->tag, doc.root->content);
        XMLDocument_free(&doc);
    }
    return 0;
}