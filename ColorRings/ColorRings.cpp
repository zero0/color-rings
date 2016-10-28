#include "ColorRings.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

void color_rings_assert( const char* file, size_t line, const char* msg, ... )
{
    char buff[ 1024 ];

    va_list vl;
    va_start( vl, msg );

    size_t end = vsprintf_s( buff, msg, vl );
    sprintf_s( buff + end, sizeof( buff ) - end, "\n" );
    printf_s( buff );

    va_end( vl );

    __debugbreak();
}

void color_rings_printf( const char* msg, ... )
{
    char buff[ 1024 ];

    va_list vl;
    va_start( vl, msg );

    size_t end = vsprintf_s( buff, msg, vl );
    sprintf_s( buff + end, sizeof( buff ) - end, "\n" );
    printf_s( buff );

    va_end( vl );
}

int color_rings_random_int( int min, int max )
{
    int r = rand();
    return r % ( max - min ) + min;
}
float color_rings_random_float( float min, float max )
{
    float r = (float)rand() / (float)RAND_MAX;
    return r * ( max - min ) + min;
}

float color_rings_sqrt( float a )
{
    return sqrtf( a );
}

int color_rings_getchar()
{
    return getchar();
}
