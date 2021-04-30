#include <Python.h>
#include <stddef.h>
#include <stdio.h>

int pymustach_process_cjson(const char *template, const char *value, size_t buffer_length, FILE *file);
int pymustach_process_jansson(const char *template, const char *buffer, size_t buflen, FILE *file);
int pymustach_process_json_c(const char *template, const char *str, size_t len, FILE *file);
