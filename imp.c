#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
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

void gotoxy(int x, int y)
{
  COORD c;
  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void quadro()
{
	int i;
	gotoxy(27,2);printf("  Trabalho 1 - MNC  ");
	gotoxy(2,2);printf("%c", 201);
	for(i=3; i<=18;i++) //eixo y
	{
		gotoxy(2,i);
		printf("%c", 186);
	}
	gotoxy(2,18);printf("%c", 200);
	
	gotoxy(69,2);printf("%c", 187);
	for(i=3; i<=18;i++)
	{
		gotoxy(69,i);
		printf("%c", 186);
	}
	gotoxy(69,18);printf("%c", 188);
	//eixo x
	for(i=3; i<=68;i++)
	{ //posi��o do titulo
		if(!(i>25&&i<48))
		{
		gotoxy(i,2);
		printf("%c", 205);
		}
	}
	
	for(i=3; i<=68;i++)
	{
		gotoxy(i,18);
		printf("%c", 205);
	}
}
//-------------------------------------------------------------------------------------------------------------------------
int escolher(){
	int opc;
	do{
		system("cls");
		system("COLOR B1");
		quadro();
		gotoxy(6,3);printf("Zero de Fun%c%ces e Diferencia%c%co",135,148,135,198);
		gotoxy(6,5);printf("Digite a op%c%co desejada:", 135,198);
		gotoxy(6,6);printf("1 - Bissec%c%co", 135,198);
		gotoxy(6,7);printf("2 - Posi%c%co Falsa", 135,198);
		gotoxy(6,8);printf("3 - Posi%c%co Falsa Modificada",135,198);
		gotoxy(6,9);printf("4 - Newton");
		gotoxy(6,10);printf("5 - Newton Modificado");
		gotoxy(6,11);printf("6 - Primeira Derivada");
		//gotoxy(6,12);printf("7 - Segunda Derivada");
		gotoxy(6,12);printf("7 - Jacobiano");
		gotoxy(6,13);printf("8 - Hessiana");
		gotoxy(6,14);printf("9 - Sobre");
		gotoxy(6,15);printf("10 - Sair");
		gotoxy(6,16);scanf("%d", &opc);
	}while(opc>10 || opc<1);
	return opc;
}
//-----------------------------------------------------------------------------------------------------------------------
void sobre()
{
	system("cls");
	system("COLOR 8E");
	fflush(stdin);
	char menu;
	quadro();
	gotoxy(10,3);printf("Cr%cditos: ", 130);
	gotoxy(10,5);printf("Trabalho de M%ctodos Num%cricos Computacionais", 130,130);
	gotoxy(10,7);printf("Desenvolvido por: ");
	gotoxy(10,8);printf("Pedro Henrique Nunes Barros     (171022548)");
	gotoxy(10,9);printf("Pedro Lamkowski dos Santos      (171021266)");
    gotoxy(10,10);printf("Tania Sanai Shimabukuro         (171025717)");
    gotoxy(10,12);printf("Deseja voltar ao menu? (s ou n) ");scanf("%c", &menu);
    if (menu == 'n' || menu =='N')
    {
    	system("cls");
    	system("COLOR A0");
    	quadro();
		gotoxy(18,9);printf("Obrigado por utilizar nosso sistema!\n\n\n\n\n\n\n\n");
		exit(3);
    }
    else{
    	system("cls");
	}
}
//---------------------Fun��es---------------------------------------------------------------------------------------------

double pX,pY,pZ,pW;

te_variable vars[] = {{"x",&pX},{"y",&pY},{"z",&pZ},{"w",&pW}};

void limpa(){
	system("cls");
	system("color 8E");
	quadro();
}

te_expr * verifica_gera_expr(char ex[]){
    int err = 1;
    char expr[50];
    te_expr * f;
    while(err){
    	limpa();
        gotoxy(6,4);printf("Digite uma fun%c%co matem%ctica v%clida:",135,198,160,160);
        gotoxy(6,5);gets(expr);
        f = te_compile(expr,vars,4,&err);
    }
    strcpy(ex,expr);
    return f; 
}

double pegaE(){
	double e;
	gotoxy(6,6);printf("Digite a precis%co (E): ", 198);
	gotoxy(6,7);scanf("%lf", &e);
	return e;
}

int pegaiMax(){
	int i;
	gotoxy(6,8);printf("Digite o m%cximo de itera%c%ces: ", 160,135,148);
	gotoxy(6,9);scanf("%d", &i);
	return i;
}

int numEq(){
	int i;
	gotoxy(6,4);printf("Digite o n%cmero de equa%c%ces: ", 130,135,148);
	gotoxy(6,5);scanf("%d", &i);
	return i;
}

int numVar(){
	int i;
	do{
		gotoxy(6,6);printf("Digite o n%cmero de vari%cveis (de 1 a 4): ", 130,160);
		gotoxy(6,7);scanf("%d", &i);
	}while(i<1 || i>4);
	return i;
}

int numVar2(){
	int i;
	do{
		gotoxy(6,4);printf("Digite o n%cmero de vari%cveis (de 1 a 4): ", 130,160);
		gotoxy(6,5);scanf("%d", &i);
	}while(i<1 || i>4);
	return i;
}

double pegaX(){
	double x;
	gotoxy(6,10);printf("Digite o valor inicial (X0): ");
	gotoxy(6,11);scanf("%lf", &x);
	return x;
}

double pegaA(){
	double a;
	gotoxy(6,4);printf("Digite o intervalo inicial: ");
	gotoxy(6,5);scanf("%lf", &a);
	return a;
}

double pegaB(){
	double b;
	gotoxy(6,6);printf("Digite o intervalo final: ");
	gotoxy(6,7);scanf("%lf", &b);
	return b;
}

void leVar(double *x, int nvar){
	int i,j=4;
	limpa();
	for(i=0;i<nvar;i++){
		gotoxy(6,j);printf("Valor da vari%cvel %d: ", 160, i);
		gotoxy(6,j+1);scanf("%lf", &x[i]);
		j+=2;
	}
}

double leVar2(double *x){
	gotoxy(6,10);printf("Digite o valor de X: ");
	gotoxy(6,11);scanf("%lf", &x);
	return x;
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
    double r,e;
    int i, j,iMax;
    limpa();
    e=pegaE();
    iMax=pegaiMax();
    for(i = 0; i < eqN; i++){
        te_expr *f = fv[i];
        for(j = 0; j < N; j++){
            m[i][j] = realNdf1(e,iMax,f,x,j,N);
        }
    }
}

int hessiana(double N, te_expr *f, double x[], double m[][varsN]){
    double r,e;
    int i, j,iMax;
    limpa();
    e=pegaE();
    iMax=pegaiMax();
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            if(i == j){
                m[i][j] = realNdf2_1(e,iMax,f,x,i,N);
            }else{
                m[i][j] = realNdf2_2(e,iMax,f,x,N);
            }
        }
    }
}

void printM(double m[][varsN], int col, int lin){
    int i, j, l=5,c=6;
    for(i = 0; i < lin; i++){
       // printf("\n");
        for(j = 0; j < col; j++){
            gotoxy(c,l);printf(" %.8f ",m[i][j]);
            c+=12;
        }
        c=6;
        l++;
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
    while(!flag && *k <= iMax){
        *k+=1;
        limpa();
        gotoxy(6,4);printf("[Interacao K = %d]",*k);
        dfx = realdf1(e,iMax,f,xi);
        xant = xi;
        xi = xi - (fx/dfx);
        gotoxy(6,5);printf("[x = \t%.8f]",xi);
        fx = calcF1(f,xi);
        if(fabs(fx)<e) flag = 1;
        gotoxy(6,6);printf("[|f(%.8f)| = \t|%.8f|]",xi,fx);
        err = fabs(xi - xant)/maxErr(xi);
        gotoxy(6,7);printf("[Erro = \t|%.8f|]",err);
        if(err < e) flag = 1;
        gotoxy(6,9);system("pause");
    }
    *r = xi;
    if(*k > iMax){
    	limpa();
        gotoxy(6,4);printf("O n%cmero m%cximo de intera%c%ces foi alcan%cado.",163,160,135,148,135);
        return 1;
    }
    return 0;
}

int newtonModificado(double e, int iMax, te_expr *f, double x, int *k, double *r){
    int flag = 0;
    double fx, dfx;
    double err;
    double xi, xant;
    *k = -1;
    xi = x;
    fx = calcF1(f,xi);
    dfx = realdf1(e,iMax,f,xi); //dfx fixo
    while(!flag && *k <= iMax){
        *k+=1;
        limpa();
        gotoxy(6,4);printf("[Interacao K = %d]",*k);
       // dfx = realdf1(e,iMax,f,xi); // n precisa disso pq será sempre a msm dfx
        xant = xi;
        xi = xi - (fx/dfx);
        gotoxy(6,5);printf("[x = \t%.8f]",xi);
        fx = calcF1(f,xi);
        if(fabs(fx)<e) flag = 1;
        gotoxy(6,6);printf("[|f(%.8f)| = \t|%.8f|]",xi,fx);
        err = fabs(xi - xant)/maxErr(xi);
        gotoxy(6,7);printf("[Erro = \t|%.8f|]",err);
        if(err < e) flag = 1;
    	gotoxy(6,9);system("pause");
    }
    *r = xi;
    if(*k > iMax){
    	limpa();
        gotoxy(6,4);printf("O n%cmero m%cximo de intera%c%ces foi alcan%cado.",163,160,135,148,135);
        return 1;
    }
    return 0;
}

int bissecao(double e, int iMax, te_expr *f, double a, double b, int *k, double *r){
    double x;
    double fx;
    int flag = 0;
    if(!bolzano(f,a,b)){
        gotoxy(6,4);printf("O intervalo n%co converge...",198);
        return 1;
    }
    //printf("---//---//---");
    while(!flag && *k <= iMax){
        *k += 1;
        limpa();
        gotoxy(6,4);printf("[Iteracao K = %d]",*k);
        gotoxy(6,5);printf("[Intervalo = [%.8f %.8f] ]",a,b);
        x = (a+b)/2;
        gotoxy(6,6);printf("[x = \t%.8f]",x);
        fx = calcF1(f,x);
        gotoxy(6,7);printf("[|f(x)| = \t|%.8f|]",fx);
        if(fabs(fx) < e) flag = 1;
        if(bolzano(f,a,x)){
            b = x; // se fa*fx < 0
        }else{
            a = x; // se fa*fx > 0
        }
        if(fabs(b - a) < e) flag = 1;
        gotoxy(6,9);system("pause");
    }

    *r = x;

    if(*k > iMax){
    	limpa();
        gotoxy(6,4);printf("O n%cmero m%cximo de intera%c%ces foi alcan%cado.",163,160,135,148,135);
        return 2;
    }
    
    return 0;
    
}

int posicaofalsa(double e, int iMax, te_expr *f, double a, double b, int *k, double *r){
    //printf("\nPosicao falsa");
	double x;
    double fx;
    int flag = 0;
    if(!bolzano(f,a,b)){
       gotoxy(6,4);printf("O intervalo n%co converge...",198);
        return 1;
    }
    while(!flag && *k <= iMax){
        *k += 1;
        limpa();
        gotoxy(6,4);printf("Interacao %d",*k);
        gotoxy(6,5);printf("k = %d",*k);
        x = (a*calcF1(f,b) - b*calcF1(f,a))/(calcF1(f,b) - calcF1(f,a)); //criando novo x;
        gotoxy(6,6);printf("x = %f",x);
        fx = calcF1(f,x);        
        gotoxy(6,7);printf("|f(x)| = |%f| ",fx);
        if(fabs(fx) < e) flag = 1; //fabs = modulo checar f(x)
	
        if(bolzano(f,a,x)){
            b = x; // se fa*fx < 0
        }else{
            a = x; // se fa*fx > 0
        }
        gotoxy(6,8);printf("|b-a| = |%f|",fabs(b-a));
        if(fabs(b - a) < e) flag = 1; //|b-a| checar intervalo   
        gotoxy(6,10);system("pause");
	}
    *r = x;

    if(*k > iMax){
    	limpa();
        gotoxy(6,4);printf("O n%cmero m%cximo de intera%c%ces foi alcan%cado.",163,160,135,148,135);
        return 2;
    }
    
    return 0;
    
}

int posicaofalsamodificada(double e, int iMax, te_expr *f, double a, double b, int *k, double *r){
    //printf("\nPosicao falsa modificada");
	double x=0;
    double fx;
    double xp;
    int flag = 0;
    int flag2=0;
    int fixo=0; //flag de fixo
    if(!bolzano(f,a,b)){
       gotoxy(6,4);printf("O intervalo n%co converge...",198);
        return 1;
    }
    while(!flag && *k <= iMax){
        *k += 1;
        limpa();
        gotoxy(6,4);printf("Interacao %d",*k);
        gotoxy(6,5);printf("k = %d",*k);
        if(x) xp = x;
        else xp=a;
        if(flag2)
        {
        	if(!fixo)//fixo = a
        	{
        		gotoxy(6,6);printf("f(a) = f(a)/2");
        		x = (a*calcF1(f,b) - b*calcF1(f,a)/2)/(calcF1(f,b) - calcF1(f,a)/2); 

			}
        	else{
        		gotoxy(6,6);printf("f(b) = f(b)/2");
        		x = (a*calcF1(f,b)/2 - b*calcF1(f,a))/(calcF1(f,b)/2 - calcF1(f,a)); 
			}
		}
		else x = (a*calcF1(f,b) - b*calcF1(f,a))/(calcF1(f,b) - calcF1(f,a)); 
        //criando novo x;
        flag2=0;
        gotoxy(6,7);printf("x = %f",x);
        fx = calcF1(f,x);        
        gotoxy(6,8);printf("|f(x)| = |%f| ",fx);
        if(fabs(fx) < e) flag = 1; //fabs = modulo checar f(x)
	
        if(bolzano(f,a,x)){
            b = x; // se fa*fx < 0
            fixo = 0; // fixo = a
        }else{
            a = x; // se fa*fx > 0
            fixo = 1;//fixo = b
        }
        gotoxy(6,9);printf("|b-a| = |%f|",fabs(b-a));
        if(fabs(b - a) < e) flag = 1; //|b-a| checar intervalo
		gotoxy(6,10);printf("Xp = %f",xp);  
        if(calcF1(f,xp) * calcF1(f,x) > 0 )
        {
        	flag2 = 1;
		}
		gotoxy(6,11);printf("[a b] = [%f   %f]",a,b);
		gotoxy(6,13);system("pause"); 
	}
    *r = x;

    if(*k > iMax){
    	limpa();
        gotoxy(6,4);printf("O n%cmero m%cximo de intera%c%ces foi alcan%cado.",163,160,135,148,135);
        return 2;
    }
    
    return 0;
    
}

void pre_bissecao(){
    char ex[50];
    te_expr *f = verifica_gera_expr(ex);
    double r,e,a,b;
    int k,iMax,aux;
    k = 0;
    e=pegaE();
    iMax=pegaiMax();
    limpa();
    a=pegaA();
    b=pegaB();
    limpa();
    aux=bissecao(e,iMax,f,a,b,&k,&r);
    if(!aux){
	    //gotoxy(6,4);printf("%s",ex);
	    gotoxy(6,11);printf("M%ctodo Bissec%c%co",130,135,198);
		gotoxy(6,12);printf("Itera%c%ces: %d",135,148,k);
	    gotoxy(6,13);printf("Raiz aproximada: %.8f",r);
	}
    getch();
}

void pre_posicaofalsa(){
    char ex[50];
    te_expr *f = verifica_gera_expr(ex);
    double r,e,a,b;
    int k,iMax,aux;
    k = 0;
    e=pegaE();
    iMax=pegaiMax();
    limpa();
    a=pegaA();
    b=pegaB();
    limpa();
    aux=posicaofalsa(e,iMax,f,a,b,&k,&r);
    if(!aux){
	    //gotoxy(6,4);printf("%s",ex);
	    gotoxy(6,12);printf("M%ctodo Posi%c%co Falsa",130,135,198);
		gotoxy(6,13);printf("Itera%c%ces: %d",135,148,k);
	    gotoxy(6,14);printf("Raiz aproximada: %.8f",r);
	}
    getch();
}

void pre_posicaofalsamodificada(){
    char ex[50];
    te_expr *f = verifica_gera_expr(ex);
    double r,e,a,b;
    int k,iMax,aux;
    k = 0;
    e=pegaE();
    iMax=pegaiMax();
    limpa();
    a=pegaA();
    b=pegaB();
    limpa();
    aux=posicaofalsamodificada(e,iMax,f,a,b,&k,&r);
    if(!aux){
	    //gotoxy(6,4);printf("%s",ex);
	    gotoxy(6,15);printf("M%ctodo Posi%c%co Falsa Modificada",130,135,198);
		gotoxy(6,16);printf("Itera%c%ces: %d",135,148,k);
	    gotoxy(6,17);printf("Raiz aproximada: %.8f",r);
	}
    getch();
}

void pre_newton(){
    char ex[50];
    te_expr *f = verifica_gera_expr(ex);
    double r,e,x;
    int k,iMax,aux;
     e=pegaE();
    iMax=pegaiMax();
    x=pegaX();
    limpa();
    aux=newton(e,iMax,f,x,&k,&r);
	if(!aux){
	    gotoxy(6,11);printf("M%ctodo Newton",130);
		gotoxy(6,12);printf("Itera%c%ces: %d",135,148,k);
	    gotoxy(6,13);printf("Raiz aproximada: %.8f",r);
	}
    getch();
}

void pre_newtonModificado(){
    char ex[50];
    te_expr *f = verifica_gera_expr(ex);
    double r,e,x;
    int k,iMax,aux;
     e=pegaE();
    iMax=pegaiMax();
    x=pegaX();
    limpa();
    aux=newtonModificado(e,iMax,f,x,&k,&r);
    if(!aux){
	    gotoxy(6,11);printf("M%ctodo Newton Modificado",130);
		gotoxy(6,12);printf("Itera%c%ces: %d",135,148,k);
	    gotoxy(6,13);printf("Raiz aproximada: %.8f",r);
	}
    getch();
}

void teste_Ndf1(){
    char ex[50];
    te_expr *f = verifica_gera_expr(ex);
    int nvar,iMax;
    double e;
    limpa();
    e=pegaE();
    iMax=pegaiMax();
    double x;
    leVar2(&x);
    limpa();
    gotoxy(6,4);printf("Derivada Primeira");
    gotoxy(6,5);printf("f1 = %.8f",realdf1(e,iMax,f,x));
    getch();
}

void functionArrayGen(te_expr *f[], int N){
    int i;
    char s[50];
    for(i = 0; i < N; i++){
        f[i] = verifica_gera_expr(s);
    }
}

void pre_jacob(){
    char ex[50];
    te_expr *f[MAX];
    int neq,nvar;
    limpa();
    neq=numEq();
    nvar=numVar();
    functionArrayGen(f,neq); // 3 é o número de eqs
    double x[varsN];
    leVar(x,nvar); 
    double m[MAX][varsN];
    jacobiano(nvar,neq,f,x,m); // 2 é o tamanho do vetor x
    limpa();
    gotoxy(6,4);printf("Matriz Jacobiana");
    printM(m,nvar,neq);
    getch();
}

void pre_hessiana(){
    char ex[50];
    te_expr *f = verifica_gera_expr(ex);
    int nvar;
    limpa();
    nvar=numVar();
    double x[varsN];
    leVar(x,nvar);
    double m[MAX][varsN];
    hessiana(nvar,f,x,m); // 2 aqui é tamanho do vetor x
    limpa();
    gotoxy(6,4);printf("Matriz Hessiana");
    printM(m,nvar,nvar);
    getch();
}
//-------------------------------------------------------------------------------------------------------------------------------------
int main(){
	//pre_newtonModificado();
	char resp;
	int opcao;
	system("cls");
	system("color 5F");
	quadro();
	opcao = escolher();
	switch(opcao){
		case 1:  do{
					limpa();
					pre_bissecao();
					do{
						limpa();
						gotoxy(13,10);printf("Deseja realizar uma nova opera%c%co? (S/N)", 135, 198);
						scanf("%s", &resp);
						resp=tolower(resp);
					}while(resp!='s' && resp!='n');
					
				}while(resp=='s');
				main();
				break;
		
		case 2: do{
					limpa();
					pre_posicaofalsa();
					do{
						limpa();
						gotoxy(13,10);printf("Deseja realizar uma nova opera%c%co? (S/N)", 135, 198);
						scanf("%s", &resp);
						resp=tolower(resp);
					}while(resp!='s' && resp!='n');
					
				}while(resp=='s');
				main();
				break;
		case 3: do{
					limpa();
					pre_posicaofalsamodificada();
					do{
						limpa();
						gotoxy(13,10);printf("Deseja realizar uma nova opera%c%co? (S/N)", 135, 198);
						scanf("%s", &resp);
						resp=tolower(resp);
					}while(resp!='s' && resp!='n');
					
				}while(resp=='s');
				main();
				break;
		case 4:  do{
					limpa();
					pre_newton();
					do{
						limpa();
						gotoxy(13,10);printf("Deseja realizar uma nova opera%c%co? (S/N)", 135, 198);
						scanf("%s", &resp);
						resp=tolower(resp);
					}while(resp!='s' && resp!='n');
					
				}while(resp=='s');
				main();
				break;
		case 5:  do{
					limpa();
					pre_newtonModificado();
					do{
						limpa();
						gotoxy(13,10);printf("Deseja realizar uma nova opera%c%co? (S/N)", 135, 198);
						scanf("%s", &resp);
						resp=tolower(resp);
					}while(resp!='s' && resp!='n');
					
				}while(resp=='s');
				main();
				break;
		case 6: do{
					limpa();
					teste_Ndf1();
					do{
						limpa();
						gotoxy(13,10);printf("Deseja realizar uma nova opera%c%co? (S/N)", 135, 198);
						scanf("%s", &resp);
						resp=tolower(resp);
					}while(resp!='s' && resp!='n');
					
				}while(resp=='s');
				main();break;
		case 7:  do{
					limpa();
					pre_jacob();
					do{
						limpa();
						gotoxy(13,10);printf("Deseja realizar uma nova opera%c%co? (S/N)", 135, 198);
						scanf("%s", &resp);
						resp=tolower(resp);
					}while(resp!='s' && resp!='n');
					
				}while(resp=='s');
				main();
				break;
		case 8:  do{
					limpa();
					pre_hessiana();
					do{
						limpa();
						gotoxy(13,10);printf("Deseja realizar uma nova opera%c%co? (S/N)", 135, 198);
						scanf("%s", &resp);
						resp=tolower(resp);
					}while(resp!='s' && resp!='n');
					
				}while(resp=='s');
				main();
				break;
		case 9: sobre();
				main();
				break;
		case 10: system("cls");
				system("color A0");
				quadro();
				gotoxy(18,9);printf("Obrigado por utilizar nosso sistema!\n\n\n\n\n\n\n\n");
				break;
	}
}
