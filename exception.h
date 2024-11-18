#pragma once
#include <exception>
#include <string>

class Exception : public std::exception {
public:
    Exception(const std::string& message) : message(message) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
protected:
    std::string message;
};