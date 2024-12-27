#pragma once
#include <vector>

class Ship 
{
public:
    enum class Segment {Intact, Damaged, Destroyed, Invalid};

    Ship(unsigned length, int index, bool isHorizontal = true);

    unsigned getLength() const;
    bool isHorizontal() const;
    void changePosition();
    Segment getSegStatus(int segment_i) const;
    bool getSegDamaged(int segment_i);
    bool isDestroyed() const;
    int index;
private:
    unsigned length;
    bool position;
    std::vector<Segment> segments;
};