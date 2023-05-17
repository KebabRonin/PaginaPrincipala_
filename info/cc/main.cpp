#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("bac.txt");

int n,I,S,sol[70];
/*
Subalgoritm mutaZero(a, n):
 i ← 1
 f ← n
 Câttimp i < f execută
 Câttimp (i < f) ȘI (a[i] ≠ 0) execută
 i ← i + 1
 SfCâttimp
 Câttimp (i < f) ȘI (a[f] = 0) execută
 f ← f - 1
 SfCâttimp
 Dacă i < f atunci
 tmp ← a[i]
 a[i] ← a[f]
 a[f] ← tmp
 SfDacă
 SfCâttimp
SfSubalgoritm
*/

int s[]={-1,3,0,7,0,0,4,3,3,3,0,5};

void f(int a[],int n) {
    int i=1,f=n,tmp;
    while(i<f){
        while(i<f && a[i]!=0) i++;
        while(i<f && a[f]==0) f--;
        if(i<f) {
            tmp=a[i];
            a[i]=a[f];
            a[f]=tmp;
        }
    }
}

int main() {
    f(s,11);
    for(int i=1;i<11;i++) cout<<s[i];
}
