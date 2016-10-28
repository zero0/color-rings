#pragma once
#ifndef RING_H
#define RING_H

#include "ColorRings.h"

struct Ball
{
    Vector4f position;
    Color4 color;
    float radius;
};

class Ring
{
public:
    Ring();
    ~Ring();

    Vector4f GetPosition() const;
    Vector4f GetForward() const;
    float GetRadius() const;

    float DistanceToBallSquared( Ball* ball );
    
    void Setup( Vector4f position, Vector4f forward, float radius );
    void AddBall( Ball* ball );
    void RemoveBall( size_t index );

    size_t GetNumBalls() const;

    const Ball* GetBall( size_t index ) const;

private:
    Vector4f m_position;
    Vector4f m_forward;
    float m_radius;

    size_t m_numBalls;
    Ball* m_ownedBalls[ COLOR_RING_MAX_BALLS_PER_RING ];
};

#endif // !RING_H
