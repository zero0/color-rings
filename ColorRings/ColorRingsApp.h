#pragma once
#ifndef COLOR_RINGS_APP_H
#define COLOR_RINGS_APP_H

#include "ColorRings.h"

class ColorRingsApp
{
public:
    ColorRingsApp();
    ~ColorRingsApp();

    void Init();
    void Process();
    int Shutdown();

    void AddRing( Vector4f position, Vector4f forward, float radius );
    void AddBall( Vector4f position, Color4 color, float radius );

private:
    void Tick( float dt );

    Player m_player;
    Ring m_rings[ COLOR_RING_MAX_RINGS ];
    Ball m_balls[ COLOR_RING_MAX_BALLS ];

    // board size
    Vector4f m_boardMin;
    Vector4f m_boardMax;

    size_t m_numBalls;
    size_t m_numRings;

    bool m_isRunning;

    int m_returnCode;
};

#endif // !COLOR_RINGS_APP_H
