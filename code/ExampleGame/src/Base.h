#pragma once

struct Base
{
    int remainingLives = 5;

    void takeDamage()
    {
        remainingLives--;
    }


};