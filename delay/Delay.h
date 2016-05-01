#pragma once

#include <memory>

// Audio Delay Building Block
class Delay
{

public:

    Delay(unsigned size);

    // Returns the value of a sample in the delay buffer with given delay in samples
    float Delayed(unsigned delay);

    // Process one sample
    float Process(float in);
    
    // Resets delay internal state
    void Reset();

private:

    unsigned                 size;
    unsigned                 head;
    std::unique_ptr<float[]> data;
};


