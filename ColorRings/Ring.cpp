#include "ColorRings.h"

Ring::Ring()
{
}

Ring::~Ring()
{
}

Vector4f Ring::GetPosition() const
{
    return m_position;
}

Vector4f Ring::GetForward() const
{
    return m_forward;
}

float Ring::GetRadius() const
{
    return m_radius;
}

float Ring::DistanceToBallSquared( Ball* ball )
{
    Vector4f dir = Math::Sub( m_position, ball->position );
    float dist = Math::Length3Sqr( dir );
    return dist;
}

void Ring::Setup( Vector4f position, Vector4f forward, float radius )
{
    m_position = position;
    m_forward = forward;
    m_radius = radius;
}

void Ring::AddBall( Ball* ball )
{
    COLOR_RINGS_ASSERT( m_numBalls != COLOR_RING_MAX_BALLS_PER_RING, "Max balls reached" );
    
    m_ownedBalls[ m_numBalls ] = ball;
    ++m_numBalls;
}

void Ring::RemoveBall( size_t index )
{
    COLOR_RINGS_ASSERT( index < m_numBalls, "Index out of range" );
    COLOR_RINGS_ASSERT( m_numBalls > 0, "No Balls to remove" );

    --m_numBalls;
    m_ownedBalls[ index ] = m_ownedBalls[ m_numBalls ];
}

size_t Ring::GetNumBalls() const
{
    return m_numBalls;
}

const Ball* Ring::GetBall( size_t index ) const
{
    COLOR_RINGS_ASSERT( index < m_numBalls, "Index out of range" );
    return m_ownedBalls[ index ];
}
