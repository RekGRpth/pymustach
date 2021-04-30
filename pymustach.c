#include "pymustach.h"
#include <mustach/mustach.h>

static PyObject *pymustach_internal(PyObject *json, const char *template, const char *file, int (*pymustach_process)(const char *template, const char *data, size_t len, FILE *file)) {
    char *input_data;
    char *output_data;
    FILE *out;
    Py_ssize_t input_len;
    Py_ssize_t output_len;
    if (!PyBytes_Check(json)) { PyErr_SetString(PyExc_TypeError, "!PyBytes_Check"); goto ret; }
    if (PyBytes_AsStringAndSize(json, &input_data, &input_len)) { PyErr_SetString(PyExc_TypeError, "PyBytes_AsStringAndSize"); goto ret; }
    if (file) {
        if (!(out = fopen(file, "wb"))) { PyErr_SetString(PyExc_TypeError, "!fopen"); goto ret; }
    } else {
        if (!(out = open_memstream(&output_data, (size_t *)&output_len))) { PyErr_SetString(PyExc_TypeError, "!open_memstream"); goto ret; }
    }
    switch (pymustach_process(template, input_data, input_len, out)) {
        case MUSTACH_OK: break;
        case MUSTACH_ERROR_SYSTEM: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_SYSTEM"); goto free;
        case MUSTACH_ERROR_UNEXPECTED_END: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_UNEXPECTED_END"); goto free;
        case MUSTACH_ERROR_EMPTY_TAG: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_EMPTY_TAG"); goto free;
        case MUSTACH_ERROR_TAG_TOO_LONG: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_TAG_TOO_LONG"); goto free;
        case MUSTACH_ERROR_BAD_SEPARATORS: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_BAD_SEPARATORS"); goto free;
        case MUSTACH_ERROR_TOO_DEEP: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_TOO_DEEP"); goto free;
        case MUSTACH_ERROR_CLOSING: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_CLOSING"); goto free;
        case MUSTACH_ERROR_BAD_UNESCAPE_TAG: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_BAD_UNESCAPE_TAG"); goto free;
        case MUSTACH_ERROR_INVALID_ITF: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_INVALID_ITF"); goto free;
        case MUSTACH_ERROR_ITEM_NOT_FOUND: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_ITEM_NOT_FOUND"); goto free;
        case MUSTACH_ERROR_PARTIAL_NOT_FOUND: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_PARTIAL_NOT_FOUND"); goto free;
        default: PyErr_SetString(PyExc_TypeError, "ngx_http_mustach_process"); goto free;
    }
    if (file) Py_RETURN_TRUE; else {
        fclose(out);
        PyObject *bytes = PyBytes_FromStringAndSize(output_data, output_len);
        free(output_data);
        return bytes;
    }
free:
    if (!file) free(output_data);
ret:
    Py_RETURN_NONE;
}

PyObject *pymustach(PyObject *json, const char *template) { return pymustach_internal(json, template, NULL, pymustach_process_json_c); }
PyObject *pymustach_cjson(PyObject *json, const char *template) { return pymustach_internal(json, template, NULL, pymustach_process_cjson); }
PyObject *pymustach_jansson(PyObject *json, const char *template) { return pymustach_internal(json, template, NULL, pymustach_process_jansson); }
PyObject *pymustach_json_c(PyObject *json, const char *template) { return pymustach_internal(json, template, NULL, pymustach_process_json_c); }

PyObject *pymustach_file(PyObject *json, const char *template, const char *file) { return pymustach_internal(json, template, file, pymustach_process_json_c); }
PyObject *pymustach_cjson_file(PyObject *json, const char *template, const char *file) { return pymustach_internal(json, template, file, pymustach_process_cjson); }
PyObject *pymustach_jansson_file(PyObject *json, const char *template, const char *file) { return pymustach_internal(json, template, file, pymustach_process_jansson); }
PyObject *pymustach_json_c_file(PyObject *json, const char *template, const char *file) { return pymustach_internal(json, template, file, pymustach_process_json_c); }
