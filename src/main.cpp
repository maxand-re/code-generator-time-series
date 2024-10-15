#include <iostream>

std::string signature_sequence(const int input[], size_t size) {
    std::string signature(size - 1, '\0');

    for (size_t i = 1; i < size; i++) {
        const int before = input[i - 1];
        const int now = input[i];

        if (before == now) {
            signature[i - 1] = '=';
        } else if (before < now) {
            signature[i - 1] = '>';
        } else {
            signature[i - 1] = '<';
        }
    }

    return signature;
}

int main() {
    const int input[] = {1, 2, 1, 2, 1, 1, 2, 1, 2, 3};
    size_t size = std::size(input);

    std::cout << "Sequence: " << signature_sequence(input, size) << std::endl;

    return 0;
}
