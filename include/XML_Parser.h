#pragma once

#include "XMLParser/XML_Document.h"
#include "XMLParser/XML_Attribute.h"
#include "XMLParser/XML_Node.h"

typedef enum TagType TagType;

enum TagType {
    TAG_START,
    TAG_INLINE,
};

bool ends_with(const char *str, const char *to_find);
