#include <iostream>
#include <stdlib.h>

using namespace std;

#define MAX_SORT    30
#define MAX_RANDOM  40 //Забивка массива будет от -20 до 20

int a[MAX_SORT];

void Shake(int n){
    
    int l, r, i, k, buf;
    k = l = 0;
    r = n - 2;
    while(l <= r){
        for(i = l; i <= r; i++)
            if (a[i] > a[i+1]){
                buf = a[i]; a[i] = a[i+1]; a[i+1] = buf;
                k = i;
            }
            r = k - 1;
        for(i = r; i >= l; i--)
            if (a[i] > a[i+1]){
                buf = a[i]; a[i] = a[i+1]; a[i+1] = buf;
                k = i;
            }
            l = k + 1;
    }
    
    cout << endl << "Массив после сортировки:" << endl;
    for(int i = 0; i < MAX_SORT; i++)  cout << a[i] << " ";
}

int main()
{
    cout << "Массив до сортировки:" << endl;
    for(int i = 0; i < MAX_SORT; i++){
        a[i] = rand() % MAX_RANDOM+1 - (MAX_RANDOM/2);
        cout << a[i] << " ";
    }
    Shake(MAX_SORT);
    return 0;
}
