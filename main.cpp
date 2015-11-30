#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <cmath>
#include <ctime>

#define MEMMAX 100.0
#define PI 3.1415926535

using namespace std;

void allocatePercent(double* (*buffer), double percentToUse, MEMORYSTATUSEX statex)
{
    if ((*buffer) != NULL)
        free((*buffer));
    if (percentToUse > MEMMAX)
    {
        cout << "Going to allocate too much memory!" << endl;
        return;
    }

    long long int sizealloc = ((percentToUse/100.0)*statex.ullAvailPhys)+sizeof(double);
    cout << "Bytes:" << sizealloc << endl;
    double* tempBuff = NULL;
    tempBuff = (double*) malloc(sizealloc);
    if (tempBuff == NULL)
    {
        cout << "Buffer allocation error" << endl;
        exit (1);
    }
    else
    {
        (*buffer) = tempBuff;
        for (unsigned long long int i = 0; i < (sizealloc/sizeof(double)); i ++)
            (*buffer)[i] = 0.0;
    }
}

int main()
{
    MEMORYSTATUSEX statex;
    double* buffer = NULL;
    double X1, X2, dT, A;
    statex.dwLength = sizeof (statex);

    clock_t time0 = clock();
    clock_t time1 = clock();
    clock_t time2 = clock();

    cout << "X1: ";
    cin >> X1;
    cout << "X2: ";
    cin >> X2;
    cout << "Time to take (sec): ";
    cin >> dT;
    cout << "Amplitude (% of available RAM): ";
    cin >> A;

    for (double C = X1;C < X2;C += ((time2-time1)/((double)CLOCKS_PER_SEC))/(dT/X2))
    {
        time1 = clock();
        allocatePercent(&buffer, abs(sin(C) * A), statex);
        GlobalMemoryStatusEx (&statex);
        cout << statex.dwMemoryLoad << "% of memory in use" << endl;
        time2 = clock();
    }
    if (buffer != NULL)
        free(buffer);
    GlobalMemoryStatusEx (&statex);
    cout << statex.dwMemoryLoad << "% of memory in use" << ", Total Time: " << (clock()-time0/((double)CLOCKS_PER_SEC)) << endl;
    return 0;
}
