#include <stdio.h>
#include <conio.h>
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

te_expr * verifica_gera_expr(){
    int err = 1;
    char expr[50];
    te_expr *f;
    while(err){
        printf("\nDigite uma funcao matemarica valida:\n");
        gets(expr);
        f = te_compile(expr,vars,4,&err);
    }
    return f; 
}

double calcF1(te_expr *f, double x){
    pX = x;
    double r = te_eval(f);
    printf("\t%.6f\n",r);
    return r;
}

int bolzano(te_expr *f, double a, double b){
    return calcF1(f,a)*calcF1(f,b)<0 ? 1 : 0;
}


int bissecao(double e, int iMax, te_expr *f, double a, double b, int *k, double *r){
    double x;
    double fx;
    int flag = 0;
    if(!bolzano(f,a,b)){
        printf("\nO intervalo não converge...\n");
        return 1;
    }
    while(!flag && *k <= iMax){
        *k += 1;
        x = (a+b)/2; //criando novo x;
        fx = calcF1(f,x);
        if(fabs(fx) < e) flag = 1;
        if(bolzano(f,a,x)){
            b = x; // se fa*fx < 0
        }else{
            a = x; // se fa*fx > 0
        }
        if(fabs(b - a) < e) flag = 1;
    }

    *r = x;

    if(*k > iMax){
        printf("\nO número máximo de interações foi alcançado.\n");
        return 2;
    }
    
    return 0;
    
}



int posicaofalsa(double e, int iMax, te_expr *f, double a, double b, int *k, double *r){ // errp, maxinteraçoes, func, [a b],k->interacao, raiz
    double x;
    double fx;
    int flag = 0;
    if(!bolzano(f,a,b)){
        printf("\nO intervalo não converge...\n");
        return 1;
    }
    while(!flag && *k <= iMax){
        *k += 1;
        x = (a*calcF1(f,b) - b*calcF1(f,a))/(calcF1(f,b) - calcF1(f,a)); //criando novo x;
        fx = calcF1(f,x);
        if(fabs(fx) < e) flag = 1; //fabs = modulo checar f(x)
        if(bolzano(f,a,x)){
            b = x; // se fa*fx < 0
        }else{
            a = x; // se fa*fx > 0
        }
        if(fabs(b - a) < e) flag = 1; //|b-a| checar intervalo
    }

    *r = x;

    if(*k > iMax){
        printf("\nO número máximo de interações foi alcançado.\n");
        return 2;
    }
    
    return 0;
    
}


int main(){
    //te_expr *f = verifica_gera_expr();
    double r;
    int k;
    k = 0;/*
    bissecao(0.01,10,f,1.5,2.8,&k,&r);    
    printf("%.5f",r);*/
    k=0;    
    te_expr *f = verifica_gera_expr();
    posicaofalsa(0.0001,10,f,-0.3,0.25,&k,&r);
    printf("%.5f",r);
    getch();
}
