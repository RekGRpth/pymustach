#include "pymustach.h"

#if __has_include(<mustach/mustach-jansson.h>)
#include <mustach/mustach-jansson.h>

int pymustach_process_jansson(const char *template, size_t length, const char *buffer, size_t buflen, FILE *file) {
    int rc = -1;
    json_error_t error;
    json_t *root;
    if (!(root = json_loadb(buffer, buflen, JSON_DECODE_ANY, &error))) { PyErr_Format(PyExc_TypeError, "!json_loadb and %s", error.text); goto ret; }
    rc = mustach_jansson_file(template, length, root, Mustach_With_AllExtensions | Mustach_With_ErrorUndefined, file);
    json_decref(root);
ret:
    return rc;
}
#else
int pymustach_process_jansson(const char *template, size_t length, const char *buffer, size_t buflen, FILE *file) {
    PyErr_Format(PyExc_TypeError, "!mustach_jansson");
    return -1;
}
#endif
