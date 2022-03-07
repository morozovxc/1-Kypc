#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

int n;

int main()
{
    cout << "Введите кол-во чисел: ";
    cin >> n;
    
    int massive[n];

    cout << "Числа: ";
  
    for(int i=0; i < n; i++){
        massive[i] = 16 - rand() % 30;
        cout << massive[i] << " ";  
    }

    for(int i=0; i < n; i++){
        for(int j=0; j < n-1; j++){
            if(massive[j] > massive[j+1]){
                int buf = massive[j];
                massive[j] = massive[j+1];
                massive[j+1] = buf;
            }
        }
    }

    cout << endl <<"Числа (после сортировки): ";
    for(int i=0; i < n; i++){
        cout << massive[i] << " ";  
    }
    
    return 0;
}
