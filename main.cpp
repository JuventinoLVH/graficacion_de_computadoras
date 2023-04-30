#include <iostream>
#include "Graficador.h"

using namespace std;

inline void waitForLeftMouseClick();

int main()
{
    Graficador principal(1200,600,CENTRO);

    waitForLeftMouseClick();
    return 0;
}

inline void waitForLeftMouseClick()
{
    while(!kbhit());
}
