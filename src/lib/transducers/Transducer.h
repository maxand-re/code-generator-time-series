#ifndef SEEDTRANSDUCER_H
#define SEEDTRANSDUCER_H
#include <vector>
#include <nlohmann/json.hpp>

#include "../Semantic.h"

class Transducer {
    static std::string compare(int a, int b);

public:
    static std::vector<Semantic::Letter> process(const std::vector<int> &series, nlohmann::json patternJson);
};


#endif //SEEDTRANSDUCER_H
