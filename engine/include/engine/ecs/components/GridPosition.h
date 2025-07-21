#pragma once
struct GridPosition {
    int x;
    int y;

    bool operator==(const GridPosition& other) const {
        return x == other.x && y == other.y;
    }
};
