#include "braceExpand.h"

#include <string>
#include <iostream>

int main() {
    std::string input_str;

    std::cin >> input_str;

    BraceExpander be(input_str);

    if (RetType::SUCCESS == BraceExpander::validate(input_str)) {
        std::cout << be.expand() << std::endl;
    }

    return 0;
}