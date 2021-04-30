%module pymustach
%{
extern PyObject *pymustach_cjson(const char *json, const char *template, const char *file);
extern PyObject *pymustach_jansson(const char *json, const char *template, const char *file);
extern PyObject *pymustach_json_c(const char *json, const char *template, const char *file);
%}

extern PyObject *pymustach_cjson(const char *json, const char *template, const char *file);
extern PyObject *pymustach_jansson(const char *json, const char *template, const char *file);
extern PyObject *pymustach_json_c(const char *json, const char *template, const char *file);
