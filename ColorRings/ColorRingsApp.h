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
    void Tick();
    int Shutdown();

    void AddRing( Vector4f position, Vector4f forward, float radius );
    void AddBall( Vector4f position, Color4 color, float radius );

private:
    Player m_player;
    Ring m_rings[ COLOR_RING_MAX_RINGS ];
    Ball m_balls[ COLOR_RING_MAX_BALLS ];

    size_t m_numBalls;
    size_t m_numRings;

    bool m_isRunning;

    int m_returnCode;
};

#endif // !COLOR_RINGS_APP_H
