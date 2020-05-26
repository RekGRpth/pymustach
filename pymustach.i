%module pymustach
%{
extern PyObject *pymustach(const char *json, const char *template, const char *file);
%}

extern PyObject *pymustach(const char *json, const char *template, const char *file);
