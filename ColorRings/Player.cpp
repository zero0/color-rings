#include "ColorRings.h"

int DefaultColorSorter( Color4 a, Color4 b )
{
    // sort blue first
    int cmp = a.b > b.b ? -1 : a.b < b.b ? 1 : 0;
    if( cmp == 0 )
    {
        // then by red
        cmp = a.r > b.r ? -1 : a.r < b.r ? 1 : 0;
        if( cmp == 0 )
        {
            // then by green
            cmp = a.g > b.g ? -1 : a.g < b.g ? 1 : 0;
        }
    }
    return cmp;
}

Player::Player()
    : m_radius( 2.0f )
    , m_state( PlayerState::Idle )
    , m_colorOrder( PlayerCollectionOrder::Blue )
    , m_currentRing( nullptr )
    , m_numCollectedBalls( 0 )
    , m_score( 0 )
{
}
Player::~Player()
{
}

float Player::DistanceToRingSquared( const Ring& ring ) const
{
    Vector4f d = Math::Sub( m_position, ring.GetPosition() );
    float dist = Math::Length3Sqr( d );
    return dist;
}


int Player::GetScore() const
{
    return m_score;
}

float Player::GetRadius() const
{
    return m_radius;
}

Vector4f Player::GetPosition() const
{
    return m_position;
}
void Player::SetPosition( Vector4f position )
{
    m_position = position;
}

Vector4f Player::GetForward() const
{
    return m_forward;
}
void Player::SetForward( Vector4f forward )
{
    m_forward = forward;
}

void Player::TranslateForward( float distance )
{
    Vector4f direction = Math::Scale( m_forward, distance );
    m_position = Math::Add( m_position, direction );
}

void Player::CollectBallsFromRing( Ring* rings )
{
    m_currentRing = rings;
    m_state = PlayerState::Collecting;
}

void Player::Update( float dt )
{
    switch( m_state )
    {
        case Idle:
            IdleState( dt );
            break;
        case Collecting:
            CollectingState( dt );
            break;
        default:
            break;
    }
}

void Player::IdleState( float dt )
{

}

void Player::CollectingState( float dt )
{
    static const Color4 orderedColors[] = {
        { 0, 0, 255, 255 }, // blue
        { 255, 0, 0, 255 }, // red
        { 0, 255, 0, 255 }, // green
    };

    Color4 currentColor = orderedColors[ m_colorOrder ];

    int numBallsOfCurrentColor = 0;
    float distSqr = 1000000.0f;
    const Ball* ball = nullptr;
    size_t index = 0;
    size_t imax = m_currentRing->GetNumBalls();

    for( size_t i = 0; i != imax; ++i )
    {
        const Ball* b = m_currentRing->GetBall( i );
        if( b->color.rgba == currentColor.rgba )
        {
            ++numBallsOfCurrentColor;

            Vector4f d = Math::Sub( m_position, b->position );
            float dist = Math::Length3Sqr( d );
            if( dist < distSqr )
            {
                distSqr = dist;
                ball = b;
                index = i;
            }
        }
    }

    if( numBallsOfCurrentColor == 0 || ball != nullptr )
    {
        m_colorOrder = (PlayerCollectionOrder)( ( m_colorOrder + 1 ) % PlayerCollectionOrder_Count );
    }

    if( ball != nullptr )
    {
        color_rings_printf( "Collected Ball! [%X %X %X]", ball->color.r, ball->color.g, ball->color.b );
        
        m_collectedBalls[ m_numCollectedBalls ] = ball;
        ++m_numCollectedBalls;

        m_currentRing->RemoveBall( index );

        if( m_currentRing->GetNumBalls() == 0 )
        {
            ++m_score;
            color_rings_printf( "Point Scored! %d", m_score );


        }
    }

    // clean up
    m_currentRing = nullptr;

    m_state = PlayerState::Idle;
}
