#ifndef SEEDTRANSDUCER_H
#define SEEDTRANSDUCER_H
#include <vector>


class SeedTransducer {
protected:
    static char compare(int a, int b);

public:
    enum SemanticLetter {
        OUT,
        OUT_R,
        OUT_A,
        MAYBE_B,
        MAYBE_A,
        FOUND,
        FOUND_E,
        IN
    };

    virtual ~SeedTransducer() = default;
    virtual std::vector<SemanticLetter> process(std::vector<int>) = 0;

};



#endif //SEEDTRANSDUCER_H
