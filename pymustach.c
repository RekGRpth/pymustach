#include <Python.h>
#include <stddef.h>
#include <stdio.h>

#include <mustach/mustach.h>
#include <mustach/mustach-wrap.h>

int mustach_process_cjson(const char *template, size_t length, const char *value, size_t buffer_length, int flags, FILE *file, char **err);
int mustach_process_jansson(const char *template, size_t length, const char *buffer, size_t buflen, int flags, FILE *file, char **err);
int mustach_process_json_c(const char *template, size_t length, const char *str, size_t len, int flags, FILE *file, char **err);

#if PY_VERSION_HEX < 0x03000000
const char *PyUnicode_AsUTF8AndSize(PyObject *unicode, Py_ssize_t *psize) {
    if (!PyUnicode_Check(unicode)) { PyErr_BadArgument(); return NULL; }
    PyObject *utf8 = PyUnicode_AsUTF8String(unicode);
    if (!utf8) { PyErr_BadArgument(); return NULL; }
    const char *data = PyString_AsString(utf8);
    if (psize) *psize = PyString_GET_SIZE(utf8);
    return data;
}

const char *PyUnicode_AsUTF8(PyObject *unicode) {
    return PyUnicode_AsUTF8AndSize(unicode, NULL);
}
#endif

static int flags = Mustach_With_AllExtensions;

PyObject *pymustach_with_allextensions(void) { flags |= Mustach_With_AllExtensions; Py_RETURN_NONE; }
PyObject *pymustach_with_colon(void) { flags |= Mustach_With_Colon; Py_RETURN_NONE; }
PyObject *pymustach_with_compare(void) { flags |= Mustach_With_Compare; Py_RETURN_NONE; }
PyObject *pymustach_with_emptytag(void) { flags |= Mustach_With_EmptyTag; Py_RETURN_NONE; }
PyObject *pymustach_with_equal(void) { flags |= Mustach_With_Equal; Py_RETURN_NONE; }
PyObject *pymustach_with_errorundefined(void) { flags |= Mustach_With_ErrorUndefined; Py_RETURN_NONE; }
PyObject *pymustach_with_escfirstcmp(void) { flags |= Mustach_With_EscFirstCmp; Py_RETURN_NONE; }
PyObject *pymustach_with_incpartial(void) { flags |= Mustach_With_IncPartial; Py_RETURN_NONE; }
PyObject *pymustach_with_jsonpointer(void) { flags |= Mustach_With_JsonPointer; Py_RETURN_NONE; }
PyObject *pymustach_with_noextensions(void) { flags = Mustach_With_NoExtensions; Py_RETURN_NONE; }
PyObject *pymustach_with_objectiter(void) { flags |= Mustach_With_ObjectIter; Py_RETURN_NONE; }
PyObject *pymustach_with_partialdatafirst(void) { flags |= Mustach_With_PartialDataFirst; Py_RETURN_NONE; }
PyObject *pymustach_with_singledot(void) { flags |= Mustach_With_SingleDot; Py_RETURN_NONE; }

static PyObject *pymustach_internal(PyObject *json, PyObject *template, PyObject *name, int (*pymustach_process)(const char *template, size_t length, const char *data, size_t len, int flags, FILE *file, char **err)) {
    char *err;
    char *data = NULL;
    const char *json_data;
    const char *template_data;
    FILE *file;
    Py_ssize_t json_len;
    Py_ssize_t len;
    Py_ssize_t template_len;
    if (!PyUnicode_Check(json)) { PyErr_SetString(PyExc_TypeError, "!PyUnicode_Check"); goto ret; }
    if (!PyUnicode_Check(template)) { PyErr_SetString(PyExc_TypeError, "!PyUnicode_Check"); goto ret; }
    if (!(json_data = PyUnicode_AsUTF8AndSize(json, &json_len))) { PyErr_SetString(PyExc_TypeError, "!PyUnicode_AsUTF8AndSize"); goto ret; }
    if (!(template_data = PyUnicode_AsUTF8AndSize(template, &template_len))) { PyErr_SetString(PyExc_TypeError, "!PyUnicode_AsUTF8AndSize"); goto ret; }
    if (name) {
        const char *file_data;
        if (!PyUnicode_Check(name)) { PyErr_SetString(PyExc_TypeError, "!PyUnicode_Check"); goto ret; }
        if (!(file_data = PyUnicode_AsUTF8(name))) { PyErr_SetString(PyExc_TypeError, "!PyUnicode_AsUTF8"); goto ret; }
        if (!(file = fopen(file_data, "wb"))) { PyErr_SetString(PyExc_TypeError, "!fopen"); goto ret; }
    } else {
        if (!(file = open_memstream(&data, (size_t *)&len))) { PyErr_SetString(PyExc_TypeError, "!open_memstream"); goto ret; }
    }
    switch (pymustach_process(template_data, template_len, json_data, json_len, flags, file, &err)) {
        case MUSTACH_OK: break;
        case MUSTACH_ERROR_SYSTEM: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_SYSTEM"); if (data) free(data); goto ret;
        case MUSTACH_ERROR_UNEXPECTED_END: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_UNEXPECTED_END"); if (data) free(data); goto ret;
        case MUSTACH_ERROR_EMPTY_TAG: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_EMPTY_TAG"); if (data) free(data); goto ret;
#if MUSTACH_VERSION >= 200
        case MUSTACH_ERROR_TOO_BIG: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_TOO_BIG"); if (data) free(data); goto ret;
#else
        case MUSTACH_ERROR_TAG_TOO_LONG: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_TAG_TOO_LONG"); if (data) free(data); goto ret;
#endif
#if MUSTACH_VERSION >= 200
        case MUSTACH_ERROR_BAD_DELIMITER: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_BAD_DELIMITER"); if (data) free(data); goto ret;
#else
        case MUSTACH_ERROR_BAD_SEPARATORS: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_BAD_SEPARATORS"); if (data) free(data); goto ret;
#endif
        case MUSTACH_ERROR_TOO_DEEP: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_TOO_DEEP"); if (data) free(data); goto ret;
        case MUSTACH_ERROR_CLOSING: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_CLOSING"); if (data) free(data); goto ret;
        case MUSTACH_ERROR_BAD_UNESCAPE_TAG: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_BAD_UNESCAPE_TAG"); if (data) free(data); goto ret;
        case MUSTACH_ERROR_INVALID_ITF: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_INVALID_ITF"); if (data) free(data); goto ret;
#if MUSTACH_VERSION >= 200
        case MUSTACH_ERROR_NOT_FOUND: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_NOT_FOUND"); if (data) free(data); goto ret;
#else
        case MUSTACH_ERROR_ITEM_NOT_FOUND: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_ITEM_NOT_FOUND"); if (data) free(data); goto ret;
        case MUSTACH_ERROR_PARTIAL_NOT_FOUND: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_PARTIAL_NOT_FOUND"); if (data) free(data); goto ret;
#endif
        case MUSTACH_ERROR_UNDEFINED_TAG: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_UNDEFINED_TAG"); if (data) free(data); goto ret;
        case MUSTACH_ERROR_TOO_MUCH_NESTING: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_TOO_MUCH_NESTING"); if (data) free(data); goto ret;
#if MUSTACH_VERSION >= 200
        case MUSTACH_ERROR_OUT_OF_MEMORY: PyErr_SetString(PyExc_TypeError, "MUSTACH_ERROR_OUT_OF_MEMORY"); if (data) free(data); goto ret;
#endif
        default: PyErr_Format(PyExc_TypeError, "%s", err); if (data) free(data); goto ret;
    }
    if (name) Py_RETURN_TRUE; else {
        PyObject *unicode = PyUnicode_FromStringAndSize(data, len);
        free(data);
        return unicode;
    }
ret:
    return NULL;
}

PyObject *pymustach(PyObject *json, PyObject *template) { return pymustach_internal(json, template, NULL, mustach_process_json_c); }
PyObject *pymustach_cjson(PyObject *json, PyObject *template) { return pymustach_internal(json, template, NULL, mustach_process_cjson); }
PyObject *pymustach_jansson(PyObject *json, PyObject *template) { return pymustach_internal(json, template, NULL, mustach_process_jansson); }
PyObject *pymustach_json_c(PyObject *json, PyObject *template) { return pymustach_internal(json, template, NULL, mustach_process_json_c); }

PyObject *pymustach_file(PyObject *json, PyObject *template, PyObject *name) { return pymustach_internal(json, template, name, mustach_process_json_c); }
PyObject *pymustach_cjson_file(PyObject *json, PyObject *template, PyObject *name) { return pymustach_internal(json, template, name, mustach_process_cjson); }
PyObject *pymustach_jansson_file(PyObject *json, PyObject *template, PyObject *name) { return pymustach_internal(json, template, name, mustach_process_jansson); }
PyObject *pymustach_json_c_file(PyObject *json, PyObject *template, PyObject *name) { return pymustach_internal(json, template, name, mustach_process_json_c); }
