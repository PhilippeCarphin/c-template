#define _DEFAULT_SOURCE
#include "options.h"


#define PHIL_DEBUG
#include "debug.h"
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>

#include "myapi.h"
/*
 * Here we are implementing the parse_args() function.  To do this, only a
 */
/*
 * couple of building blocks are necessary:
 * 1) Complete the struct option array, the short_opts string, and the
 * parse_option() funciton.
 * 2) Implement the parse_posargs function. 
 */

/*******************************************************************************
 * Option specififcation passed to getopt_long to specify the names and types of
 * your command line options
*******************************************************************************/
static struct option options[] = {
      // TODO : COMPLETE THIS
      // long name | has_args | flag | short name
		{ "help",         0,        0,      'h'},
		{ "type",         1,        0,      't'},
		{0,0,0,0}
	};

// TODO : COMPLETE THIS (a colon after means it takes an argument)
static char *short_opts = "ht:";

/*******************************************************************************
 * This function is driven by the parse_opts function that uses getopt_long.
 * It will call this function for each option on the command line.
*******************************************************************************/
static void show_usage();
static int parse_option(int opt, char *optarg, struct MyOpts *opts)
{
   // TODO : COMPLETE THIS
   switch(opt){
      case 'h':
         show_usage();
         break;
      case 't':
         if(strcmp(optarg, "float") == 0){
            opts->type = FLOATING;
         } else if (strcmp(optarg, "int") == 0){
            opts->type = INTEGER;
         } else {
            return -1;
         }
         break;
      default:
         fprintf(stderr, "Unknown option %c (%d)\n", opt, opt);
         show_usage();
         return -1;
         break;
   }

   return 0;
}
static void show_usage(){fprintf(stderr, "SHOW_USAGE TODO\n");}

/*******************************************************************************
 * In this section, you implement the parse_posargs function, you can do
 * whatever you want to do with them.  This is an example
*******************************************************************************/
// TODO : COMPLETE THIS
static int command(const char *command_name, enum Command *cmd);
static int parse_posargs(int posargc, char *posargv[], struct MyOpts *opts)
{
   if(posargc < 1){
      DBG_PRINT("==============================\n");
      DBG_PRINT("Error: No subcommand\n");
      return -1;
   }

   if(command(posargv[0], &(opts)->cmd)){
      DBG_PRINT("==============================\n");
      DBG_PRINT("Unknown command %s\n", posargv[1]);
      return -1;
   }

   opts->nb_elements = posargc - 1;
   opts->float_elements = malloc((posargc - 1) * sizeof(float));
   opts->int_elements = malloc((posargc - 1) * sizeof(int));
   for(int i = 1; i < posargc; ++i){
      switch(opts->type){
         case INTEGER:
            if(sscanf(posargv[i], "%d", &(opts->int_elements[i-1])) != 1){
               DBG_PRINT("==============================\n");
	       DBG_PRINT("sscanf failed\n");
               return -1;
            }
            break;
         case FLOATING:
            if(sscanf(posargv[i], "%f", &opts->float_elements[i-1]) != 1){
               DBG_PRINT("==============================\n");
	       DBG_PRINT("sscanf failed\n");
               return -1;
            }
            break;
         default:
            return -1;
      }
   }

   // Maybe do something with the other positionnal arguments
   return 0;
}
static int command(const char *command_name, enum Command *cmd)
{
   struct NameValue {const char *name; const int value;};// Library
   static struct NameValue cmd_value [] = {
      {"sum", SUM},
      {"product", PRODUCT},
      {NULL,0}
   };
   for(struct NameValue *nv = cmd_value; nv->name != NULL; nv++){
      if(strcmp(command_name, nv->name) == 0){
         *cmd = nv->value;
         return 0;
      }
   }
   return -1;
}


/*******************************************************************************
 * This can be seen as a driver for the for getopt_long that uses parse_option
 * and parse_posargs.  The exported function is parse_args
*******************************************************************************/
// You don't have to touch this.
static int parse_opts(int argc, char *argv[], struct MyOpts *opts, int *posargc, char ***posargv);
static int parse_posargs(int posargc, char *posargv[], struct MyOpts *opts);
int parse_args(int argc, char *argv[], struct MyOpts **opts)
{
   *opts = malloc(sizeof **opts);
   int posargc;
   char **posargv;
   int retval;
   if((retval = parse_opts(argc, argv, *opts, &posargc, &posargv))){
      DBG_PRINT("Error parsing options\n");
   }

   if((retval = parse_posargs(posargc, posargv, *opts))){
      DBG_PRINT("Error in parsing positionnal arguments\n");
   }
   return retval;
}
static int parse_opts(int argc, char *argv[], struct MyOpts *opts, int *posargc, char ***posargv)
{
	int opt;
	int index;
	while(( opt = getopt_long(argc, argv, short_opts, options, &index)) != -1 ){
      if(parse_option(opt, optarg, opts)){
         fprintf(stderr, "error parsing argument %s of option %c at index %d\n", optarg, opt, index);
      }
	}
   *posargc = argc - optind;
   *posargv = argv + optind;
   return 0;
}
