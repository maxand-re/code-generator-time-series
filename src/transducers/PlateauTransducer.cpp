#include "PlateauTransducer.h"

#include <iostream>
#include <ostream>

std::vector<PlateauTransducer::SemanticLetter> PlateauTransducer::process(const std::vector<int> series) {
    std::vector<SemanticLetter> result;

    for (unsigned int i = 1; i < series.size(); ++i) {
        const char comparison = compare(series[i - 1], series[i]);

        switch (state) {
            case START:
                result.push_back(OUT);
                if (comparison == '<') {
                    state = RISING;
                }

                break;
            case RISING:
                if (comparison == '<') {
                    result.push_back(OUT);
                } else if (comparison == '=') {
                    result.push_back(MAYBE_B);
                    state = PLATEAU;
                } else {
                    result.push_back(FOUND_E);
                    state = START;
                }

                break;
            case PLATEAU:
                if (comparison == '=') {
                    result.push_back(MAYBE_B);
                } else if (comparison == '<') {
                    result.push_back(OUT_R);
                    state = RISING;
                } else {
                    result.push_back(FOUND_E);
                    state = START;
                }

                break;
            default:
                std::cerr << "PlateauTransducer::process() called with invalid state" << std::endl;
                exit(-1);
        }
    }

    return result;
}
