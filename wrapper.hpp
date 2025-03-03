#pragma once

#include "file_exceptions.h"
#include ".vscode/nlohmann/json.hpp"

#include <iostream>
#include <fstream>

class Wrapper {
private:
    std::fstream file;
public:
    Wrapper(const std::string& filename);

    ~Wrapper();

    void read(nlohmann::json& j);
    void write(nlohmann::json& j);
};