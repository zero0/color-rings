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
    // seed random with time
    long t = color_rings_time();
    color_rings_random_seed( (int)t );

    // board size
    m_boardMin = Math::Vector4( -20, 0, -20, 1 );
    m_boardMax = Math::Vector4(  20, 0,  20, 1 );

    // set player position
    float x = color_rings_random_float( m_boardMin.x, m_boardMax.x );
    float y = color_rings_random_float( m_boardMin.y, m_boardMax.y );
    float z = color_rings_random_float( m_boardMin.z, m_boardMax.z );

    m_player.SetPosition( Math::Vector4( x, y, z, 1 ) );
    m_player.SetForward( Math::Vector4( 1, 0, 0, 0 ) );
    m_player.SetRadius( 5.0f );

    // add rings
    size_t numRings = color_rings_random_int( 10, COLOR_RING_MAX_RINGS );
    color_rings_printf( "Spawning %d Rings", numRings );

    for( size_t i = 0; i != numRings; ++i )
    {
        x = color_rings_random_float( m_boardMin.x, m_boardMax.x );
        y = color_rings_random_float( m_boardMin.y, m_boardMax.y );
        z = color_rings_random_float( m_boardMin.z, m_boardMax.z );
        Vector4f pos = Math::Vector4( x, y, z, 1 );

        x = color_rings_random_float( -1.0f, 1.0f );
        y = 0.0f;
        z = color_rings_random_float( -1.0f, 1.0f );
        Vector4f fwd = Math::Vector4( x, y, z, 0 );
        fwd = Math::Normalize3( fwd );

        AddRing( pos, fwd, 10.0f );
    }

    // add balls
    size_t numBalls = color_rings_random_int( 30, COLOR_RING_MAX_BALLS );
    color_rings_printf( "Spawning %d Balls", numBalls );
    
    for( size_t i = 0; i != numBalls; ++i )
    {
        x = color_rings_random_float( m_boardMin.x, m_boardMax.x );
        y = color_rings_random_float( m_boardMin.y, m_boardMax.y );
        z = color_rings_random_float( m_boardMin.z, m_boardMax.z );
        Vector4f pos = Math::Vector4( x, y, z, 1 );

        int r = color_rings_random_int( 0, 3 );
        Color4 c;
        c.r = r == 0 ? 255 : 0;
        c.g = r == 1 ? 255 : 0;
        c.b = r == 2 ? 255 : 0;
        c.a = 255;

        AddBall( pos, c, 1.0f  );
    }

    // foreach ball, add it to the closest ring
    for( size_t i = 0; i != m_numBalls; ++i )
    {
        Ball* b = &m_balls[ i ];

        float distSqr = 100000.0f;
        Ring* ring = nullptr;

        // find the closest ring to the ball
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

        // add ball to ring
        COLOR_RINGS_ASSERT( ring, "Unable to find a close ring for ball" );
        ring->AddBall( b );
    }

    // start running
    m_isRunning = true;
}

void ColorRingsApp::Process()
{
    while( m_isRunning )
    {
        // TODO: use real timing, for now assume 60fps
        float dt = 1.0f / 60.0f;

        Tick( dt );
    }
}

int ColorRingsApp::Shutdown()
{
    return m_returnCode;
}

void ColorRingsApp::AddRing( Vector4f position, Vector4f forward, float radius )
{
    COLOR_RINGS_ASSERT( m_numRings != COLOR_RING_MAX_RINGS, "Max rings reached" );
    color_rings_printf( "Ring Added at [%f %f %f]", position.x, position.y, position.z );

    // setup new ring
    Ring& ring = m_rings[ m_numRings ];
    ring.Setup( position, forward, radius );

    // increment rings
    ++m_numRings;
}

void ColorRingsApp::AddBall( Vector4f position, Color4 color, float radius )
{
    COLOR_RINGS_ASSERT( m_numBalls != COLOR_RING_MAX_BALLS, "Max balls reached" );
    color_rings_printf( "Ball [%X %X %X] Added at [%f %f %f]", color.r, color.g, color.b, position.x, position.y, position.z );

    // store ball values
    Ball& ball = m_balls[ m_numBalls ];
    ball.position = position;
    ball.radius = radius;
    ball.color = color;

    // increment balls
    ++m_numBalls;
}


void ColorRingsApp::Tick( float dt )
{
    float distSqr = 100000.0f;
    Ring* ring = nullptr;

    // find the closes ring with balls to the player
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

    // if a ring is in range, check that the player is in front of the ring to collect
    if( ring != nullptr )
    {
        // vector from the ring to the player
        Vector4f v = Math::Sub( m_player.GetPosition(), ring->GetPosition() );
        v = Math::Normalize3( v );

        // calculate the zone of colletion (15 deg in front of the ring)
        float zoneOfCollection = 1.0f - Math::DegToRad( 15.0f );
        float angleBetween = Math::Dot3( v, ring->GetForward() );

        // if the player is not in the zone of collections, clear the ring since it can't be used
        if( angleBetween < zoneOfCollection )
        {
            ring = nullptr;
        }
    }

    // if a ring with balls was found, collect balls from the ring
    if( ring != nullptr && ring->GetNumBalls() != 0 )
    {
        m_player.CollectBallsFromRing( ring );
    }
    // otherwise, move the player forward as if the user made them move
    else
    {
        m_player.TranslateForward( COLOR_RINGS_METERS( 2 ) );
    }

    // update the player
    m_player.Update( dt );

    // fail safe to move the player back inside the board if they move outside
    bool playerOutsideBoard = false;
    Vector4f playerPos = m_player.GetPosition();
    if( playerPos.x < m_boardMin.x )
    {
        playerOutsideBoard = true;
        playerPos.x += m_boardMax.x - m_boardMin.x;
    }
    if( playerPos.x > m_boardMax.x )
    {
        playerOutsideBoard = true;
        playerPos.x -= m_boardMax.x - m_boardMin.x;
    }
    if( playerPos.z < m_boardMin.z )
    {
        playerOutsideBoard = true;
        playerPos.z += m_boardMax.z - m_boardMin.z;
    }
    if( playerPos.z > m_boardMax.z )
    {
        playerOutsideBoard = true;
        playerPos.z -= m_boardMax.z - m_boardMin.z;
    }

    // if the player fell outside the board, put them back
    if( playerOutsideBoard )
    {
        m_player.SetPosition( playerPos );
    }

    // find the total balls not collected
    size_t totalBalls = 0;
    for( size_t i = 0; i != m_numRings; ++i )
    {
        totalBalls += m_rings[ i ].GetNumBalls();
    }

    // if there are no more balls, exit loop
    if( totalBalls == 0 )
    {
        color_rings_printf( "All Balls Collected! (Press Enter to exit)" );
        m_isRunning = false;
    }
}
