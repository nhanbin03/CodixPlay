#ifndef ALGORITHMS_ALGORITHM_H
#define ALGORITHMS_ALGORITHM_H

#include "../Visualization.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

class Algorithm {
public:
    Algorithm(Visualization& visualization);

protected:
    Visualization& mVisualization;
};

#endif // ALGORITHMS_ALGORITHM_H
