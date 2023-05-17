#include <fstream>
#include <iostream>
#include <time.h>
#include <conio.h>
#include "graphics.h"
using namespace std;
//n = dimensiunea matricii; t = matrice; S = scor total; stemp = scor pe miscarea curenta; x = string pentru afisare; mult = multiplier pt score;
int n=9,t[15][15],S,stemp,miscari,mult=2,poly[10]; char x[300];
struct hs{int scor; char nume[15];}li[15];
///joc
void joc(); // incepe un joc cu 10 mutari
///editare matrice
void plusbum(int i,int j); // miscare speciala
void testspecial(int i,int j); // testeaza legaturile cu elementele speciale
void process(int x,int y,bool dir); // sterge liniile care sunt minim 3 in a row
int check(int i,int j,bool fa); // verifica daca t[i][j] face parte dintr-o secventa de minim 3 si o scoate daca fa==1 AICI SE ADAUGA SCORUL
void refill(); // reumple matricea
bool primitivecheck(); // vede daca in toata matricea exista un sir de minim 3
bool bestcheck(int i,int j); // cea mai buna mutare pentru primitivecheck
///meta
bool buton(int X1,int X2,int Y1,int Y2,void f(void),int x,int y);
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
void corona(int a,int b);
void nimic(int a,int b);
void sel(int a,int b);

int main (){
    //read highscore.sav
    ifstream fin("highscore.sav");
    for(stemp=1;stemp<=5;stemp++) {fin>>li[stemp].scor; fin.getline(li[stemp].nume,15); strcpy(li[stemp].nume,li[stemp].nume+1);}
    fin.close();
    initwindow(700,800);
    title();
    closegraph();
    return 0;
}

///joc
void joc() {
    cleardevice();
    time_t time0;
    time(&time0);
    srand(mousex()+mousey()+(int)time0);
    genereaza();
    S=0; miscari=1;
    boardinit();
    while(miscari>0) {
        afisare();
        do refill(); while (primitivecheck()) ;
        getInput();
        miscari--; updatemiscari();
    }
    do refill(); while (primitivecheck()) ;
    setcolor(WHITE);
    if(miscari==0) strcpy(x,"MISCARI EPUIZATE. APASA CLICK PENTRU A CONTINUA");
    else return;
    setfillstyle(0,BLACK);
    bar(150,310,550,370);outtextxy(170,330,x);
    while (1) if(ismouseclick(WM_LBUTTONDOWN)) break;
    clearmouseclick(WM_LBUTTONDOWN);
}

///editare matrice
void plusbum(int i,int j) {
    int k;
    S+=5; t[i][j]=0;
    for(k=1;k<=n;k++) { S+=t[i][k]+t[j][k];if(t[i][k]==5) plusbum(i,k); if(t[k][j]==5) plusbum(k,j);t[i][k]=t[k][j]=0;}
}

void testspecial(int i,int j,int &Sl,int &Sv) {
    int L,V,k; Sl=Sv=0;
    for(int l=1;l<5;l++) {
        L=V=0;
        k=1;
        while(l==t[i+k][j] && i+k<=n){V++;k++;}k=1;
        while(l==t[i-k][j] && i-k>=1){V++;k++;}
        k=1;
        while(l==t[i][j+k] && j+k<=n){L++;k++;}k=1;
        while(l==t[i][j-k] && j-k>=1){L++;k++;}
        if(L>=2 || V>=2) {Sv=V; Sl=L;}
    }
}

void process(int x,int y,bool dir){
    //0 = vertical;  1 = orizontal;
    int k,s=0,h=t[x][y];
    if(dir==0){k=1;
        while (h==t[x+k][y] && x+k<=n)
            {t[x+k][y]=0;s++;k++;}k=1;
        while (h==t[x-k][y] && x-k>=1)
        {t[x-k][y]=0;s++;k++;}
        }
    else {
        k=1;
        while (h==t[x][y+k] && y+k<=n)
            {t[x][y+k]=0;s++;k++;}k=1;
        while (h==t[x][y-k] && y-k>=1)
            {t[x][y-k]=0;s++;k++;}
    }
    //afisare();
    stemp+=(s+1);
}

int check(int i,int j,bool fa){
    int Sv=0,Sl=0,k=1;
    if(t[i][j]<=0) return 0;
    k=1;stemp=0;
    if(t[i][j]<5) {
    while(t[i][j]==t[i+k][j] && i+k<=n){Sv++;k++;}k=1;
    while(t[i][j]==t[i-k][j] && i-k>=1){Sv++;k++;}
    k=1;
    while(t[i][j]==t[i][j+k] && j+k<=n){Sl++;k++;}k=1;
    while(t[i][j]==t[i][j-k] && j-k>=1){Sl++;k++;}
    }
    else testspecial(i,j,Sl,Sv);
    if(fa) {
        if(Sv>=2) process(i,j,0);
        if(Sl>=2) process(i,j,1);
        S+=stemp*mult;
        if(Sv>=2 || Sl>=2) {if(t[i][j]==5) plusbum(i,j); t[i][j]=0;}
        if(Sl>=2 && Sv>=2)
            {S+=5; t[i][j]=5;}
        updatescor();//afisare();
    }
    if(Sv>=2 || Sl>=2) return Sv+Sl;
    return 0;
}

void refill() {
    int i,j,k; bool ok=1;
    while(ok) {ok=0;
        for(j=1;j<=n;j++) {
            for(i=n;i>=1;i--) {k=i;
                if(t[i][j]==0) {ok=1;
                    while(k>0){swap(t[k][j],t[k-1][j]);k--;}
                    if(k!=i){t[1][j]=trurand();break;}
                }
            }
        }
        afisare();
    }
}

bool primitivecheck(){
    int i,j;bool nr=0;
    for(i=1; i<=n; i++) for(j=1; j<=n; j++) if(t[i][j]==0 || bestcheck(i,j)) nr=1;
    afisare(); Sleep(10);
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
bool buton(int X1,int X2,int Y1,int Y2,void f(void),int x,int y) {
    if(x>X1 && x<X2 && y>Y1 && y<Y2) {f(); return 1;}
    return 0;
}

void ext() {
    exit(0);
}

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
            //if(y1>650 && y1<700 && x1>64 && x1<114) {miscari=-1;return;}
            if(buton(64,114,650,700,ext,x1,y1));
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
                            if (y2>=1 && y2<=n && x2>=1 && x2<=n && abs(x1-x2)+abs(y1-y2)==1){
                            if(f==1) {
                                f=0;
                                swap(t[y1][x1],t[y2][x2]);
                                afisare();
                                Sleep(100);
                                if(!f && !check(y2,x2,0) && !check(y1,x1,0)) {
                                    swap(t[y1][x1],t[y2][x2]);
                                    afisare();
                                    setfillstyle(SOLID_FILL,RED);
                                    bar(120,650,600,667);
                                    setcolor(WHITE);
                                    strcpy(x,"MISCARE IVALIDA");
                                    outtextxy(120,650,x);
                                    f=1;
                                    break;
                                    }
                                else {
                                    mult=2;
                                    if(t[y1][x1]==5) plusbum(y1,x1);
                                    else check(y1,x1,1);
                                    if(t[y2][x2]==5) plusbum(y2,x2);
                                    else check(y2,x2,1);
                                     afisare();
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
                                    setcolor(RED);
                                    rectangle(120,650,600,667);setcolor(WHITE);strcpy(x,"MISCARE INVALIDA");outtextxy(120,650,x); f=1; break;}
                        }
                    }
                }
            }
        }
    }

}

void genereaza(){//refill fara afisare
    int i,j;t[0][0]=-1;
    for(i=1; i<=n; i++) for(j=1; j<=n; j++) t[i][j]=trurand();
    while (primitivecheck()) refill();
    t[0][0]=1;
}

int trurand() {
    time_t time0;
    time(&time0);
    return (mousex()+mousey()+rand()+(int)time0)%4+1;
}

void updatescor() {
    setcolor(WHITE);
    strcpy(x,"        ");
    outtextxy(160,22,x);
    itoa(S, x, 10);
    if(S>li[5].scor) {setcolor(YELLOW); strcat (x," HS");}
    outtextxy(160,22,x);
}

void updatemiscari() {
    if(miscari>-1) {
        setcolor(WHITE);
        strcpy(x,"    ");
        outtextxy(568,22,x);
        itoa(miscari, x, 10);
        outtextxy(568,22,x);
    }
}

void showsc() {
    int i;
    system("CLS");
    strcpy(x,"------------  HIGH SCORES  ------------");
    outtextxy(250,300,x);
    for(i=1;i<=5;i++) {
        itoa(i,x,10);outtextxy(250,300+i*30,x);
        strcpy(x,".");outtextxy(260,300+i*30,x);
        strcpy(x,li[i].nume);outtextxy(270,300+i*30,x);
        itoa(li[i].scor,x,10);outtextxy(400,300+i*30,x);
    }
}

void highscore() {
    int i,j=-1;
    drawtitle();
    for(i=1;i<=5;i++)
        if(li[i].scor<S) {
            setcolor(WHITE);
            strcpy(x,"NOU HIGH SCORE! Scrie-ti numele:");
            outtextxy(236,480,x); x[0]='\0';
            while(x[200]!='\r'){
                x[200]=getch();
                if(x[200]==8) {
                    x[j--]='\0';
                    outtextxy(310,495,"                          ");
                    }
                //else if(x[200]=='\r') break;
                else if(j<9 && x[200]>31) {x[++j]=x[200]; x[j+1]='\0';}
                if(j<-1) j=-1;
                outtextxy(310,495,x);
            }
            for (j=4;j>=1 && li[j].scor<S;j--) swap(li[j],li[j+1]);
            if(x[0]==0) strcpy(x,"guest");
            li[i].scor=S; strcpy(li[i].nume,x);
            drawtitle();
            strcpy(x,"BRAVO!!!");
            outtextxy(310,480,x);
            ofstream fout("highscore.sav");for(i=1;i<=5;i++) fout<<li[i].scor<<" "<<li[i].nume<<'\n';fout.close();
            break;
        }
}

void title() {
    int x1,y1;
    drawtitle(); //desenez titlul
    clearmouseclick(WM_LBUTTONDOWN);
    while(1)
        if(ismouseclick(WM_LBUTTONDOWN)) { //daca dau click
            x1 = mousex(); y1 = mousey(); //pozitia mouse
            clearmouseclick(WM_LBUTTONDOWN);//(250,270,450,190)
            //if(y1>190 && y1<270 && x1>250 && x1<450)
            if(buton(250,450,190,270,joc,x1,y1)) {/*if(miscari==-2) return; else {*/clearmouseclick(WM_LBUTTONDOWN); drawtitle(); highscore();/*}*/} //buton start
            //else if(y1>650 && y1<700 && x1>64 && x1<114) return; //buton exit
            buton(64,114,650,700,ext,x1,y1); //buton exit
        }
}

///desene
void boardinit () {

    updatemiscari(); updatescor(); readimagefile("bg.jpg",0,0,700,800);
    setcolor(YELLOW);
    rectangle(60,60,644,644);
    setfillstyle(SOLID_FILL,YELLOW);
    floodfill(61,61,YELLOW);
    setcolor(RED);
    rectangle(64,650,114,700);
    setfillstyle(SOLID_FILL,RED);
    floodfill(65,651,RED);
    setcolor(WHITE);
    strcpy(x,"EXIT");
    outtextxy(75,667,x);
    strcpy(x,"SCOR :");
    outtextxy(110,22,x);
    strcpy(x,"MISCARI RAMASE :");
    outtextxy(440,22,x);
    updatemiscari(); updatescor();
}

void afisare (){
    int i,j;
    if(t[0][0]==-1) return;
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=n; j++)
            switch (t[i][j]) {
            case 0: {nimic(i,j);break;}
            case 1: {cerc(i,j); break;}
            case 2: {patrat(i,j); break;}
            case 3: {triunghi(i,j); break;}
            case 4: {gogoasa(i,j); break;}
            case 5: {corona(i,j); break;}
            }
    }
    //Sleep(10);
}

void drawtitle() {
    setfillstyle(SOLID_FILL,BLACK); bar(0,0,800,800);
    readimagefile("tit.jpg",1,1,700,800);
    showsc(); // scor
    setfillstyle(1,RED);
    bar(64,650,114,700);
    setcolor(WHITE);
    strcpy(x,"EXIT");
    outtextxy(75,667,x);
    //setfillstyle(BLUE);
    //bar(250,270,450,190);
    setcolor(WHITE);
    strcpy(x,"INCEPE JOCUL");
    outtextxy(302,223,x);
}

///fructe
void triunghi(int b,int a) {
    a=a*64; b=b*64;
    readimagefile("mar.jpg",a+1,b+1,a+62,b+62);
}

void cerc(int b,int a) {
    a=a*64; b=b*64;
    readimagefile("capsuna.jpg",a+1,b+1,a+62,b+62);
}

void patrat(int b,int a) {
    a=a*64; b=b*64;
    readimagefile("porto.jpg",a+1,b+1,a+62,b+62);
}

void gogoasa(int b,int a) {
    a=a*64; b=b*64;
    readimagefile("struguri.jpg",a+1,b+1,a+62,b+62);
}

void corona(int b,int a) {
    a=a*64; b=b*64;
    readimagefile("coro.jpg",a+1,b+1,a+62,b+62);
}

void nimic(int b,int a) {
    a=a*64; b=b*64;
    readimagefile("nica.jpg",a+1,b+1,a+62,b+62);
}

void sel(int a,int b) {
    a=a*64; b=b*64;
    setcolor(BLUE);
    rectangle(a+1,b+1,a+62,b+62);    rectangle(a+2,b+2,a+61,b+61);    rectangle(a+3,b+3,a+60,b+60);    rectangle(a+4,b+4,a+59,b+59);
}
/*
 - getch() gets special characters (see arrows and del)
 - chacacters inputed before highscore() call will still load in name string
 - afisare sometimes skips a beat in refill
 - blank screen before game
*/
