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
int my_main(struct MyOpts *opts){
   //...
   (void) opts;
   switch(opts->cmd){
      case SUM:
         return sum(opts);
      case PRODUCT:
         return product(opts);
   }

   return 0;
}

int sum(struct MyOpts *opts){
   switch(opts->type){
      case INTEGER:{
         int sum = 0;
         for(int i = 0; i < opts->nb_elements; i++){
            int j;
            if(sscanf(opts->elements[i], "%d", &j) != 1){
               return -1;
            }
            sum += j;
         }
         printf("SUM IS %d\n", sum);
                   }
         return 0;
      case FLOATING:{
         float sum = 0;
         for(int i = 0; i < opts->nb_elements; i++){
            float f;
            if(sscanf(opts->elements[i], "%f", &f) != 1){
               return -1;
            }
            sum += f;
         }
         printf("SUM IS %f\n", sum);
                    }
         return 0;
      default:
         return -1;
   }
};

int product(struct MyOpts *opts){
   switch(opts->type){
      case INTEGER:{
         int product = 1;
         for(int i = 0; i < opts->nb_elements; i++){
            int j;
            if(sscanf(opts->elements[i], "%d", &j) != 1){
               return -1;
            }
            product *= j;
         }
         printf("PRODUCT IS %d\n", product);
                   }
         return 0;
      case FLOATING:{
         float product = 1;
         for(int i = 0; i < opts->nb_elements; i++){
            float f;
            if(sscanf(opts->elements[i], "%f", &f) != 1){
               return -1;
            }
            product *= f;
         }
         printf("PRODUCT IS %f\n", product);
                    }
         return 0;
      default:
         return -1;
   }
};
