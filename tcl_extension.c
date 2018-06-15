#ifdef TCL
#include <tcl.h>
#include "myapi.h"
#include "options.h"
#include "debug.h"
// ref http://wiki.tcl.tk/11153

/* With this file, no extra code required, you can make your program a TCL
 * extension.
 */
static int tcl_print_args(int objc, Tcl_Obj *const objv[]){
    for(int i=0; i<objc; ++i){
        DBG_PRINT("C : Tcl_GesString(objv[%d])=%s\n",i, Tcl_GetString(objv[i]));
    }
    return 0;
}

/*
 * TCL adapter: runs TCL commands the same way as if they were on the command
 * line.
 */
static int tcl_extension_callback(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
   (void) cdata;
   (void) interp;

   struct MyOpts *opts;

   /*
    * Parse the arguments
    */
   char *argv[objc];
   for(int i = 0; i < objc; ++i){
      argv[i] = Tcl_GetString(objv[i]);
   }
   if(parse_args(objc, argv, &opts)){
      // tell TCL
      return TCL_ERROR;
   }

   return my_main(opts);
}

int Myapi_Init(Tcl_Interp *interp)
{
    FUNCBEGIN
    if(Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL){
        return TCL_ERROR;
    }

    if(Tcl_PkgProvide(interp, TCL_API_NAME, "1.0") == TCL_ERROR){
        return TCL_ERROR;
    }

    Tcl_CreateObjCommand(interp, TCL_CMD_NAME, tcl_extension_callback, NULL, NULL);

    FUNCEND
    return TCL_OK;
}
#endif
