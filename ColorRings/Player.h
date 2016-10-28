#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "ColorRings.h"

enum PlayerState
{
    Idle,
    Collecting,

    PlayerState_Count
};

enum PlayerCollectionOrder
{
    Blue,
    Red,
    Green,

    PlayerCollectionOrder_Count
};

class Player
{
public:
    Player();
    ~Player();

    float DistanceToRingSquared( const Ring& ring ) const;

    int GetScore() const;

    float GetRadius() const;
    void SetRadius( float r );

    Vector4f GetPosition() const;
    void SetPosition( Vector4f position );

    Vector4f GetForward() const;
    void SetForward( Vector4f forward );

    void TranslateForward( float distance );

    void CollectBallsFromRing( Ring* ring );

    void Update( float dt );

private:
    void IdleState( float dt );
    void CollectingState( float dt );

    Vector4f m_position;
    Vector4f m_forward;
    float m_radius;

    PlayerState m_state;

    PlayerCollectionOrder m_colorOrder;

    Ring* m_currentRing;

    size_t m_numCollectedBalls;
    const Ball* m_collectedBalls[ COLOR_RING_MAX_BALLS ];

    int m_score;

};

#endif // !PLAYER_H
