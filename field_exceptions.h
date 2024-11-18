#pragma once
#include "exception.h"

class AttackOutsideTheFieldException final : public Exception {
public:
    explicit AttackOutsideTheFieldException(const std::string& message = "The attack is outside the field.\n") : Exception(message) {}
};

class ShipOutsideTheFieldException final : public Exception {
public:
    explicit ShipOutsideTheFieldException(const std::string& message = "A ship cannot be outside the field.\n") : Exception(message) {}
};

class ShipsClosePlacementException final : public Exception {
public:
    explicit ShipsClosePlacementException(const std::string& message = "The ship is too close to another.\n") : Exception(message) {}
};