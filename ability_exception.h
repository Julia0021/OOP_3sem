#pragma once
#include "exception.h"

class EmptyAbilitiesException final : public Exception {
public:
    explicit EmptyAbilitiesException(const std::string& message = "You have no abilities left.\n") : Exception(message) {}
};