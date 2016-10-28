#include "ColorRings.h"

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
void Player::SetRadius( float r )
{
    m_radius = r;
}

Vector4f Player::GetPosition() const
{
    return m_position;
}
void Player::SetPosition( Vector4f position )
{
    m_position = position;
    color_rings_printf( "Player Moved to [%f %f %f]", m_position.x, m_position.y, m_position.z );
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
            COLOR_RINGS_ASSERT( false, "Unknown PlayerState" );
            break;
    }
}

void Player::IdleState( float dt )
{
    // TODO: implement idle state logic
}

void Player::CollectingState( float dt )
{
    // colors to find in order
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

    // find the current ordered color in the ring
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

    // if there were no balls of the current color, or a ball was found, move to the next color
    if( numBallsOfCurrentColor == 0 || ball != nullptr )
    {
        m_colorOrder = (PlayerCollectionOrder)( ( m_colorOrder + 1 ) % PlayerCollectionOrder_Count );
    }

    // if a ball was found, collect ball and move player
    if( ball != nullptr )
    {
        color_rings_printf( "Collected Ball! [%X %X %X]", ball->color.r, ball->color.g, ball->color.b );
        
        // collect ball
        m_collectedBalls[ m_numCollectedBalls ] = ball;
        ++m_numCollectedBalls;

        // remove ball from ring since it was collected
        m_currentRing->RemoveBall( index );

        // if there are no more balls in the ring, score point
        if( m_currentRing->GetNumBalls() == 0 )
        {
            // score a point
            ++m_score;
            color_rings_printf( "Point Scored! %d", m_score );

            // reset order back to blue when scoring
            m_colorOrder = PlayerCollectionOrder::Blue;

            // determine the angle to move
            float deg = color_rings_random_float( -15.0f, 15.0f );
            deg = Math::WrapAngleDeg( deg );
            float rad = Math::DegToRad( deg );

            // rotate forward vector by angle
            Vector4f fwd = m_currentRing->GetForward();
            fwd = Math::RotateY( fwd, rad );
            fwd = Math::Scale( fwd, COLOR_RINGS_METERS( 5 ) );

            // get new position for player based on current ring's position and forward
            Vector4f newPos = Math::Add( m_currentRing->GetPosition(), fwd );
            SetPosition( newPos );
            SetForward( fwd );
        }
    }
    
    // clean up and return to idle
    m_currentRing = nullptr;

    m_state = PlayerState::Idle;
}
