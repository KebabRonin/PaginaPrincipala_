#include <fstream>
#include <iostream>
#include <time.h>
#include "graphics.h"
using namespace std;
//n = dimensiunea matricii; t = matrice; S = scor total; stemp = scor pe miscarea curenta; x = string pentru afisare; mult = multiplier pt score;
int n=9,t[15][15],S,stemp,miscari=10,mult=2,poly[10]; char x[300];
struct hs{int scor; char nume[15];}li[15];
///joc
void joc(); // incepe un joc cu 10 mutari
///editare matrice
void process(int x,int y,bool dir); // sterge liniile care sunt minim 3 in a row
int check(int i,int j,bool fa); // verifica daca t[i][j] face parte dintr-o secventa de minim 3 si o scoate daca fa==1 AICI SE ADAUGA SCORUL
void refill(); // reumple matricea
bool primitivecheck(); // vede daca in toata matricea exista un sir de minim 3
bool bestcheck(int i,int j); // cea mai buna mutare pentru primitivecheck
///meta
void genereaza(); // genereaza matricea
void getInput(); // Input
int trurand(); // genereaza chestii random
void updatescor();
void updatemiscari();
void showsc(); // afiseaza leaderbordul
void highscore(); // pune high score nou in leader board
void title();
///desene
void boardinit(); // deseneaza bg o data la inceput
void afisare(); // arat elementele matricii
void drawtitle(); // secventa de titlu
///fructe
void triunghi(int a,int b);
void gogoasa(int a,int b);
void patrat(int a,int b);
void cerc(int a,int b);
void nimic(int a,int b);
void sel(int a,int b);

int main (){
    //read highscore.sav
    ifstream fin("highscore.sav");
    for(stemp=1;stemp<=5;stemp++) fin>>li[stemp].scor>>li[stemp].nume;
    fin.close();
    initwindow(700,800);
    title();
    closegraph();
    return 0;
}

///joc
void joc() {
    cleardevice();
    genereaza();
    S=0; miscari=10;
    boardinit();
    do {
        afisare();
        do refill(); while (primitivecheck()) ;
        getInput();
        miscari--; updatemiscari();
    } while (miscari>0);
    do refill(); while (primitivecheck()) ;
    setcolor(WHITE);
    if(miscari==0) strcpy(x,"MISCARI EPUIZATE. APASA CLICK PENTRU A CONTINUA");
    else return;
    outtextxy(1,30,x);
    while (1) if(ismouseclick(WM_LBUTTONDOWN)) break;
}

///editare matrice
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

int check(int i,int j,bool fa){
    int Sv=0,Sl=0,k=1;
    if(t[i][j]<=0) return 0;
    k=1;stemp=0;
    while(t[i][j]==t[i+k][j] && i+k<=n){Sv++;k++;}k=1;
    while(t[i][j]==t[i-k][j] && i-k>=1){Sv++;k++;}
    k=1;
    while(t[i][j]==t[i][j+k] && j+k<=n){Sl++;k++;}k=1;
    while(t[i][j]==t[i][j-k] && j-k>=1){Sl++;k++;}
    if(fa) {
        if(Sv>=2) process(i,j,0);
        if(Sl>=2) process(i,j,1);
        S+=stemp*mult; updatescor();
    }
    if(Sv>=2 || Sl>=2) {if(fa) t[i][j]=0; return Sv+Sl;}
    return 0;
}

void refill() {
    int i,j,k;
    for(j=1;j<=n;j++)
    for(i=n;i>=1;i--) {k=i;
        while (t[k][j]!=0 && t[k+1][j]==0 && k<9) {swap(t[k+1][j],t[k][j]);k++; afisare();}
        while (t[1][j]==0) {
                t[1][j]=trurand(); k=1; afisare();
                while (k<9 && t[k+1][j]==0) {swap(t[k][j],t[k+1][j]);k++; afisare();}
        }
    }
}

bool primitivecheck(){
    int i,j;bool nr;
    for(i=1; i<=n; i++) for(j=1; j<=n; j++) if(t[i][j]==0 || bestcheck(i,j)) nr=1;
    return nr;
}

bool bestcheck(int i,int j) {
    int k=1,scor=check(i,j,0);
    if(scor) {
        if(t[i][j]<=0) return 0;
        k=1;
        while(t[i][j]==t[i+k][j] && k!=0 && i+k<=n){if(scor<check(i+k,j,0)) {i=i+k;k=-1;} k++;} if(k==-1) {check(i,j,1); return 1;}
        k=1;
        while(t[i][j]==t[i-k][j] && k!=0 && i-k>=1){if(scor<check(i-k,j,0)) {i=i-k;k=-1;} k++;} if(k==-1) {check(i,j,1); return 1;}
        k=1;
        while(t[i][j]==t[i][j+k] && k!=0 && j+k<=n){if(scor<check(i,j+k,0)) {j=j+k;k=-1;} k++;} if(k==-1) {check(i,j,1); return 1;}
        k=1;
        while(t[i][j]==t[i][j-k] && k!=0 && j-k>=1){if(scor<check(i,j-k,0)) {j=j-k;k=-1;} k++;} if(k==-1) {check(i,j,1); return 1;}
        check(i,j,1);
        return 1;
    }
    return 0;
}

///meta
void getInput(){
    bool f=1;
    int x1,x2,y1,y2;
    clearmouseclick(WM_LBUTTONDOWN);
    setcolor(WHITE);
    strcpy(x,"Apasa pe itemele pe care vrei sa le muti");
    outtextxy(120,665,x);
    while (f){
        if(ismouseclick(WM_LBUTTONDOWN)) {
            x1 = mousex();
            y1 = mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            if(y1>650 && y1<700 && x1>64 && x1<114) {miscari=-1;return;}
            else {
                x1/=64; y1/=64;
                if (y1>=1 && y1<=n && x1>=1 && x1<=n){
                    sel(x1,y1);
                    while (1)
                    if (ismouseclick(WM_LBUTTONDOWN)) {
                        x2 = mousex();
                        y2 = mousey();
                        clearmouseclick(WM_LBUTTONDOWN);
                        if(y2>650 && y2<700 && x2>64 && x2<114) {miscari=-1; return;}
                        else {
                            x2/=64; y2/=64;
                            if (y2>=1 && y2<=n && x2>=1 && x2<=n){
                            if(f==1 && abs(x1-x2)+abs(y1-y2)==1) {
                                f=0;
                                swap(t[y1][x1],t[y2][x2]);
                                afisare();
                                Sleep(100);
                                if(!f && !check(y2,x2,0) && !check(y1,x1,0)) {
                                    swap(t[y1][x1],t[y2][x2]);
                                    afisare();
                                    setcolor(GREEN);
                                    rectangle(120,650,600,667);
                                    setfillstyle(SOLID_FILL,BLACK);
                                    floodfill(121,651,GREEN);
                                    setcolor(BLACK);
                                    rectangle(120,650,600,667);
                                    setcolor(WHITE);
                                    strcpy(x,"MISCARE INUTILA");
                                    outtextxy(120,650,x);
                                    f=1;
                                    break;
                                    }
                                else {
                                    mult=2;
                                    check(y1,x1,1); check(y2,x2,1); afisare();
                                    mult=1;
                                    setcolor(GREEN);
                                    rectangle(120,650,600,667);
                                    setfillstyle(SOLID_FILL,BLACK);
                                    floodfill(121,651,GREEN);
                                    setcolor(BLACK);
                                    rectangle(120,650,600,667);
                                    return;
                                }
                            }
                            else {break;}
                            }
                            else {afisare();setcolor(GREEN);
                                    rectangle(120,650,600,667);
                                    setfillstyle(SOLID_FILL,BLACK);
                                    floodfill(121,651,GREEN);
                                    setcolor(BLACK);
                                    rectangle(120,650,600,667);setcolor(WHITE);strcpy(x,"MISCARE INVALIDA");outtextxy(120,650,x); f=1; break;}
                        }
                    }
                }
            }
        }
    }

}

void genereaza(){
    int i,j,k;t[0][0]=-1;
    for(i=1; i<=n; i++) for(j=1; j<=n; j++) t[i][j]=trurand();
    while (primitivecheck())
    //refill fara afisare
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

int trurand() {
    time_t time0;
    time(&time0);
    return (rand()+(int)time0)%4+1;
}

void updatescor() {
    setcolor(WHITE);
    strcpy(x,"        ");
    outtextxy(60,3,x);
    itoa(S, x, 10);
    outtextxy(60,3,x);
}

void updatemiscari() {
    if(miscari>-1) {
        setcolor(WHITE);
        strcpy(x,"        ");
        outtextxy(580,3,x);
        itoa(miscari, x, 10);
        outtextxy(580,3,x);
    }
}

void showsc() {
    int i;
    system("CLS");
    strcpy(x,"------------  HIGH SCORES  ------------");
    outtextxy(225,300,x);
    for(i=1;i<=5;i++) {
        itoa(i,x,10);outtextxy(225,300+i*30,x);
        strcpy(x,".");outtextxy(235,300+i*30,x);
        strcpy(x,li[i].nume);outtextxy(245,300+i*30,x);
        itoa(li[i].scor,x,10);outtextxy(400,300+i*30,x);
    }
}

void highscore() {
    int i,j=-1;
    drawtitle();
    for(i=1;i<=5;i++)
        if(li[i].scor<S) {
            setcolor(WHITE);
            strcpy(x,"NOU HIGH SCORE! SCRIE-TI NUMELE (MAXIM 10 LITERE)");
            outtextxy(150,540,x); x[0]='\0';
            do {
                x[200]=getch();
                if(x[200]==8) {
                    x[j--]='\0';
                    outtextxy(250,560,"                       ");
                    }
                else if(x[200]=='\r') break;
                else if(j<9) {x[++j]=x[200]; x[j+1]='\0';}
                if(j<-1) j=-1;
                outtextxy(250,560,x);
            }while(1);
            for (j=4;j>=1 && li[j].scor<S;j--) swap(li[j],li[j+1]);
            if(x[0]==0) strcpy(x,"guest");
            li[i].scor=S; strcpy(li[i].nume,x);
            drawtitle();
            strcpy(x,"BRAVO!!!");
            outtextxy(150,540,x);
            ofstream fout("highscore.sav");for(i=1;i<=5;i++) fout<<li[i].scor<<" "<<li[i].nume<<'\n';fout.close();
            break;
        }
}

void title() {
    int x1,y1;
    drawtitle(); //desenez titlul
    while(1)
        if(ismouseclick(WM_LBUTTONDOWN)) { //daca dau click
            x1 = mousex(); y1 = mousey(); //pozitia mouse
            clearmouseclick(WM_LBUTTONDOWN);
            if(y1>200 && y1<220 && x1>220 && x1<420) {joc(); if(miscari==-2) return; else {drawtitle(); highscore();}} //buton start
            else if(y1>650 && y1<700 && x1>64 && x1<114) return; //buton exit
        }
}
///desene
void boardinit () {
    updatemiscari();updatescor();
    setcolor(WHITE);
    rectangle(60,60,644,644);
    setfillstyle(SOLID_FILL,WHITE);
    floodfill(61,61,WHITE);
    setcolor(RED);
    rectangle(64,650,114,700);
    setfillstyle(SOLID_FILL,RED);
    floodfill(65,651,RED);
    setcolor(WHITE);
    strcpy(x,"EXIT");
    outtextxy(75,667,x);
    strcpy(x,"SCOR : ");
    outtextxy(3,3,x);
    strcpy(x,"MISCARI RAMASE : ");
    outtextxy(450,3,x);
}

void afisare (){
    int i,j;
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=n; j++)
            switch (t[i][j]) {
            case 0: {nimic(i,j);break;}
            case 1: {cerc(i,j); break;}
            case 2: {patrat(i,j); break;}
            case 3: {triunghi(i,j); break;}
            case 4: {gogoasa(i,j); break;}
            }
    }
}

void drawtitle() {
    setfillstyle(SOLID_FILL,BLACK);
    floodfill(1,1,YELLOW);
    strcpy(x,"            __                  __            ");     outtextxy(200,50,x);
    strcpy(x,"           /    _ __  _| \\/   /   __     _ |_ ");    outtextxy(200,66,x);
    strcpy(x,"           \\__(_|| |(_| /    \\__ |  |_|_> | |");    outtextxy(200,82,x);
    strcpy(x,"                PROIECT REALIZAT DE");                outtextxy(200,114,x);
    strcpy(x,"                  APROFIREI ADRIAN");                 outtextxy(200,130,x);
    strcpy(x,"                BRASSAT ALEXANDRU");                  outtextxy(200,146,x);
    showsc(); // scor
    setcolor(RED);
    rectangle(64,650,114,700);
    setfillstyle(SOLID_FILL,RED);
    floodfill(65,651,RED);
    setcolor(WHITE);
    strcpy(x,"EXIT");
    outtextxy(75,667,x);
    setcolor(BLUE);
    rectangle(260,200,420,220);
    setfillstyle(SOLID_FILL,BLUE);
    floodfill(261,201,BLUE);
    setcolor(WHITE);
    strcpy(x,"INCEPE JOCUL");
    outtextxy(292,202,x);
}

///fructe
void triunghi(int b,int a) {
    a=a*64; b=b*64;
    setcolor(GREEN);
    line(a+60,b+60,a+5,b+60);
    line(a+60,b+60,a+32,b+5);
    line(a+5,b+60,a+32,b+5);
    setfillstyle(SOLID_FILL,GREEN);
    floodfill(a+32,b+32,GREEN);
    //delete bg
    setcolor(GREEN);
    rectangle(a,b,a+64,b+64);
    setfillstyle(SOLID_FILL,WHITE);
    floodfill(a+1,b+1,GREEN);
    setcolor(WHITE);
    rectangle(a,b,a+64,b+64);
}

void cerc(int b,int a) {
    a=a*64; b=b*64;
    setcolor(CYAN);
    circle(a+32,b+32,30);
    setfillstyle(SOLID_FILL,CYAN);
    floodfill(a+32,b+32,CYAN);
    //delete bg
    setcolor(CYAN);
    rectangle(a,b,a+63,b+63);
    setfillstyle(SOLID_FILL,WHITE);
    floodfill(a+1,b+1,CYAN);
    setcolor(WHITE);
    rectangle(a,b,a+63,b+63);
}

void patrat(int b,int a) {
    a=a*64; b=b*64;
    setcolor(BLUE);
    rectangle(a+5,b+5,a+58,b+58);
    setfillstyle(SOLID_FILL,BLUE);
    floodfill(a+32,b+32,BLUE);
    //delete bg
    setcolor(BLUE);
    rectangle(a,b,a+63,b+63);
    setfillstyle(SOLID_FILL,WHITE);
    floodfill(a+1,b+1,BLUE);
    setcolor(WHITE);
    rectangle(a,b,a+63,b+63);
}

void gogoasa(int b,int a) {
    a=a*64; b=b*64;
    setcolor(RED);
    circle(a+32,b+32,30);
    circle(a+32,b+32,15);
    setfillstyle(SOLID_FILL,RED);
    floodfill(a+49,b+32,RED);
    setfillstyle(SOLID_FILL,WHITE);
    floodfill(a+32,b+32,RED);
    //delete bg
    setcolor(RED);
    rectangle(a,b,a+63,b+63);
    setfillstyle(SOLID_FILL,WHITE);
    floodfill(a+1,b+1,RED);
    setcolor(WHITE);
    rectangle(a,b,a+63,b+63);
}

void nimic(int b,int a) {
    a=a*64; b=b*64;
    setcolor(BLACK);
    rectangle(a,b,a+63,b+63);
    setfillstyle(SOLID_FILL,WHITE);
    floodfill(a+1,b+1,BLACK);
    setcolor(WHITE);
    rectangle(a,b,a+63,b+63);
}

void sel(int a,int b) {
    a=a*64; b=b*64;
    setcolor(BLACK);
    rectangle(a+2,b+2,a+61,b+61);
}
