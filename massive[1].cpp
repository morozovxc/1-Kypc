#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

int n;
long ch;

int main()
{
    cout << "Введите кол-во чисел: ";
    cin >> n;
    
    int massive[n];

    cout << "Числа: ";
  
    for(int i=0; i < n; i++){
        massive[i] = rand() % 30 - 15;
        cout << massive[i] << " ";
        ch += massive[i];
    }
    
    cout << endl << "Сумма: "<< ch << endl;
    
    return 0;
}
