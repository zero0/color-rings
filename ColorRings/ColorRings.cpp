#include "ColorRings.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

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

long color_rings_time()
{
    time_t t;
    time( &t );
    
    return (long)t;
}

void color_rings_random_seed( int seed )
{
    srand( seed );
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

float color_rings_sin( float a )
{
    return sinf( a );
}
float color_rings_cos( float a )
{
    return cosf( a );
}

int color_rings_getchar()
{
    return getchar();
}
