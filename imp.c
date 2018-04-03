#include <stdio.h>
#include <conio.h>
#include "tinyexpr.h"


int bissecao(double e, int iMax, te_expr *f, double a, double b, int *k, double *r, te_variable vars[]){
    int *x = vars[0].address;
    *x = a;
    double fa = te_eval(*f);
    *x = b;
    double fb = te_eval(*f);
}

int main(){

}