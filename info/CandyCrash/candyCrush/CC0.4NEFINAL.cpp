#include <fstream>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <random>
using namespace std;
//n = dimensiunea matricii   t = matrice   S = scor total    a1,b1 = coordonatele alese(in consola)    a2,b2 = coordonatele cu care se schimba a1 si b1   stemp = scor pe miscarea curenta    miscari = numar de miscari ramase
int n=9,t[10][10],S,a1,b1,a2,b2,stemp,miscari;
// D = directie(N,S,E,V)
char D;
// na = nume pt high score
char na[50];
// lista cu scoruri
struct hs {int scor; char nume[10];}li[6];
void afisare(); /// arat tabla (!! poate facem cu mod grafic)
void process(int x,int y,bool dir); // sterge liniile care sunt minim 3 in a row
bool check(int i,int j,bool fa); // verifica daca t[i][j] face parte dintr-o secventa de minim 3 si o scoate daca fa==1
void getInput(); /// Input (!! poate facem cu click pe matrice direct)
void refill(bool fa); // reumple matricea
bool primitivecheck(); // vede daca in toata matricea exista un sir de minim 3 (!nu face cea mai buna mutare)
void genereaza(); // genereaza matricea
void joc(); // incepe un joc cu 10 mutari
void showscc(); // arata toate lista de high score (!vedem cu afisarea cum facem)
void highscore(); // arata high score si ia unul nou daca este cazul
void title(); //secventa de titlu (!nu e gata)

int main (){
    //read highscore.sav
    ifstream fin("highscore.sav");
    for(a2=1;a2<=5;a2++) {
        fin.getline(na,50);
        S=na[0]-'0';
        for(b2=2;b2<=S+1;b2++) li[a2].nume[b2-2]=na[b2];
        while (na[++b2]!=0) li[a2].scor=li[a2].scor*10+na[b2]-'0';
    }
    fin.close();
    //title();
    //jocul
    /*while (a1!=1337) {
            joc();
            if(a1==-1)
            a1=0;
            highscore();
        }*/
    joc();
    //end
    cout<<"Joc finalizat.";
    ofstream fout("highscore.sav");for(a2=1;a2<=5;a2++) fout<<strlen(li[a2].nume)<<" "<<li[a2].nume<<" "<<li[a2].scor<<'\n';
    fout.close();
}

void afisare (){
    int i,j;
    //Sleep(20);
    system("CLS");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
    cout<<"Date de intrare: linie coloana directie(N,S,V sau E)"<<'\n';
    cout<<"Scrie "<<-1<<" ca sa resetezi tabla"<<'\n';
    cout<<"Scrie "<<1337<<" ca sa inchizi jocul"<<'\n';
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
    cout<<"Score : "<<S<<"        Miscari ramase : "<<miscari<<'\n';
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout<<"   1 2 3 4 5 6 7 8 9"<<'\n';
    cout<<"   _________________"<<'\n';
    for(i=1; i<=n; i++)
    {
        cout<<i<<" |";
        for(j=1; j<=n; j++)
            switch (t[i][j]) {
            case 0: {cout<<"  "; break;}
            case 1: {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);cout<<(char) 233<<' '; break;}
            case 2: {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6); cout<<(char) 254<<' '; break;}
            case 3: {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4); cout<<(char) 234<<' '; break;}
            case 4: {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9); cout<<(char) 167<<' '; break;}
            }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        cout<<'|'<<'\n';
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
    bool x=1;
    while (x){
        cout<<"Fa miscarea la : ";
        cin>>a1;
        if(a1==-1) x=0;
        else if (a1==1337) x=0;
        else {
            cin>>b1>>D;
            switch(D) {
            case 'N' : a2=a1-1; b2=b1;    break;
            case 'n' : a2=a1-1; b2=b1;    break;
            case 'E' : a2=a1;   b2=b1+1;  break;
            case 'e' : a2=a1;   b2=b1+1;  break;
            case 'S' : a2=a1+1; b2=b1;    break;
            case 's' : a2=a1+1; b2=b1;    break;
            case 'V' : a2=a1;   b2=b1-1;  break;
            case 'v' : a2=a1;   b2=b1-1;  break;
            default : x=0;
            }
        if(x==1 && a2>=1 && a2<=n && b2>=1 && b2<=n && a1>=1 && a1<=n && b1>=1 && b1<=n) {x=0;swap(t[a1][b1],t[a2][b2]);afisare();Sleep(300);}
        else {afisare();cout<<"Miscare invalida."<<'\n'; x=1;}
        if(!x && !check(a2,b2,0) && !check(a1,b1,0))
            {swap(t[a1][b1],t[a2][b2]);afisare();cout<<"Miscare inutila."<<'\n'; x=1;}
        }
    }
//ReadConsoleInput(hin, &InputRecord, 1, &Events);
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
    int i,j;t[0][0]=-1;
    for(i=1; i<=n; i++) for(j=1; j<=n; j++) t[i][j]=rand()%4+1;
    while (primitivecheck()) refill();
}

void joc() {
    genereaza();
    S=0; miscari=10;
    while (miscari && a1!=1337 && a1!=-1){
        afisare();
        while (primitivecheck()) refill();
        getInput();
        check(a1,b1,1); check(a2,b2,1);
        miscari--;
    }
    afisare();
    if(!miscari){cout<<"MISCARI EPUIZATE"<<'\n';cout<<"APASA ORICE TASTA PENTRU A CONTINUA"<<'\n';_getch();}
}

void showsc() {
            system("CLS");
            cout<<"------------  HIGH SCORES  ------------"<<'\n';
            for(a2=1;a2<=5;a2++) {cout<<a2<<". "<<li[a2].nume;for(b2=4+strlen(li[a2].nume);b2<=35;b2++)cout<<" ";cout<<li[a2].scor<<'\n';}
}

void highscore() {
        showsc();
            for(a2=1;a2<=5;a2++)
                if(li[a2].scor<S) {
                    for (b2=4;b2>=1 && li[b2].scor<S;b2--) {swap(li[b2].scor,li[b2+1].scor);swap(li[b2].nume,li[b2+1].nume);}
                    li[a2].scor=S;
                    cout<<"NOU HIGH SCORE! SCRIE-TI NUMELE (MAXIM 9 LITERE): ";
                    cin.ignore();
                    cin.getline(li[a2].nume,10);
                    showsc();
                    ofstream fout("highscore.sav");for(a2=1;a2<=5;a2++) fout<<strlen(li[a2].nume)<<" "<<li[a2].nume<<" "<<li[a2].scor<<'\n';fout.close();
                    break;
                }
            cout<<"APASA ORICE TASTA PENTRU A CONTINUA"<<'\n';
            _getch();
}

void title() {
    cout<<"            __                __            "<<'\n';
    cout<<"           /   _ __  _| \\/   /   __ _  _ |_ "<<'\n';
    cout<<"           \\__(_|| |(_| /    \\__ | (_|_> | |"<<'\n';
    cout<<'\n';
    cout<<"                PROIECT REALIZAT DE"<<'\n';
    cout<<"                  APROFIREI ADRIAN"<<'\n';
    cout<<"                  BRASSAT ALEXANDRU"<<'\n';
    cout<<"                   GALATANU MARIO"<<'\n';
    cout<<'\n'<<"apasa orice tasta pentru a incepe";
    _getch();
}
