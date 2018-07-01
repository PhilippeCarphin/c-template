# DIRECTORY STRUCTURE
src_dir=.
build_dir=.
inc_dir=.

# TARGETS
trg=a.out
shared_lib = libmyapi.$(lib_extension)
tcl_shared_lib=libtclmyapi.$(lib_extension)

# FILENAME LISTS
src = $(wildcard $(src_dir)/*.c)
obj = $(subst $(src_dir),$(build_dir),$(src:.c=.o))
main_obj = $(src_dir)/main.o
ext_obj = $(src_dir)/tcl_extension.o $(src_dir)/py_extension.o
shared_obj = $(filter-out $(main_obj) $(ext_obj),$(obj))

# COMPILATION AND LINKING FLAGS
CFLAGS= -g -Wall -MMD -I $(inc_dir) -fPIC -std=c11 -Wno-unused-function -I /usr/include/python3.6m/
LDLIBS=-L$(tcl_lib) -l tclstub8.6

# TCL shared library variables
TCL_LDFLAGS = $(LDFLAGS)
TCL_LIBS =
TCL_CFLAGS = $(CFLAGS) -DUSE_TCL_STUBS

# OS SPECIFIC STUFF
ifeq ($(shell uname), Darwin)
	lib_extension = dylib
	LDFLAGS += -dynamiclib
	TCL_LIBS += -L/Library/Frameworks/Tcl.framework -l tclstub8.5
else
	lib_extension = so
	LDFLAGS += -shared
	TCL_LIBS += -L /usr/lib/x86_64-linux-gnu/ -l tclstub8.6
	TCL_CFLAGS += -I /usr/include/tcl8.6
endif

.PHONY:pylib
all: lib libtcl pylib exec

lib:$(shared_lib)
libtcl:$(tcl_shared_lib)
pylib:$(src) setup.py

$(trg): main.c $(shared_obj)
	gcc -o $(trg) $< $(shared_obj)

$(obj): $(build_dir)/%.o : $(src_dir)/%.c
	gcc $(CFLAGS) -c $< -o $@

$(shared_lib): $(shared_obj)
	gcc $(LDFLAGS) -o $@ $^
#
$(tcl_shared_lib):tcl_extension.c $(shared_obj)
	gcc $(TCL_LDFLAGS) $(TCL_CFLAGS) $< $(shared_obj) $(TCL_LIBS) -o $@

pylib:$(src) setup.py
	rm -rf build
	python3 setup.py install --user

#
# Python shared library
clean:
	$(RM) exec $(obj) $(obj:.o=.d) *.$(lib_extension)
vars:
	@echo "src = $(src)"
	@echo "obj = $(obj)"
	@echo "shared_obj = $(shared_obj)"

test: $(trg)
	./$(trg) sum 1 2 -t float 3 4
	./$(trg) sum 1 2 -t int 3 4
	./$(trg) product 1 2 -t float 3 4
	./$(trg) product 1 2 -t int 3 4


.PHONY:vars clean
-include $(build_dir)/*.d
