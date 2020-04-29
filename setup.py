from distutils.core import setup, Extension
from distutils.command.build_py import build_py as build_py_orig
import sys, os

class build_ext_first(build_py_orig):
    def run(self):
        self.run_command("build_ext")
        return super().run()

if sys.platform.startswith("linux"):
    module = Extension(
        "_pymustach",
        ["pymustach.i", "pymustach.c"],
        libraries=[
            "mustach",
        ],
    )

setup(
    name="pymustach",
    url="https://github.com/RekGRpth/pymustach",
    cmdclass={"build_py": build_ext_first},
    ext_modules=[module],
    py_modules=["pymustach"],
)
