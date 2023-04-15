#ifndef ALGORITHMS_ALGORITHM_H
#define ALGORITHMS_ALGORITHM_H

#include "../Visualization.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

class Algorithm {
public:
    static constexpr int SPACING = 110;
    static constexpr Vector2 STARTING_POSITION = {230, 368};

public:
    Algorithm(Visualization& visualization);

protected:
    Visualization& mVisualization;
};

#endif // ALGORITHMS_ALGORITHM_H
