#include "SeedTransducer.h"

char SeedTransducer::compare(const int a, const int b) {
    if (a < b) return '<';
    if (a == b) return '=';
    return '>';
}
