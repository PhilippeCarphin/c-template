trg=exec

src_dir=.
build_dir=.
inc_dir=.

src = $(wildcard $(src_dir)/*.c)
obj = $(subst $(src_dir),$(build_dir),$(src:.c=.o))
main_obj = $(src_dir)/main.o $(src_dir)/tcl_extension.o
shared_obj = $(filter-out $(main_obj),$(obj))
trg=exec

CFLAGS = -g -Wall -MMD -I $(inc_dir) 

all: lib
$(trg): $(obj)
	gcc -o $(trg) $(obj)
$(obj): $(build_dir)/%.o : $(src_dir)/%.c
	gcc $(CFLAGS) -c $< -o $@
# C-shared library with options.o and myapi.o
lib:libmyapi.dylib
libmyapi.dylib: $(shared_obj)
	gcc -dynamiclib -o $@ $^ 
#
# TCL-shared library with options.o, myapi.o, tcl_extension.o
libtcl:libtclmyapi.dylib
libtclmyapi.dylib:tcl_extension.o $(shared_obj)
	gcc -dynamiclib -DUSE_TCL_STUBS $< -o $@ -L/Library/Frameworks/Tcl.framework -l tclstub8.5

#
# Python shared library
clean:
	$(RM) exec $(obj) $(obj:.o=.d)
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
