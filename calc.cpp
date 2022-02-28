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
  
    switch(n){
        case '+':{ ch += ch2; cout<<"Вывод:"<<old<<n<<ch2<<"="<<ch<<endl; break; }
        case '-':{ ch -= ch2; cout<<"Вывод:"<<old<<n<<ch2<<"="<<ch<<endl; break; }
        case '*':{ ch *= ch2; cout<<"Вывод:"<<old<<n<<ch2<<"="<<ch<<endl; break; }
        case '/':{ 
            if(ch2 == 0){
                cout<<"Делить на ноль нельзя."<<endl;
                break;
            }
            ch /= ch2; cout<<"Вывод:"<<old<<n<<ch2<<"="<<ch<<endl; break; 
        }
        case '%':{ ch %= ch2; cout<<"Вывод:"<<old<<n<<ch2<<"="<<ch<<endl; break; }
        case '^':{ pow(ch, ch2); cout<<"Вывод:"<<old<<n<<ch2<<"="<<ch<<endl; break; }
        default:{
            cout<<"Неверное действие.\nПовторите запрос:";
            cin>>d;
            calc(d, c);
            break;
        }
    }
    return 1;
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
