#include <stdio.h>
#include <conio.h>
#include "tinyexpr.h"





int main(){
    double x;
    te_variable vars[] = {{"x",&x}};
    int err;
    te_expr *ex = te_compile("x^2 + x",vars,1,&err);
    int i = 0;
    for(i = 0; i < 5; i++){
        x = i;
        printf("%.4f\n",te_eval(ex));
    }
    getch();
    te_free(ex);
    return 0;
}