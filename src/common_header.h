#include "util_header.h"
#include <string>
#include "types.h"
#include <memory>
using std::string;

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC false

#define DECLARE_RESOURCE(class_name) typedef std::shared_ptr<class_name> PTR;