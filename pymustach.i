%module pymustach
%{
extern PyObject *pymustach(PyObject *json, const char *template);
extern PyObject *pymustach_cjson(PyObject *json, const char *template);
extern PyObject *pymustach_jansson(PyObject *json, const char *template);
extern PyObject *pymustach_json_c(PyObject *json, const char *template);

extern PyObject *pymustach_file(PyObject *json, const char *template, const char *file);
extern PyObject *pymustach_cjson_file(PyObject *json, const char *template, const char *file);
extern PyObject *pymustach_jansson_file(PyObject *json, const char *template, const char *file);
extern PyObject *pymustach_json_c_file(PyObject *json, const char *template, const char *file);
%}

extern PyObject *pymustach(PyObject *json, const char *template);
extern PyObject *pymustach_cjson(PyObject *json, const char *template);
extern PyObject *pymustach_jansson(PyObject *json, const char *template);
extern PyObject *pymustach_json_c(PyObject *json, const char *template);

extern PyObject *pymustach_file(PyObject *json, const char *template, const char *file);
extern PyObject *pymustach_cjson_file(PyObject *json, const char *template, const char *file);
extern PyObject *pymustach_jansson_file(PyObject *json, const char *template, const char *file);
extern PyObject *pymustach_json_c_file(PyObject *json, const char *template, const char *file);
