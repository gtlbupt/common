
#pragma once

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&); \
    TypeName& operator=(const TypeName&)

#define ARRAY_LENGTH(x) (sizeof(x)/sizeof(x[0]))
