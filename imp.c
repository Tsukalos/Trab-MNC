#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include "tinyexpr.h"
/*
*   Vários tipos de função podem ser escritos usando tinyexpr
*   Para a implementação do método, podem ser escritas funções usando variáveis x,y,z,w
*   Exemplos:
*       x^2 - x^3 + 30
*       sin(x+y)
*/
double pX,pY,pZ,pW;

te_variable vars[] = {{"x",&pX},{"y",&pY},{"z",&pZ},{"w",&pW}};

te_expr * verifica_gera_expr(char ex[]){
    int err = 1;
    char expr[50];
    te_expr * f;
    while(err){
        printf("\nDigite uma funcao matemarica valida:\n");
        gets(expr);
        f = te_compile(expr,vars,4,&err);
    }
    strcpy(ex,expr);
    return f; 
}

double calcF1(te_expr *f, double x){
    pX = x;
    double r = te_eval(f);
    return r;
}

int bolzano(te_expr *f, double a, double b){
    return calcF1(f,a)*calcF1(f,b)<0 ? 1 : 0;
}

double maxErr(double a){
    return (fabs(a)>=1) ? a : 1;
}

double realdf1(double e, int iMax, te_expr *f, double x){
    int flag = 0;
    int k = 0;
    double fx, fant;
    double err, errant;
    double h = 2;
    printf("---//---//---");
    while(!flag && k <= iMax){
        k++;
        h = h/2;
        printf("\n[Interacao K = %d / h = %.5f",k,h);
        fx = (calcF1(f,x+h)-calcF1(f,x-h))/(2*h);
        printf("\n[dF(x)/x = \t%.8f]",fx);
        if(k>1){
            err = fabs(fx - fant)/maxErr(fx);
            printf("\n[Erro = \t%.8f]",err);
            if(err < e) flag = 1;
        }
        if(k > 2){
            if(err > errant) flag = 1;
        }
        errant = err;
        fant = fx;
        printf("\n\n");
    }
    return fx;
        
}


int bissecao(double e, int iMax, te_expr *f, double a, double b, int *k, double *r){
    double x;
    double fx;
    int flag = 0;
    if(!bolzano(f,a,b)){
        printf("\nO intervalo não converge...\n");
        return 1;
    }
    printf("---//---//---");
    while(!flag && *k <= iMax){
        *k += 1;
        printf("\n[Interacao K = %d]",*k);
        printf("\n[Intervalo = [%.8f %.8f] ]",a,b);
        x = (a+b)/2;
        printf("\n[x = \t%.8f]",x);
        fx = calcF1(f,x);
        printf("\n[f(x) = \t%.8f]",fx);
        if(fabs(fx) < e) flag = 1;
        if(bolzano(f,a,x)){
            b = x; // se fa*fx < 0
        }else{
            a = x; // se fa*fx > 0
        }
        if(fabs(b - a) < e) flag = 1;
        printf("\n");
    }

    *r = x;

    if(*k > iMax){
        printf("\nO número máximo de interações foi alcançado.\n");
        return 2;
    }
    
    return 0;
    
}

void pre_bissecao(){
    char ex[50];
    te_expr *f = verifica_gera_expr(ex);
    double r;
    int k;
    k = 0;
    bissecao(0.01,10,f,1.5,2.8,&k,&r);
    printf("\n\n%s\n",ex);
    printf("\n%.8f",r);
    getch();
}

int main(){
    char ex[50];
    te_expr *f = verifica_gera_expr(ex);
    double r;
    r = realdf1(0.01,10,f,4);
    printf("\n\nResult = %.8f",r);
    getch();
}