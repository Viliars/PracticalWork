#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

int main()
{
    srand(time(NULL));
    int a,b;
    ofstream out("input.txt", ios_base::out | ios_base::trunc );
    for(int i=0;i<99;++i)
    {
        a=rand()%400;
        b=rand()%400;
        out<<a<<" "<<b<<endl;
    }
    a=rand()%400;
    b=rand()%400;
     out<<a<<" "<<b;
    return 0;
}
