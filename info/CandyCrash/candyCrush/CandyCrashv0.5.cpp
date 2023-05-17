#include <iostream>
#include "graphics.h"
using namespace std;
//n = dimensiunea matricii   t = matrice   S = scor total    a1,b1,a2,b2 = coordonate   stemp = scor pe miscarea curenta
int n=9,t[10][10],S,stemp,miscari;
void board(); // deseneaza bg
void afisare(); // arat tabla
void process(int x,int y,bool dir); // sterge liniile care sunt minim 3 in a row
bool check(int i,int j,bool fa); // verifica daca t[i][j] face parte dintr-o secventa de minim 3 si o scoate daca fa==1
void getInput(); // Input
void refill(bool fa); // reumple matricea
bool primitivecheck(); /// vede daca in toata matricea exista un sir de minim 3 (!nu face cea mai buna mutare)
void genereaza(); // genereaza matricea
void joc(); // incepe un joc cu 10 mutari
void title(); ///secventa de titlu (!nu e gata)
///desene (!!!)
void triunghi(int a,int b);
void gogoasa(int a,int b);
void patrat(int a,int b);
void cerc(int a,int b);

int main (){
    initwindow(700,800);
    title();
    joc();
    //no end message!
    closegraph();
    return 0;
}

void board () {
    char buffer[11] = {0};
    setcolor(WHITE);
    rectangle(60,60,644,644);
    setfillstyle(SOLID_FILL,WHITE);
    floodfill(61,61,WHITE);
    setcolor(RED);
    rectangle(64,650,114,700);
    setfillstyle(SOLID_FILL,RED);
    floodfill(65,651,RED);
    setcolor(WHITE);
    outtextxy(75,667,"EXIT");
    outtextxy(3,3,"SCOR : ");
    itoa(S, buffer, 10);
    outtextxy(60,3,buffer);
    outtextxy(450,3,"MISCARI RAMASE : ");
    itoa(miscari, buffer, 10);
    outtextxy(580,3,buffer);
}

void afisare (){
    int i,j;
    Sleep(20);
    cleardevice();
    board();
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=n; j++)
            switch (t[i][j]) {
            case 0: {break;}
            case 1: {cerc(i,j); break;}
            case 2: {patrat(i,j); break;}
            case 3: {triunghi(i,j); break;}
            case 4: {gogoasa(i,j); break;}
            }
    }
}

void process(int x,int y,bool dir){
    //0 = vertical;  1 = orizontal;
    int k,s=0;
    if(dir==0){k=1;
        while (t[x][y]==t[x+k][y] && x+k<=n)
            {t[x+k][y]=0;s++;k++;}k=1;
        while (t[x][y]==t[x-k][y] && x-k>=1)
        {t[x-k][y]=0;s++;k++;}
        }
    else {
        k=1;
        while (t[x][y]==t[x][y+k] && y+k<=n)
            {t[x][y+k]=0;s++;k++;}k=1;
        while (t[x][y]==t[x][y-k] && y-k>=1)
            {t[x][y-k]=0;s++;k++;}
    }
    stemp+=(s+1);
}

bool check(int i,int j,bool fa){
    int Sv=0,Sl=0,k=1;
    if(t[i][j]<=0) return 0;
    k=1;stemp=0;
    while(t[i][j]==t[i+k][j] && i+k<=n){Sv++;k++;}k=1;
    while(t[i][j]==t[i-k][j] && i-k>=1){Sv++;k++;}
    if(fa && Sv>=2) {process(i,j,0);}
    k=1;
    while(t[i][j]==t[i][j+k] && j+k<=n){Sl++;k++;}k=1;
    while(t[i][j]==t[i][j-k] && j-k>=1){Sl++;k++;}
    if(fa && Sl>=2) {process(i,j,1);}
    if(fa && (Sv>=2 || Sl>=2))t[i][j]=0;
    if(fa) S+=stemp;
    if(Sv>=2 || Sl>=2) return 1;
    return 0;
}

void getInput(){
    bool f=1;
    int x1,x2,y1,y2;
    clearmouseclick(WM_LBUTTONDOWN);
    while (f){
        setcolor(WHITE);
        outtextxy(120,665,"Apasa pe itemele pe care vrei sa le muti");
        if(ismouseclick(WM_LBUTTONDOWN)) {
            x1 = mousex();
            y1 = mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            if(y1>650 && y1<700 && x1>64 && x1<114) {miscari=1;f=0;break;}
            else {
                x1/=64; y1/=64;
                if (y1>=1 && y1<=n && x1>=1 && x1<=n){
                    while (1)
                    if (ismouseclick(WM_LBUTTONDOWN)) {
                        x2 = mousex();
                        y2 = mousey();
                        clearmouseclick(WM_LBUTTONDOWN);
                        if(y2>650 && y2<700 && x2>64 && x2<114) {miscari=1;f=0;break;}

                        else {
                            x2/=64; y2/=64;
                            if (y2>=1 && y2<=n && x2>=1 && x2<=n){
                            if(f==1 && abs(x1-x2)+abs(y1-y2)==1) {
                                f=0;
                                swap(t[y1][x1],t[y2][x2]);
                                afisare();
                                Sleep(100);
                            }
                            else {afisare();setcolor(WHITE);outtextxy(120,650,"MISCARE INVALIDA"); f=1;}
                            if(!f && !check(y2,x2,0) && !check(y1,x1,0))
                                {
                                    swap(t[y1][x1],t[y2][x2]);
                                    afisare();
                                    setcolor(WHITE);
                                    outtextxy(120,650,"MISCARE INUTILA");
                                    f=1;
                                    }
                        }}
                        break;
                    }
                }
            }
        }
    }
    check(y1,x1,1); check(y2,x2,1);
}

void refill() {
    int i,j,k;
    for(j=1;j<=n;j++)
    for(i=n;i>=1;i--) {k=i;
        while (t[k][j]!=0 && t[k+1][j]==0 && k<9) {swap(t[k+1][j],t[k][j]);k++; afisare();}
        while (t[1][j]==0) {
                t[1][j]=rand()%4+1; k=1; afisare();
                while (k<9 && t[k+1][j]==0) {swap(t[k][j],t[k+1][j]);k++; afisare();}
        }
    }
}

bool primitivecheck(){
    int i,j;
    for(i=1; i<=n; i++) for(j=1; j<=n; j++) if(t[i][j]==0 || check(i,j,1)) return 1;
    return 0;
}

void genereaza(){
    int i,j,k;t[0][0]=-1;
    for(i=1; i<=n; i++) for(j=1; j<=n; j++) t[i][j]=rand()%4+1;
    while (primitivecheck())
    //basically refill
    {for(j=1;j<=n;j++)
    for(i=n;i>=1;i--) {k=i;
        while (t[k][j]!=0 && t[k+1][j]==0 && k<9) {swap(t[k+1][j],t[k][j]);k++;}
        while (t[1][j]==0) {
                t[1][j]=rand()%4+1; k=1;
                while (k<9 && t[k+1][j]==0) {swap(t[k][j],t[k+1][j]);k++;}
        }
    }
    }
}

void joc() {
    genereaza();
    S=0; miscari=10;
    while (miscari){
        afisare();
        do refill(); while (primitivecheck()) ;
        getInput();
        miscari--;
    }
    afisare();
    setcolor(WHITE);
    outtext("MISCARI EPUIZATE. APASA CLICK PENTRU A CONTINUA");
    while (1)if(ismouseclick(WM_LBUTTONDOWN)) break;
}

void title() {
    outtext("Apasa o tasta");
    while(!kbhit());
}

//putpixel(1,1,GREEN) putimage,Setbkcolor
void triunghi(int b,int a) {
    a=a*64; b=b*64;
    setcolor(GREEN);
    circle(a+32,b+32,30);
    setfillstyle(SOLID_FILL,GREEN);
    floodfill(a+32,b+32,GREEN);
}

void cerc(int b,int a) {
    a=a*64; b=b*64;
    setcolor(CYAN);
    circle(a+32,b+32,30);
    setfillstyle(SOLID_FILL,CYAN);
    floodfill(a+32,b+32,CYAN);
}

void patrat(int b,int a) {
    a=a*64; b=b*64;
    setcolor(BLUE);
    circle(a+32,b+32,30);
    setfillstyle(SOLID_FILL,BLUE);
    floodfill(a+32,b+32,BLUE);
}

void gogoasa(int b,int a) {
    a=a*64; b=b*64;
    setcolor(RED);
    circle(a+32,b+32,30);
    circle(a+32,b+32,15);
    setfillstyle(SOLID_FILL,RED);
    floodfill(a+49,b+32,RED);
}
