#include "Main.h"

int main( const char** args )
{
    int ret = 0;

    ColorRingsApp app;
    app.Init();
    app.Process();
    ret = app.Shutdown();

    color_rings_getchar();

    return ret;
}
