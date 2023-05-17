#include "graphics2.h"
#include <windows.h>
#include <math.h>
#include <iostream>
#define sq sqrt(2)
using namespace std;

int r,gd,gm,cx,cy, N,color,ok,g,rm,mi;
char p;
void CercImparte(int xc,int yc,int r,int n) {
    if (kbhit()) p = getch();
    if(n<=N && p!='t' && r>=1) {
    Sleep(g);
    circle(xc,yc,r-r/(1+sq));
	CercImparte(xc,yc,r-r/(1+sq),n+1);
    r=r/(1+sq);
    if (ok==2) setcolor(n);
    if (ok==1) setcolor(++color%15);
    circle(xc,yc-r-r*sq+r/(1+sq),r/(1+sq));
	CercImparte(xc,yc-r-r*sq+r/(1+sq),r/(1+sq),n+1);
	if (ok==2) setcolor(n);
	if (ok==1) setcolor(++color%15);
	circle(xc+r*sq,yc-r*sq,r/(1+sq));
	CercImparte(xc+r*sq,yc-r*sq,r/(1+sq),n+1);
	if (ok==2) setcolor(n);
	if (ok==1) setcolor(++color%15);
	circle(xc+r+r*sq-r/(1+sq),yc,r/(1+sq));
	CercImparte(xc+r+r*sq-r/(1+sq),yc,r/(1+sq),n+1);
	if (ok==2) setcolor(n);
	if (ok==1) setcolor(++color%15);
	circle(xc+r*sq,yc+r*sq,r/(1+sq));
	CercImparte(xc+r*sq,yc+r*sq,r/(1+sq),n+1);
	if (ok==2) setcolor(n);
	if (ok==1) setcolor(++color%15);
	circle(xc,yc+r+r*sq-r/(1+sq),r/(1+sq));
	CercImparte(xc,yc+r+r*sq-r/(1+sq),r/(1+sq),n+1);
	if (ok==2) setcolor(n);
	if (ok==1) setcolor(++color%15);
	circle(xc-r*sq,yc+r*sq,r/(1+sq));
	CercImparte(xc-r*sq,yc+r*sq,r/(1+sq),n+1);
	if (ok==2) setcolor(n);
	if (ok==1) setcolor(++color%15);
	circle(xc-r-r*sq+r/(1+sq),yc,r/(1+sq));
	CercImparte(xc-r-r*sq+r/(1+sq),yc,r/(1+sq),n+1);
	if (ok==2) setcolor(n);
	if (ok==1) setcolor(++color%15);
	circle(xc-r*sq,yc-r*sq,r/(1+sq));
	CercImparte(xc-r*sq,yc-r*sq,r/(1+sq),n+1);
    }
}

int main()
{
    cout<<"Raza cercului mare : ";
    cin>>r; rm=r;
    cout<<"Nivel de detaliu : ";
    cin>>N;
    cout<<"Timp de sleep : ";
    cin>>g;
    cout<<"Mod de colorare :"<<'\n'<<"0 - Alb"<<'\n'<<"1 - Party mode"<<'\n'<<"2 - Culori diferite pe fiecare nivel"<<'\n';
    cin>>ok;
    if (ok==3) { cout<<"Miscare in pixeli : "; cin>>mi;}
    initgraph(&gd, &gm, "", 1024, 1024);
    cx=getmaxx()/2; cy=getmaxy()/2;
    do {
    circle(cx,cy,rm);
    CercImparte(cx,cy,rm,1);
    if (ok==3) {cleardevice(); rm=(rm+mi)%r+r;}
    }while (p!='t');
	closegraph();
}
