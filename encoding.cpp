#include <iostream>
#include <stdlib.h>
#include <cstring> 

using namespace std;


#define CODE_ATBASH       "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define DECODE_ATBASH    "ZYXWVUTSRQPONMLKJIHGFEDCBA"
#define MAX_LENGTH 128
char maybe;
char load[MAX_LENGTH];
int k;


char* code_atbash(char* src) {
   char* dst = src;
   const char* cch, *dch;
 
   while( *src ) {
        if(isalpha(*src)) {
                  for(dch = DECODE_ATBASH, cch = CODE_ATBASH; *cch; *cch++, *dch++) {
                       if( *cch == toupper(*src) ) {
                            *src = (isupper(*src)) ?  *dch : tolower(*dch);
                             break;
                       }
                  }
         }
         *src++;
   }
   return dst;
}

char* decode_atbash(char* src) {
   char* dst = src;
   const char* cch, *dch;
 
   while( *src ) {
         if(isalpha(*src)) {
               for(dch = DECODE_ATBASH, cch = CODE_ATBASH; *cch; *cch++, *dch++) {
                    if( *dch == toupper(*src) ) {
                          *src = (isupper(*src)) ?  *cch : tolower(*cch);
                            break;
                     }
                }
         }
         *src++;
   }
   return dst;
}

string decode(char check)
{
    setlocale(0,"RUS");
    switch(check)
    {
        case '1':{
            for(int i = 0; i < MAX_LENGTH; i++)
                load[i] -= 3;
            break;
            
        }
        case '2':{
            for(int i = 0; i < MAX_LENGTH; i++)
                load[i] -= k * i + 1;
            break;
        }
        case '3':{
            return decode_atbash(load);
            break;
        }
    }
    return load;
}
string code(char check)
{
    setlocale(0,"RUS");
    switch(check)
    {
        case '1':{
            for(int i = 0; i < MAX_LENGTH; i++)
                load[i] += 3;
            break;
        }
        case '2':{
            printf("Введите ключ: ");
            cin >> k;
            for(int i = 0; i < MAX_LENGTH; i++)
                load[i] += k * i + 1;
            break;
        }
        case '3':{
            return code_atbash(load);
            break;
        }
        default:{
            printf("Вы выбрали неверное действите!\n");
            printf("\n1) Цезарь\n2) Виженера\n3) Атбаш\nДействие: ");
            cin >> maybe;
            printf("Введите строку: ");
            cin >> load;
            cout << decode(maybe);
            break;
        }
    }
    return load;
}

int main()
{
    printf("\n1) Цезарь\n2) Виженера\n3) Атбаш\nДействие: ");
    cin >> maybe;
    printf("Введите строку: ");
    cin >> load;
    cout << code(maybe) << endl;
    cout << decode(maybe); 
    return 0;
}

