cmake_minimum_required(VERSION 3.13)
project(c_template C)

set(CMAKE_C_STANDARD 11)

find_package(PythonLibs 3 REQUIRED)
find_package(Tcl REQUIRED)

include_directories(.)

add_library(options SHARED options.c)

add_library(myApi SHARED myapi.c)
target_link_libraries(myApi PUBLIC options)

add_executable(c_template main.c)
target_link_libraries(c_template PRIVATE myApi)

add_library(tcl-ext SHARED tcl_extension.c)
target_link_libraries(tcl-ext PRIVATE ${TCL_LIBRARY} myApi)
# target_include_directories(tcl-ext PRIVATE ${TCL_INCLUDE_PATH})

python_add_module(myModule py_extension.c)
target_include_directories(myModule PUBLIC ${PYTHON_INCLUDE_DIRS})
target_link_libraries(myModule PUBLIC ${PYTHON_LIBRARIES} myApi)

add_custom_target(check-main
   COMMAND
   ${CMAKE_BINARY_DIR}/c_template sum -t float 1 2 3 4 5 6 7
   )

add_dependencies(check-main
   c_template)

 add_custom_target(check-py
   COMMAND
   PYTHONPATH=${CMAKE_SOURCE_DIR} python3 ${CMAKE_SOURCE_DIR}/test_py_extension.py
 )

 add_dependencies(check-py myModule)

 add_custom_target(check)
 add_dependencies(check check-py check-main)
