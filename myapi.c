#define PHIL_DEBUG

#include "debug.h"
#include <stdio.h>
#include "myapi.h"
#include "options.h"

/*
 * Responsible for turning parsed command line arguments into internal program
 * function calls
 */
int first_subroutine(struct MyOpts *opts);
int second_subroutine(struct MyOpts *opts);
int product(struct MyOpts *opts);
int product_float(struct MyOpts *opts){return -1;}
int product_int(struct MyOpts *opts){return -1;}
int sum(struct MyOpts *opts);
int sum_int(struct MyOpts *opts){return -1;}
int sum_float(struct MyOpts *opts){return -1;}
int my_main(struct MyOpts *opts)
{
   switch(opts->cmd){
      case SUM:
         return sum(opts);
      case PRODUCT:
         return product(opts);
      default:
	 return -1;
   }
}

int sum(struct MyOpts *opts){
   int int_sum = 0;
   float float_sum = 0;
   switch(opts->type){
      case INTEGER:
         for(int i = 0; i < opts->nb_elements; i++){
            int_sum += opts->int_elements[i];
         }
         printf("SUM IS %d\n", int_sum);
         return 0;
      case FLOATING:
         for(int i = 0; i < opts->nb_elements; i++){
            float_sum += opts->float_elements[i];
         }
         printf("SUM IS %f\n", float_sum);
         return 0;
      default:
         return -1;
   }
};

int product(struct MyOpts *opts){
   int int_product = 1;
   float float_product = 1;
   switch(opts->type){
      case INTEGER:
         for(int i = 0; i < opts->nb_elements; i++){
            int_product *= opts->int_elements[i];
         }
         printf("PRODUCT IS %d\n", int_product);
         return 0;
      case FLOATING:
         for(int i = 0; i < opts->nb_elements; i++){
            float_product *= opts->float_elements[i];
         }
         printf("PRODUCT IS %f\n", float_product);
         return 0;
      default:
         return -1;
   }
};
