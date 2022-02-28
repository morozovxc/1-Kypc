#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

int c;
int ch;
char d;
char k = 'y';

int calc(char n, int ch2){
    int old = ch;

    cout<<"[debug]";
    cout<<n;
    printf("%d ",ch2);
  
    switch(n){
        case '+':{ ch += ch2; }
        case '-':{ ch -= ch2; }
        case '*':{ ch *= ch2; }
        case ':':{ ch /= ch2; }
        case '%':{ ch %= ch2; }
        case '^':{ pow(ch, ch2); }
        default:{
            cout<<"Неверное действие.\nПовторите запрос:";
            cin>>d;
            calc(d, c);
        }
    }
    cout<<"Вывод:"<<old<<n<<ch2<<"="<<ch<<endl;
    return 0;
}

int main(){
    cout<<"Введите первое число:";
    cin>>ch;
    while(k == 'y'){
        cout<<"Введите действие:";
        cin>>d;
        if(d == 'n'){
            k = 'n';
            cout<<"Вывод: "<<ch<<endl;
            break;
        }
        cout<<"Введите число:";
        cin>>c;
        calc(d, c);
    }
    return 0;
}
