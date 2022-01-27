%module pymustach
%{
extern PyObject *pymustach_with_allextensions(void);
extern PyObject *pymustach_with_colon(void);
extern PyObject *pymustach_with_compare(void);
extern PyObject *pymustach_with_emptytag(void);
extern PyObject *pymustach_with_equal(void);
extern PyObject *pymustach_with_errorundefined(void);
extern PyObject *pymustach_with_escfirstcmp(void);
extern PyObject *pymustach_with_incpartial(void);
extern PyObject *pymustach_with_jsonpointer(void);
extern PyObject *pymustach_with_noextensions(void);
extern PyObject *pymustach_with_objectiter(void);
extern PyObject *pymustach_with_partialdatafirst(void);
extern PyObject *pymustach_with_singledot(void);

extern PyObject *pymustach(PyObject *json, PyObject *template);
extern PyObject *pymustach_cjson(PyObject *json, PyObject *template);
extern PyObject *pymustach_jansson(PyObject *json, PyObject *template);
extern PyObject *pymustach_json_c(PyObject *json, PyObject *template);

extern PyObject *pymustach_file(PyObject *json, PyObject *template, PyObject *name);
extern PyObject *pymustach_cjson_file(PyObject *json, PyObject *template, PyObject *name);
extern PyObject *pymustach_jansson_file(PyObject *json, PyObject *template, PyObject *name);
extern PyObject *pymustach_json_c_file(PyObject *json, PyObject *template, PyObject *name);
%}

extern PyObject *pymustach_with_allextensions(void);
extern PyObject *pymustach_with_colon(void);
extern PyObject *pymustach_with_compare(void);
extern PyObject *pymustach_with_emptytag(void);
extern PyObject *pymustach_with_equal(void);
extern PyObject *pymustach_with_errorundefined(void);
extern PyObject *pymustach_with_escfirstcmp(void);
extern PyObject *pymustach_with_incpartial(void);
extern PyObject *pymustach_with_jsonpointer(void);
extern PyObject *pymustach_with_noextensions(void);
extern PyObject *pymustach_with_objectiter(void);
extern PyObject *pymustach_with_partialdatafirst(void);
extern PyObject *pymustach_with_singledot(void);

extern PyObject *pymustach(PyObject *json, PyObject *template);
extern PyObject *pymustach_cjson(PyObject *json, PyObject *template);
extern PyObject *pymustach_jansson(PyObject *json, PyObject *template);
extern PyObject *pymustach_json_c(PyObject *json, PyObject *template);

extern PyObject *pymustach_file(PyObject *json, PyObject *template, PyObject *name);
extern PyObject *pymustach_cjson_file(PyObject *json, PyObject *template, PyObject *name);
extern PyObject *pymustach_jansson_file(PyObject *json, PyObject *template, PyObject *name);
extern PyObject *pymustach_json_c_file(PyObject *json, PyObject *template, PyObject *name);
