#include "Delay.h"

#include <cassert>

Delay::Delay(unsigned size)
    : size(size)
    , head(0u)
{
    data = std::unique_ptr<float[]>(new float[size]);
    assert(data);
    Reset();
}

float Delay::Delayed(unsigned delay)
{
    // only allow delay requests smaller than the delay size
    assert(delay < size);

    const int      delta = (head - delay);
    const unsigned index = (delta >= 0) ? delta
                                        : delta + size;

    assert(index < size);
    return data[index];
}

float Delay::Process(float in)
{
    // read sample from delay data
    const float out = data[head];

    // write sample
    data[head] = in;

    // update head
    ++head;
    if (head >= size)
        head = 0u;

    return out;
}

void Delay::Reset()
{
    memset(data.get(), 0, (size * sizeof(float)));
    head = 0u;
}

