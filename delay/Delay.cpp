#include "Delay.h"

#include <cassert>

Delay::Delay(unsigned size)
    : size(size)
    , readPosition(0u)
    , writePosition(0u)
{
    data = std::unique_ptr<float[]>(new float[size]);
    assert(data);
    Reset();
}

float Delay::Delayed(unsigned delay)
{
    // only allow delay requests smaller than the delay size
    assert(delay < size);

    const int      delta = (readPosition - delay);
    const unsigned index = (delta >= 0) ? delta
        : delta + size;

    assert(index < size);
    return data[index];
}

float Delay::Process(float in)
{
    float const out = Read();
    Write(in);

    return out;
}

void Delay::Reset()
{
    memset(data.get(), 0, (size * sizeof(float)));
    writePosition = 0u;
    readPosition  = 0u;
}

void Delay::Write(float sample)
{
    //write sample
    data[writePosition] = sample;

    //update position
    ++writePosition;
    if (writePosition >= size)
        writePosition = 0u;
}

float Delay::Read()
{
    // read sample
    float const sample = data[readPosition];

    // update read position
    ++readPosition;
    if (readPosition >= size)
        readPosition = 0u;

    return sample;
}

