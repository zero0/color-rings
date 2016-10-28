#include "ColorRings.h"

ColorRingsApp::ColorRingsApp()
    : m_numBalls( 0 )
    , m_numRings( 0 )
    , m_isRunning( false )
    , m_returnCode( 0 )
{

}
ColorRingsApp::~ColorRingsApp()
{

}

void ColorRingsApp::Init()
{
    m_player.SetPosition( Math::Vector4( 0, 0, 0, 1 ) );
    
    Vector4f min = Math::Vector4( -10, 0, -10, 1 );
    Vector4f max = Math::Vector4(  10, 0,  10, 1 );

    // TODO: remove when testing complete
    size_t numRings = 3; // color_rings_random_int( 10, 25 );
    color_rings_printf( "Spawning %d Rings", numRings );

    for( size_t i = 0; i != numRings; ++i )
    {
        float x = color_rings_random_float( min.x, max.x );
        float y = color_rings_random_float( min.y, max.y );
        float z = color_rings_random_float( min.z, max.z );

        AddRing( Math::Vector4( x, y, z, 1 ), Math::Vector4( 1, 0, 0, 0 ), 10.0f );
    }

    size_t numBalls = 10; // (size_t)color_rings_random_int( 5, 15 );
    color_rings_printf( "Spawning %d Balls", numBalls );
    
    for( size_t i = 0; i != numBalls; ++i )
    {
        float x = color_rings_random_float( min.x, max.x );
        float y = color_rings_random_float( min.y, max.y );
        float z = color_rings_random_float( min.z, max.z );

        int r = color_rings_random_int( 0, 3 );
        Color4 c;
        c.r = r == 0 ? 255 : 0;
        c.g = r == 1 ? 255 : 0;
        c.b = r == 2 ? 255 : 0;
        c.a = 255;

        AddBall( Math::Vector4( x, y, z, 1 ), c, 1.0f  );
    }

    // foreach ball, add it to the closest ring
    for( size_t i = 0; i != m_numBalls; ++i )
    {
        Ball* b = &m_balls[ i ];

        float distSqr = 100000.0f;
        Ring* ring = nullptr;

        for( size_t j = 0; j != m_numRings; ++j )
        {
            Ring* r = &m_rings[ j ];
            float d = r->DistanceToBallSquared( b );
            if( d < distSqr )
            {
                ring = r;
                distSqr = d;
            }
        }

        COLOR_RINGS_ASSERT( ring, "Unable to find close ring for ball" );
        ring->AddBall( b );
    }
}

void ColorRingsApp::Tick()
{
    m_isRunning = true;

    while( m_isRunning )
    {
        float dt = 1.0f / 60.0f;

        float distSqr = 100000.0f;
        Ring* ring = nullptr;

        size_t numRingsNearPlayer = 0;
        for( size_t i = 0; i != m_numRings; ++i )
        {
            Ring& r = m_rings[ i ];
            float d = m_player.DistanceToRingSquared( r );
            if( d < distSqr )
            {
                ring = &r;
                distSqr = d;
            }
        }

        if( ring )
        {
            m_player.CollectBallsFromRing( ring );
        }

        m_player.Update( dt );

        size_t totalBalls = 0;
        for( size_t i = 0; i != m_numRings; ++i )
        {
            totalBalls += m_rings[ i ].GetNumBalls();
        }

        if( totalBalls == 0 )
        {
            m_isRunning = false;
        }
    }
}

int ColorRingsApp::Shutdown()
{
    return m_returnCode;
}

void ColorRingsApp::AddRing( Vector4f position, Vector4f forward, float radius )
{
    COLOR_RINGS_ASSERT( m_numRings != COLOR_RING_MAX_RINGS, "Max rings reached" );

    Ring& ring = m_rings[ m_numRings ];
    ring.Setup( position, forward, radius );

    ++m_numRings;
}

void ColorRingsApp::AddBall( Vector4f position, Color4 color, float radius )
{
    COLOR_RINGS_ASSERT( m_numBalls != COLOR_RING_MAX_BALLS, "Max balls reached" );

    Ball& ball = m_balls[ m_numBalls ];
    ball.position = position;
    ball.radius = radius;
    ball.color = color;

    ++m_numBalls;
}
