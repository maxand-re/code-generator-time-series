#ifndef PLATEAUTRANSDUCER_H
#define PLATEAUTRANSDUCER_H
#include "SeedTransducer.h"


class PlateauTransducer final : SeedTransducer {
    enum State { START, RISING, PLATEAU };
    State state = START;

public:
    std::vector<SemanticLetter> process(std::vector<int>) override;
};



#endif //PLATEAUTRANSDUCER_H
