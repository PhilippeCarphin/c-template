/* And a main function whose job it is to get the command line argumnets, turn
 * them into a struct MyOpts and dispatch to the right command*/
#include "myapi.h"
#define PHIL_DEBUG
#include "debug.h"
#include "options.h"
int main(int argc, char * argv[])
{
   struct MyOpts *opts;

   if(parse_args(argc, argv, &opts)){
      DBG_PRINT("Error parsing\n");
      return -1;
   }

   int result = my_main(opts);
   if(result){
      DBG_PRINT("Error in execution\n");
   }

   return result;
}
