#pragma once
#ifndef COLOR_RINGS_H
#define COLOR_RINGS_H

#define COLOR_RINGS_USE_ASSERTS  1

#define COLOR_RINGS_FORCE_INLINE __forceinline 

#define COLOR_RINGS_CENTEMETERS( d ) ( (d) * 0.01f )
#define COLOR_RINGS_METERS( d ) ( (d) * 1.0f )
#define COLOR_RINGS_KILOMETERS( d ) ( (d) * 1000.f )

#if COLOR_RINGS_USE_ASSERTS
#define COLOR_RINGS_ASSERT( t, m, ... )  do { if( !(t) ) { color_rings_assert( __FILE__, __LINE__, (m), __VA_ARGS__ ); } } while( 0 )
#else
#define COLOR_RINGS_ASSERT( t, m )  (void)0
#endif

void color_rings_assert( const char* file, size_t line, const char* msg, ... );
void color_rings_printf( const char* msg, ... );

int color_rings_random_int( int min, int max );
float color_rings_random_float( float min, float max );

float color_rings_sqrt( float a );

int color_rings_getchar();

enum
{
    COLOR_RING_MAX_BALLS_PER_RING = 32,
    COLOR_RING_MAX_RINGS = 64,
    COLOR_RING_MAX_BALLS = 128
};

#include "Math.h"
#include "Ring.h"
#include "Player.h"
#include "ColorRingsApp.h"

struct Ball;
class Ring;
class Player;
class ColorRingsApp;

#endif // !COLOR_RINGS_H
