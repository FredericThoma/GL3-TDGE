#pragma once


namespace gl3::ecs::components {

    struct WaveState {
        int currentWave;
        int timeElapsed;
        float waveProgressPercentage;
    };

}
