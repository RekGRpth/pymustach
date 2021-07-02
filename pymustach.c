#include "pymustach.h"
#include <mustach/mustach.h>

#ifndef PyUnicode_AsUTF8AndSize
const char *PyUnicode_AsUTF8AndSize(PyObject *unicode, Py_ssize_t *psize) {
    if (!PyUnicode_Check(unicode)) { PyErr_BadArgument(); return NULL; }
    const char *data = PyUnicode_AS_DATA(unicode);
    if (psize) *psize = strlen(data);
    return data;
}

const char *PyUnicode_AsUTF8(PyObject *unicode) {
    return PyUnicode_AsUTF8AndSize(unicode, NULL);
}
#endif

static PyObject *pymustach_internal(PyObject *json, PyObject *template, PyObject *file, int (*pymustach_process)(const char *template, size_t length, const char *data, size_t len, FILE *file)) {
    char *output_data;
    const char *json_data;
    const char *template_data;
    FILE *out;
    Py_ssize_t json_len;
    Py_ssize_t output_len;
    Py_ssize_t template_len;
    if (!PyUnicode_Check(json)) { PyErr_SetString(PyExc_TypeError, "!PyUnicode_Check"); goto ret; }
    if (!PyUnicode_Check(template)) { PyErr_SetString(PyExc_TypeError, "!PyUnicode_Check"); goto ret; }
    if (!(json_data = PyUnicode_AsUTF8AndSize(json, &json_len))) { PyErr_SetString(PyExc_TypeError, "PyUnicode_AsUTF8AndSize"); goto ret; }
    if (!(template_data = PyUnicode_AsUTF8AndSize(template, &template_len))) { PyErr_SetString(PyExc_TypeError, "PyUnicode_AsUTF8AndSize"); goto ret; }
    if (file) {
        const char *file_data;
        if (!PyUnicode_Check(file)) { PyErr_SetString(PyExc_TypeError, "!PyUnicode_Check"); goto ret; }
        if (!(file_data = PyUnicode_AsUTF8(file))) { PyErr_SetString(PyExc_TypeError, "PyUnicode_AsUTF8"); goto ret; }
        if (!(out = fopen(file_data, "wb"))) { PyErr_SetString(PyExc_TypeError, "!fopen"); goto ret; }
    } else {
        if (!(out = open_memstream(&output_data, (size_t *)&output_len))) { PyErr_SetString(PyExc_TypeError, "!open_memstream"); goto ret; }
    }
    switch (pymustach_process(template_data, template_len, json_data, json_len, out)) {
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
        PyObject *unicode = PyUnicode_FromStringAndSize(output_data, output_len);
        free(output_data);
        return unicode;
    }
free:
    if (!file) free(output_data);
ret:
    Py_RETURN_NONE;
}

PyObject *pymustach(PyObject *json, PyObject *template) { return pymustach_internal(json, template, NULL, pymustach_process_json_c); }
PyObject *pymustach_cjson(PyObject *json, PyObject *template) { return pymustach_internal(json, template, NULL, pymustach_process_cjson); }
PyObject *pymustach_jansson(PyObject *json, PyObject *template) { return pymustach_internal(json, template, NULL, pymustach_process_jansson); }
PyObject *pymustach_json_c(PyObject *json, PyObject *template) { return pymustach_internal(json, template, NULL, pymustach_process_json_c); }

PyObject *pymustach_file(PyObject *json, PyObject *template, PyObject *file) { return pymustach_internal(json, template, file, pymustach_process_json_c); }
PyObject *pymustach_cjson_file(PyObject *json, PyObject *template, PyObject *file) { return pymustach_internal(json, template, file, pymustach_process_cjson); }
PyObject *pymustach_jansson_file(PyObject *json, PyObject *template, PyObject *file) { return pymustach_internal(json, template, file, pymustach_process_jansson); }
PyObject *pymustach_json_c_file(PyObject *json, PyObject *template, PyObject *file) { return pymustach_internal(json, template, file, pymustach_process_json_c); }
