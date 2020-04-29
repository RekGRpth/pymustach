%module pymustach
%{
extern PyObject *mustach(const char *json, const char *template, const char *file);
%}

extern PyObject *mustach(const char *json, const char *template, const char *file);
