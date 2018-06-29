from distutils.core import setup, Extension

module = Extension('myModule', sources=['options.c', 'myapi.c', 'py_extension.c'])

setup(name='ThePackageName',
        version='1.0',
        description='Python extension wrapping a command line tool',
        ext_modules=[module]
)
