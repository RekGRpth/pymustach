from distutils.core import setup, Extension

module = Extension(
    "_pymustach",
    ["pymustach.i", "pymustach.c", "pymustach-cjson.c", "pymustach-jansson.c", "pymustach-json-c.c"],
    libraries=["mustach"],
)

setup(
    ext_modules=[module],
    name="pymustach",
    py_modules=["pymustach"],
    url="https://github.com/RekGRpth/pymustach",
    version='1.0.0',
)
