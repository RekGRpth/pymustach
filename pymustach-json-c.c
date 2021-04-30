#include "pymustach.h"
#include <mustach/mustach-json-c.h>

int pymustach_process_json_c(const char *template, const char *str, size_t len, FILE *file) {
    enum json_tokener_error error;
    int rc = -1;
    struct json_object *root;
    struct json_tokener *tok;
    if (!(tok = json_tokener_new())) { PyErr_Format(PyExc_TypeError, "!json_tokener_new"); goto ret; }
    do root = json_tokener_parse_ex(tok, str, len); while ((error = json_tokener_get_error(tok)) == json_tokener_continue);
    if (error != json_tokener_success) { PyErr_Format(PyExc_TypeError, "!json_tokener_parse_ex and %s", json_tokener_error_desc(error)); goto free; }
    if (json_tokener_get_parse_end(tok) < len) { PyErr_Format(PyExc_TypeError, "json_tokener_get_parse_end < %li", len); goto put; }
    rc = mustach_json_c_file(template, root, Mustach_With_AllExtensions, file);
put:
    if (!json_object_put(root)) PyErr_Format(PyExc_TypeError, "!json_object_put");
free:
    json_tokener_free(tok);
ret:
    return rc;
}