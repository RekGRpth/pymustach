#include <Python.h>
#include <mustach/mustach-json-c.h>

PyObject *mustach(const char *json, const char *template, const char *file) {
    char *output_data;
    enum json_tokener_error error;
    FILE *out;
    size_t output_len;
    struct json_object *object;
    if (file) {
        if (!(out = fopen(file, "wb"))) { PyErr_SetString(PyExc_TypeError, "!fopen"); goto Py_RETURN_NONE_; }
    } else {
        if (!(out = open_memstream(&output_data, &output_len))) { PyErr_SetString(PyExc_TypeError, "!open_memstream"); goto Py_RETURN_NONE_; }
    }
    if (!(object = json_tokener_parse_verbose(json, &error))) { PyErr_Format(PyExc_TypeError, "!json_tokener_parse and %s", json_tokener_error_desc(error)); goto free; }
    if (fmustach_json_c(template, object, out)) { PyErr_SetString(PyExc_TypeError, "fmustach_json_c"); goto json_object_put; }
    if (!json_object_put(object)) { PyErr_SetString(PyExc_TypeError, "!json_object_put"); goto free; }
    if (file) Py_RETURN_TRUE; else {
        fclose(out);
        PyObject *bytes = PyBytes_FromStringAndSize(output_data, (Py_ssize_t)output_len);
        free(output_data);
        return bytes;
    }
json_object_put:
    if (!json_object_put(object)) { PyErr_SetString(PyExc_TypeError, "!json_object_put"); }
free:
    if (!file) free(output_data);
Py_RETURN_NONE_:
    Py_RETURN_NONE;
}
