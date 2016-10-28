#pragma once
#ifndef MATH_H
#define MATH_H

#define COLOR_RINGS_PI          3.14159265359f
#define COLOR_RINGS_PIOVER180   ( COLOR_RINGS_PI / 180.0f )
#define COLOR_RINGS_180OVERPI   ( 180.0f / COLOR_RINGS_PI )

struct Vector4f
{
    float x, y, z, w;
};

struct Color4
{
    union
    {
        struct
        {
            unsigned char r, g, b, a;
        };
        unsigned int rgba;
    };
};

namespace Math
{
    COLOR_RINGS_FORCE_INLINE Vector4f Vector4( float x, float y, float z, float w );

    COLOR_RINGS_FORCE_INLINE Vector4f Scale( Vector4f a, float b );
    COLOR_RINGS_FORCE_INLINE Vector4f Add( Vector4f a, Vector4f b );
    COLOR_RINGS_FORCE_INLINE Vector4f Sub( Vector4f a, Vector4f b );
    COLOR_RINGS_FORCE_INLINE Vector4f Mul( Vector4f a, Vector4f b );

    COLOR_RINGS_FORCE_INLINE Vector4f Normalize3( Vector4f a );

    COLOR_RINGS_FORCE_INLINE Vector4f RotateY( Vector4f a, float r );

    COLOR_RINGS_FORCE_INLINE float Length3( Vector4f a );
    COLOR_RINGS_FORCE_INLINE float Length3Sqr( Vector4f a );

    COLOR_RINGS_FORCE_INLINE float Dot3( Vector4f a, Vector4f b );

    COLOR_RINGS_FORCE_INLINE float DegToRad( float d );
    COLOR_RINGS_FORCE_INLINE float RadToDeg( float r );

    COLOR_RINGS_FORCE_INLINE float WrapAngleDeg( float d );


};

#include "Math.inl"

#endif // !MATH_H
