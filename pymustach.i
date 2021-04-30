%module pymustach
%{
extern PyObject *pymustach(const char *json, const char *template);
extern PyObject *pymustach_cjson(const char *json, const char *template);
extern PyObject *pymustach_jansson(const char *json, const char *template);
extern PyObject *pymustach_json_c(const char *json, const char *template);

extern PyObject *pymustach_file(const char *json, const char *template, const char *file);
extern PyObject *pymustach_cjson_file(const char *json, const char *template, const char *file);
extern PyObject *pymustach_jansson_file(const char *json, const char *template, const char *file);
extern PyObject *pymustach_json_c_file(const char *json, const char *template, const char *file);
%}

extern PyObject *pymustach(const char *json, const char *template);
extern PyObject *pymustach_cjson(const char *json, const char *template);
extern PyObject *pymustach_jansson(const char *json, const char *template);
extern PyObject *pymustach_json_c(const char *json, const char *template);

extern PyObject *pymustach_file(const char *json, const char *template, const char *file);
extern PyObject *pymustach_cjson_file(const char *json, const char *template, const char *file);
extern PyObject *pymustach_jansson_file(const char *json, const char *template, const char *file);
extern PyObject *pymustach_json_c_file(const char *json, const char *template, const char *file);
