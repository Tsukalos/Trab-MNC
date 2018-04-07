#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include "tinyexpr.h"
#include "tinyexpr.c"

#define MAX 10
#define varsN 4
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

double calcFN(te_expr *f, double x[]){
    pX = x[0];
    pY = x[1];
    pZ = x[2];
    pW = x[3];
    double r = te_eval(f);
    return r;
}

int bolzano(te_expr *f, double a, double b){
    return calcF1(f,a)*calcF1(f,b)<0 ? 1 : 0;
}

double maxErr(double a){
    return (fabs(a)>=1) ? fabs(a) : 1;
}

double realdf1(double e, int iMax, te_expr *f, double x){
    int flag = 0;
    int k = 0;
    double fx, fant;
    double err, errant;
    double h = 2;
    while(!flag && k <= iMax){
        k++;
        h = h/2;
        fx = (calcF1(f,x+h)-calcF1(f,x-h))/(2*h);
        if(k>1){
            err = fabs(fx - fant)/maxErr(fx);
            if(err < e) flag = 1;
        }
        if(k > 2){
            if(err > errant) flag = 2;
            break;
        }
        errant = err;
        fant = fx;
    }
    if(flag == 2)
        return fant;
    return fx;
        
}

void copia_vetor(double a[], double x[], int n){
    int i;
    for(i = 0; i < n; i++){
        a[i] = x[i];
    }
}

double realNdf1(double e, int iMax, te_expr *f, double x[], int i, int N){
    int flag = 0;
    double ax1[varsN],ax2[varsN];
    int k = 0;
    double fx, fant;
    double err, errant;
    double h = 2;
    while(!flag && k <= iMax){
        copia_vetor(ax1,x,N);
        copia_vetor(ax2,x,N);
        k++;
        h = h/2;
        ax1[i]+=h;
        ax2[i]-=h;
        fx = (calcFN(f,ax1)-calcFN(f,ax2))/(2*h);
        if(k>1){
            err = fabs(fx - fant)/maxErr(fx);
            if(err < e) flag = 1;
        }
        if(k > 2){
            if(err > errant) flag = 2;
            break;
        }
        errant = err;
        fant = fx;
    }
    if(flag == 2)
        return fant;
    return fx;
        
}

double realdf2(double e, int iMax, te_expr *f, double x){
    int flag = 0;
    int k = 0;
    double fx, fant;
    double err, errant;
    double h = 2;
    double minus2fx = -2*calcF1(f,x);
    while(!flag && k <= iMax){
        k++;
        h = h/2;
        fx = (calcF1(f,x+(2*h))+minus2fx+calcF1(f,x-(2*h)))/(4*h*h);
        if(k>1){
            err = fabs(fx - fant)/maxErr(fx);

            if(err < e) flag = 1;
        }
        if(k > 2){
            if(err > errant) flag = 2;
            break;
        }
        errant = err;
        fant = fx;
    }
    if(flag == 2)
        return fant;
    return fx;
        
}

double realNdf2_1(double e, int iMax, te_expr *f, double x[], int i, int N){
    int flag = 0;
    double ax1[varsN],ax2[varsN];
    int k = 0;
    double fx, fant;
    double err, errant;
    double h = 2;
    double minus2fx = -2*calcFN(f,x);
    while(!flag && k <= iMax){
        copia_vetor(ax1,x,N);
        copia_vetor(ax2,x,N);
        k++;
        h = h/2;
        ax1[i]+=2*h;
        ax2[i]-=2*h;
        fx = (calcFN(f,ax1)+minus2fx+calcFN(f,ax2))/(4*h*h);
        if(k>1){
            err = fabs(fx - fant)/maxErr(fx);
            if(err < e) flag = 1;
        }
        if(k > 2){
            if(err > errant) flag = 2;
            break;
        }
        errant = err;
        fant = fx;
    }
    printf("\t%.8f\n",fx);
    if(flag == 2)
        return fant;
    return fx;
        
}

void set_df2_2_v(double a[], double b[], double c[], double d[], double h){
    a[0] += h;
    a[1] += h;

    b[0] += h;
    b[1] -= h;

    c[0] -= h;
    c[1] += h;

    d[0] -= h;
    d[1] -= h;
}

double realNdf2_2(double e, int iMax, te_expr *f, double x[], int N){
    int flag = 0;
    double ax1[varsN],ax2[varsN],ax3[varsN],ax4[varsN];
    int k = 0;
    double fx, fant;
    double err, errant;
    double h = 2;
    while(!flag && k <= iMax){
        copia_vetor(ax1,x,N);
        copia_vetor(ax2,x,N);
        copia_vetor(ax3,x,N);
        copia_vetor(ax4,x,N);
        k++;
        h = h/2;
        set_df2_2_v(ax1,ax2,ax3,ax4,h);
        fx = (calcFN(f,ax1)-calcFN(f,ax2)-calcFN(f,ax3)+calcFN(f,ax4))/(4*h*h);
        if(k>1){
            err = fabs(fx - fant)/maxErr(fx);
            if(err < e) flag = 1;
        }
        if(k > 2){
            if(err > errant) flag = 2;
            break;
        }
        errant = err;
        fant = fx;
    }
    if(flag == 2)
        return fant;
    return fx;
        
}

int jacobiano(double N, int eqN, te_expr *fv[], double x[], double m[][varsN]){
    double r;
    int i, j;
    for(i = 0; i < eqN; i++){
        te_expr *f = fv[i];
        for(j = 0; j < N; j++){
            m[i][j] = realNdf1(0.01,10,f,x,j,N);
        }
    }
}

void printM(double m[][varsN], int col, int lin){
    int i, j;
    for(i = 0; i < lin; i++){
        printf("\n");
        for(j = 0; j < col; j++){
            printf(" %.8f ",m[i][j]);
        }
    }
}

int newton(double e, int iMax, te_expr *f, double x, int *k, double *r){
    int flag = 0;
    double fx, dfx;
    double err;
    double xi, xant;
    *k = -1;
    xi = x;
    fx = calcF1(f,xi);
    printf("---//---//---");
    while(!flag && *k <= iMax){
        *k+=1;
        printf("\n[Interacao K = %d]",*k);
        dfx = realdf1(e,iMax,f,xi);
        xant = xi;
        xi = xi - (fx/dfx);
        printf("\n[x = \t%.8f]",xi);
        fx = calcF1(f,xi);
        if(fabs(fx)<e) flag = 1;
        printf("\n[|f(%.8f)| = \t|%.8f|]",xi,fx);
        err = fabs(xi - xant)/maxErr(xi);
        printf("\n[Erro = \t|%.8f|]",err);
        if(err < e) flag = 1;
        
        printf("\n");
    }
    *r = xi;
    return 0;
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
        printf("\n[|f(x)| = \t|%.8f|]",fx);
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

void pre_newton(){
    char ex[50];
    te_expr *f = verifica_gera_expr(ex);
    double r;
    int k;
    newton(0.001,10,f,7,&k,&r);
    printf("\n\nResult = %.8f",r);
    getch();
}

void teste_Ndf1(){
    char ex[50];
    te_expr *f = verifica_gera_expr(ex);
    double x[varsN] = {-1,1};
    printf("%.8f",realNdf2_1(0.01,10,f,x,2,2));
    getch();
}

void functionArrayGen(te_expr *f[], int N){
    int i;
    char s[50];
    for(i = 0; i < N; i++){
        f[i] = verifica_gera_expr(s);
    }
}


int main(){
    char ex[50];
    te_expr *f[MAX];
    functionArrayGen(f,3);
    double x[varsN] = {1,5};
    double m[MAX][varsN];
    jacobiano(2,3,f,x,m);
    printM(m,2,3);
    getch();
}