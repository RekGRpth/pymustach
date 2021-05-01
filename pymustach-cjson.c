#include "pymustach.h"
#include <mustach/mustach-cjson.h>

int pymustach_process_cjson(const char *template, size_t length, const char *value, size_t buffer_length, FILE *file) {
    cJSON *root;
    int rc = -1;
    if (!(root = cJSON_ParseWithLength(value, buffer_length))) { PyErr_Format(PyExc_TypeError, "!cJSON_ParseWithLength"); goto ret; }
    rc = mustach_cJSON_file(template, length, root, Mustach_With_AllExtensions, file);
    cJSON_Delete(root);
ret:
    return rc;
}
