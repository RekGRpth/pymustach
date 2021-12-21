from distutils.core import Extension, setup

setup(
    author_email='RekGRpth@gmail.com',
    author='RekGRpth',
    ext_modules=[Extension(
        libraries=["mustach"],
        name="_pymustach",
        sources=["pymustach.i", "pymustach.c", "pymustach-cjson.c", "pymustach-jansson.c", "pymustach-json-c.c"],
    )],
    license='MIT',
    name="pymustach",
    py_modules=["pymustach"],
    url="https://github.com/RekGRpth/pymustach",
    version='1.0.0',
)
