#include <iostream>
#include <ctime>
#include <fstream>


using namespace std;

// get Ckn
long long int ckn(int k,int n)
{
    if (k==n) return 1;
    if (k==1) return n;
    return ckn(k,n-1)+ckn(k-1,n-1);
}

// get a random number [a,b]
int getRandomNumber(int a,int b)
{
    srand(time(NULL));
    return a+rand()%(b-a+1);
}
