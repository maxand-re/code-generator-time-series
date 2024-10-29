#ifndef SEEDTRANSDUCER_H
#define SEEDTRANSDUCER_H
#include <vector>

#include "../Semantic.h"

class Transducer {
    static std::string compare(int a, int b);

public:
    static std::vector<Semantic::Letter> process(std::vector<int> series, std::string pattern);
};


#endif //SEEDTRANSDUCER_H
