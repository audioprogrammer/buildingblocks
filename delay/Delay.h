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

    // Writes a sample to the delay
    void Write(float sample);

    // Reads a sample from the delay
    float Read();

    unsigned                 size;
    unsigned                 readPosition;
    unsigned                 writePosition;
    std::unique_ptr<float[]> data;
};


