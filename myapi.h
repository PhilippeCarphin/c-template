#ifndef _MY_MAIN_H
#define _MY_MAIN_H
struct MyOpts;
int my_main(struct MyOpts *opts);
enum Command { SUM, PRODUCT};
struct MyOpts {
   enum Command cmd;
   char *a_path;
   int nb_elements;
   char **elements;
};
#define TCL_API_NAME "my_api"
#define TCL_CMD_NAME "tcl_cmd_name"
#endif
