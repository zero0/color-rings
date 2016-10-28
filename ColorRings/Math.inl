
namespace Math
{
    COLOR_RINGS_FORCE_INLINE Vector4f Vector4( float x, float y, float z, float w )
    {
        Vector4f v;
        v.x = x;
        v.y = y;
        v.z = z;
        v.w = w;
        return v;
    }

    COLOR_RINGS_FORCE_INLINE Vector4f Scale( Vector4f a, float b )
    {
        Vector4f v;
        v.x = a.x * b;
        v.y = a.y * b;
        v.z = a.z * b;
        v.w = a.w * b;
        return v;
    }
    COLOR_RINGS_FORCE_INLINE Vector4f Add( Vector4f a, Vector4f b )
    {
        Vector4f v;
        v.x = a.x + b.x;
        v.y = a.y + b.y;
        v.z = a.z + b.z;
        v.w = a.w + b.w;
        return v;
    }
    COLOR_RINGS_FORCE_INLINE Vector4f Sub( Vector4f a, Vector4f b )
    {
        Vector4f v;
        v.x = a.x - b.x;
        v.y = a.y - b.y;
        v.z = a.z - b.z;
        v.w = a.w - b.w;
        return v;
    }
    COLOR_RINGS_FORCE_INLINE Vector4f Mul( Vector4f a, Vector4f b )
    {
        Vector4f v;
        v.x = a.x * b.x;
        v.y = a.y * b.y;
        v.z = a.z * b.z;
        v.w = a.w * b.w;
        return v;
    }

    COLOR_RINGS_FORCE_INLINE Vector4f Normalize3( Vector4f a )
    {
        float len = Length3( a );
        return Scale( a, 1.f / len );
    }

    COLOR_RINGS_FORCE_INLINE Vector4f RotateY( Vector4f a, float r )
    {
        float s = color_rings_sin( r );
        float c = color_rings_cos( r );
        
        Vector4f v;
        v.x = a.z * s + a.x * c;
        v.y = a.y;
        v.z = a.z * c - a.x * s;
        v.w = a.w;

        return v;
    }

    COLOR_RINGS_FORCE_INLINE float Length3( Vector4f a )
    {
        float l = Dot3( a, a );
        return color_rings_sqrt( l );
    }

    COLOR_RINGS_FORCE_INLINE float Length3Sqr( Vector4f a )
    {
        float l = Dot3( a, a );
        return l;
    }

    COLOR_RINGS_FORCE_INLINE float Dot3( Vector4f a, Vector4f b )
    {
        float d = a.x * b.x + a.y * b.y + a.z * b.z;
        return d;
    }

    COLOR_RINGS_FORCE_INLINE float DegToRad( float d )
    {
        float r = d * COLOR_RINGS_PIOVER180;
        return r;
    }

    COLOR_RINGS_FORCE_INLINE float RadToDeg( float r )
    {
        float d = r * COLOR_RINGS_180OVERPI;
        return d;
    }

    COLOR_RINGS_FORCE_INLINE float WrapAngleDeg( float d )
    {
        while( d < 0.0f )
        {
            d += 360.0f;
        }

        while( d > 360.0f )
        {
            d -= 360.0f;
        }

        return d;
    }

};
