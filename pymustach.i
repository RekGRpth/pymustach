%module pymustach
%{
extern PyObject *pymustach(PyObject *json, PyObject *template);
extern PyObject *pymustach_cjson(PyObject *json, PyObject *template);
extern PyObject *pymustach_jansson(PyObject *json, PyObject *template);
extern PyObject *pymustach_json_c(PyObject *json, PyObject *template);

extern PyObject *pymustach_file(PyObject *json, PyObject *template, PyObject *file);
extern PyObject *pymustach_cjson_file(PyObject *json, PyObject *template, PyObject *file);
extern PyObject *pymustach_jansson_file(PyObject *json, PyObject *template, PyObject *file);
extern PyObject *pymustach_json_c_file(PyObject *json, PyObject *template, PyObject *file);
%}

extern PyObject *pymustach(PyObject *json, PyObject *template);
extern PyObject *pymustach_cjson(PyObject *json, PyObject *template);
extern PyObject *pymustach_jansson(PyObject *json, PyObject *template);
extern PyObject *pymustach_json_c(PyObject *json, PyObject *template);

extern PyObject *pymustach_file(PyObject *json, PyObject *template, PyObject *file);
extern PyObject *pymustach_cjson_file(PyObject *json, PyObject *template, PyObject *file);
extern PyObject *pymustach_jansson_file(PyObject *json, PyObject *template, PyObject *file);
extern PyObject *pymustach_json_c_file(PyObject *json, PyObject *template, PyObject *file);
