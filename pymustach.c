#include <Python.h>
#include <mustach/mustach.h>
#include <mustach/mustach-json-c.h>

PyObject *pymustach(const char *json, const char *template, const char *file) {
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

    switch (fmustach_json_c(template, object, out)) {
        case MUSTACH_OK: break;
        case MUSTACH_ERROR_SYSTEM: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_SYSTEM"); goto json_object_put;
        case MUSTACH_ERROR_UNEXPECTED_END: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_UNEXPECTED_END"); goto json_object_put;
        case MUSTACH_ERROR_EMPTY_TAG: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_EMPTY_TAG"); goto json_object_put;
        case MUSTACH_ERROR_TAG_TOO_LONG: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_TAG_TOO_LONG"); goto json_object_put;
        case MUSTACH_ERROR_BAD_SEPARATORS: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_BAD_SEPARATORS"); goto json_object_put;
        case MUSTACH_ERROR_TOO_DEEP: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_TOO_DEEP"); goto json_object_put;
        case MUSTACH_ERROR_CLOSING: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_CLOSING"); goto json_object_put;
        case MUSTACH_ERROR_BAD_UNESCAPE_TAG: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_BAD_UNESCAPE_TAG"); goto json_object_put;
        case MUSTACH_ERROR_INVALID_ITF: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_INVALID_ITF"); goto json_object_put;
        case MUSTACH_ERROR_ITEM_NOT_FOUND: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_ITEM_NOT_FOUND"); goto json_object_put;
        case MUSTACH_ERROR_PARTIAL_NOT_FOUND: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_PARTIAL_NOT_FOUND"); goto json_object_put;
        default: PyErr_SetString(PyExc_TypeError, "fmustach_json_c"); goto json_object_put;
    }
    if (!json_object_put(object)) { PyErr_SetString(PyExc_TypeError, "!json_object_put"); goto free; }
    fclose(out);
    if (file) Py_RETURN_TRUE; else {
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
