#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <cmath>

#define MEMMAX 95.0

using namespace std;

void allocatePercent(double* buffer, double percentToUse, MEMORYSTATUSEX statex)
{
    if (percentToUse > MEMMAX)
    {
        cout << "Going to allocate too much memory!" << endl;
        return;
    }

    long long int sizealloc = (int)(((percentToUse/100.0)*statex.ullAvailPhys)/sizeof(double));
    buffer = (double*) calloc ((int)sizealloc, sizeof(double));
    if (buffer == NULL)
    {
        cout << "Buffer allocation error" << endl;
        exit (1);
    }
    for (long long int i = 0; i < sizealloc; i++)
        buffer[i] = 0.0;
    free (buffer);
}

int main()
{
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof (statex);
    double* buffer;

    for (double C = 0.0;C < 3.14159;C += 0.1)
    {
        allocatePercent(buffer, sin(C) * 100.0, statex);
        cout << (sin(C) * 100.0) << endl;
        GlobalMemoryStatusEx (&statex);
        cout << statex.dwMemoryLoad << "% of memory in use" << endl;
        Sleep(1000);
    }
    GlobalMemoryStatusEx (&statex);
    cout << statex.dwMemoryLoad << "% of memory in use" << endl;
    return 0;
}
