#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

int n, c;
long ch;

int main()
{
    cin >> n;
    cin >> c;
    
    int massive[n];
    
    for(int i=0; i < n; i++){
        massive[i] = rand() % c-(c/2);
        ch += massive[i];
    }
    
    cout << ch << endl;
    
    return 0;
}
