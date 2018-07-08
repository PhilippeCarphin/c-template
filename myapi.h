#ifndef _MY_API_H_
#define _MY_API_H_
/*
** TODO Write this struct to reflect what information could be passed from the command line
*/
struct MyOpts;
int my_main(struct MyOpts *opts);
enum Command { SUM, PRODUCT};
enum Type { INTEGER, FLOATING };
struct MyOpts {
   enum Command cmd;
   char *a_path;
   enum Type type;
   int nb_elements;
   float *float_elements;
   int *int_elements;
};
#define TCL_API_NAME "my_api"
#define TCL_CMD_NAME "api_cmd"
#endif // _MY_API_H_
