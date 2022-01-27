#ifndef _PYMUSTACH_H
#define _PYMUSTACH_H

#include <Python.h>
#include <stddef.h>
#include <stdio.h>

int pymustach_process_cjson(const char *template, size_t length, const char *value, size_t buffer_length, int flags, FILE *file);
int pymustach_process_jansson(const char *template, size_t length, const char *buffer, size_t buflen, int flags, FILE *file);
int pymustach_process_json_c(const char *template, size_t length, const char *str, size_t len, int flags, FILE *file);

#endif // _PYMUSTACH_H
