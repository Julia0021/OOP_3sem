#include "ship.h"

Ship::Ship(unsigned length, int index, bool isHorizontal)
    :length(length),index(index),position(isHorizontal) {
        for (int i = 0; i < length; i++) {
            segments.push_back(Segment::Intact);
        }
};

unsigned Ship::getLength() const {
    return length;
}

bool Ship::isHorizontal() const {
    return position;
}

void Ship::changePosition() {
    position = false;
}

Ship::Segment Ship::getSegStatus(int segment_i) const {
    if ((segment_i < 0) || (segment_i >= length)) return Segment::Invalid;
    return segments[segment_i];
}

bool Ship::getSegDamaged(int segment_i) {
    if ((segment_i < 0) || (segment_i >= length)) return false;
    if (segments[segment_i] == Segment::Intact) {
        segments[segment_i] = Segment::Damaged;
        return true;
    } 
    if (segments[segment_i] == Segment::Damaged) {
        segments[segment_i] = Segment::Destroyed;
        return true;
    }
    return false;
}

bool Ship::isDestroyed() const {
    for (int i = 0; i < length; i++) {
        if (segments[i] != Segment::Destroyed) return false;
    }
    return true;
}