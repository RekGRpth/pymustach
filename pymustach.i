%module pymustach
%{
extern PyObject *mustach_cjson(const char *json, const char *template, const char *file);
extern PyObject *mustach_jansson(const char *json, const char *template, const char *file);
extern PyObject *mustach_json_c(const char *json, const char *template, const char *file);
%}

extern PyObject *mustach_cjson(const char *json, const char *template, const char *file);
extern PyObject *mustach_jansson(const char *json, const char *template, const char *file);
extern PyObject *mustach_json_c(const char *json, const char *template, const char *file);
