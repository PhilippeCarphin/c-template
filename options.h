#ifndef  _OPTIONS_H_
#define _OPTIONS_H_
/*
 * FIRST : Decide what your options are
 */
struct MyOpts;
int parse_args(int argc, char *argv[], struct MyOpts **opts);
#endif // _OPTIONS_H_
