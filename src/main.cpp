#include <iostream>

#include "generator/Generator.h"
#include "transducers/Transducer.h"

int main() {
    /*const std::vector input{1, 1, 2, 2, 3, 3, 2, 1};

    Transducer transducer{};

    const auto result = transducer.process(input, "plateau");

    for (const auto r : result) {
        std::cout << letter_to_string(r) << std::endl;
    }*/

    Generator generator{ One, Max, "plateau" };

    generator.generate();

    return 0;
}