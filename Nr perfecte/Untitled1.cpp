#include <iostream>
using namespace std;
int main()
{
    int a,b,i,suma,d;
    cin>>a>>b;
    for(i=a;i<=b;i++)
    {
        suma=1;
        for(d=2;d*d<=i;d++)
            if(i%d==0)
                {
                    suma=suma+d;
                    suma=suma+i/d;
                }
        d--;
        if(d*d==i)
            suma=suma-d;
        if(suma==i)
            cout<<i<<" ";
    }
    return 0;
}
