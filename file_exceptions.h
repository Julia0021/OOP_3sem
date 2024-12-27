#pragma once
#include "exception.h"

class UnableToOpenFileException final : public Exception {
public:
    explicit UnableToOpenFileException(const std::string& message = "Unable to open the file.\n") : Exception(message) {}
};

class HashMismatchException final : public Exception {
public:
    explicit HashMismatchException(const std::string& message = "Savefile has been interrupted and now you can't load it.\n") : Exception(message) {}
};