#pragma once

#include <vector>
#include <memory>
#include <iostream>

template <typename T>
class GameManager {
public:
    GameManager() = default;
    ~GameManager() = default;



private:
    std::vector<std::shared_ptr<T>> games_;
};
