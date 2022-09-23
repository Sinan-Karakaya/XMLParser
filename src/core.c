#include "core.h"

int main(int ac, char **av)
{
    XMLDocument doc;
    if (XMLDocument_load(&doc, av[1])) {
        XMLNode* str = XMLNode_getChild(doc.root, 0);

        XMLNodeList* fields = XMLNode_getChildrenByTag(str, "field");
        for (size_t i = 0; i < fields->size; i++) {
            XMLNode* field = XMLNode_getAt(fields, i);
            XMLAttribute* type = XMLNode_getAttribute(field, "type");
            type->value = "";
        }

        XMLDocument_write(&doc, "out.xml", 2);
        XMLDocument_free(&doc);
    }
    return 0;
}
