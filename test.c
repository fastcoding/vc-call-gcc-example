#include "test.h"
#include <EXTERN.h>
#include <perl.h> 
void *start_perl (int argc, char **argv, char **env)
{
    PerlInterpreter *my_perl;
    char *embedding[] = { "", "-e", "0", NULL };
    PERL_SYS_INIT3(&argc,&argv,&env);
    my_perl = perl_alloc();
    perl_construct( my_perl );
 
    perl_parse(my_perl, NULL, 3, embedding, NULL);
    PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
    perl_run(my_perl);
    return my_perl;
}

void test_perl(){
    dTHX;
    /** Treat $a as an integer **/
    eval_pv("$a = 3; $a **= 2", TRUE);
    printf("a = %d\n", SvIV(get_sv("a", 0)));
 
    /** Treat $a as a float **/
    eval_pv("$a = 3.14; $a **= 2", TRUE);
    printf("a = %f\n", SvNV(get_sv("a", 0)));
 
    /** Treat $a as a string **/
    eval_pv(
      "$a = 'rekcaH lreP rehtonA tsuJ'; $a = reverse($a);", TRUE);
    printf("a = %s\n", SvPV_nolen(get_sv("a", 0)));
 
    /** create error and report **/
    eval_pv(
	"$a='created a sample exception';die $a",0);
    if (SvTRUE(ERRSV)){
	printf("detected error:%s\n",SvPV_nolen(ERRSV));
    }else{
	printf("die testing has no error\n");
    }
}
void shutdown_perl(void *perl){
    PerlInterpreter *my_perl=perl;
    perl_destruct(my_perl);
    perl_free(my_perl);
    PERL_SYS_TERM();
}
