#include <stdio.h>
#include <conio.h>
#include <math.h>
#include "tinyexpr.h"
#include "tinyexpr.c"
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
    //printf("\t%.6f\n",r);
    return r;
}

int bolzano(te_expr *f, double a, double b){
    return calcF1(f,a)*calcF1(f,b)<0 ? 1 : 0;
}

int posicaofalsamodificada(double e, int iMax, te_expr *f, double a, double b, int *k, double *r){ // errp, maxinteraçoes, func, [a b],k->interacao, raiz
    printf("\nPosicao falsa modificada");
	double x=0;
    double fx;
    double xp;
    int flag = 0;
    int flag2=0;
    int fixo=0; //flag de fixo
    if(!bolzano(f,a,b)){
        printf("\nO intervalo não converge...\n");
        return 1;
    }
    while(!flag && *k <= iMax){
        *k += 1;
        printf("\nInteracao %d",*k);
        printf("\nk = %d",*k);
        if(x) xp = x;
        else xp=a;
        if(flag2)
        {
        	if(!fixo)//fixo = a
        	{
        		printf("\t f(a) = f(a)/2");
        		x = (a*calcF1(f,b) - b*calcF1(f,a)/2)/(calcF1(f,b) - calcF1(f,a)/2); 

			}
        	else{
        		printf("\t f(b) = f(b)/2");
        		x = (a*calcF1(f,b)/2 - b*calcF1(f,a))/(calcF1(f,b)/2 - calcF1(f,a)); 
			}
		}
		else x = (a*calcF1(f,b) - b*calcF1(f,a))/(calcF1(f,b) - calcF1(f,a)); 
        //criando novo x;
        flag2=0;
        printf("\nx = %f",x);
        fx = calcF1(f,x);        
        printf("\n |f(x)| = |%f| ",fx);
        if(fabs(fx) < e) flag = 1; //fabs = modulo checar f(x)
	
        if(bolzano(f,a,x)){
            b = x; // se fa*fx < 0
            fixo = 0; // fixo = a
        }else{
            a = x; // se fa*fx > 0
            fixo = 1;//fixo = b
        }
        printf(" |b-a| = |%f|",fabs(b-a));
        if(fabs(b - a) < e) flag = 1; //|b-a| checar intervalo
		printf("\tXp = %f",xp);  
        if(calcF1(f,xp) * calcF1(f,x) > 0 )
        {
        	flag2 = 1;
		}
		printf("\t[a b] = [%f   %f]",a,b);
		 
	}
    *r = x;

    if(*k > iMax){
        printf("\nO número máximo de interações foi alcançado.\n");
        return 2;
    }
    
    return 0;
    
}


int main(){
    double r;
    int k;
    k = 0;
    k=0;    
    te_expr *f = verifica_gera_expr();
    posicaofalsamodificada(0.0001,10,f,0.21,0.6,&k,&r); 
    printf("\nResultado = %.6f",r);
    getch();
}
