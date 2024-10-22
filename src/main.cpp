#include <iostream>

#include "transducers/PlateauTransducer.h"

std::string semanticLetterToString(const SeedTransducer::SemanticLetter letter) {
    switch (letter) {
        case SeedTransducer::SemanticLetter::OUT: return "out";
        case SeedTransducer::SemanticLetter::OUT_R: return "out_r";
        case SeedTransducer::SemanticLetter::OUT_A: return "out_a";
        case SeedTransducer::SemanticLetter::MAYBE_A: return "maybe_a";
        case SeedTransducer::SemanticLetter::MAYBE_B: return "maybe_b";
        case SeedTransducer::SemanticLetter::FOUND: return "found";
        case SeedTransducer::SemanticLetter::FOUND_E: return "found_e";
        default: return "unknown";
    }
}

int main() {
    const std::vector input{1, 1, 2, 2, 3, 3, 2, 1};

    PlateauTransducer plateau;

    const auto result = plateau.process(input);

    for (const auto r : result) {
        std::cout << semanticLetterToString(r) << std::endl;
    }

    return 0;
}
