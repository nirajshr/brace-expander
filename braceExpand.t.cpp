#include "braceExpand.h"

#include <vector>
#include <string>
#include <iostream>
#include <cassert>

void testValidation() {
    // test valid characters
    assert( (RetType::SUCCESS == BraceExpander::validate("")) );
    assert( (RetType::SUCCESS == BraceExpander::validate("{a,b{c,d}}")) );
    assert( (RetType::NOT_VALID_CHAR == BraceExpander::validate("[abc]")) );
    assert( (RetType::NOT_VALID_CHAR == BraceExpander::validate("{a, }")) );
    assert( (RetType::NOT_VALID_CHAR == BraceExpander::validate("34")) );

    // test for braces mismatch
    assert( (RetType::BRACES_MISMATCH == BraceExpander::validate("}{")) );
    assert( (RetType::BRACES_MISMATCH == BraceExpander::validate("}ABC")) );
    assert( (RetType::BRACES_MISMATCH == BraceExpander::validate("ABC}")) );
    assert( (RetType::BRACES_MISMATCH == BraceExpander::validate("{ABC")) );
    assert( (RetType::BRACES_MISMATCH == BraceExpander::validate("{ABC}}D{")) );
    assert( (RetType::BRACES_MISMATCH == BraceExpander::validate("{A{B,C}")) );
    assert( (RetType::SUCCESS == BraceExpander::validate("pre{A,B{C,D},{E,D}}suf")) );

    // test for empty expr
    assert( (RetType::EMPTY_EXPR == BraceExpander::validate("{}")) );
    assert( (RetType::EMPTY_EXPR == BraceExpander::validate("{A,}")) );
    assert( (RetType::EMPTY_EXPR == BraceExpander::validate("{,B}")) );

    // test for comma outside braces
    assert( (RetType::COMMA_OUTSIDE_BRACES == BraceExpander::validate("A,B,C")) );
    assert( (RetType::COMMA_OUTSIDE_BRACES == BraceExpander::validate("{A,B},{C,D}")) );
}

typedef std::pair<std::string, std::string> Spec;

// Ideally, This spec can be defined in a text/data file
std::vector<Spec> getSpec() {
    std::vector<Spec> specs;

    specs.push_back(Spec("{A,B,C}", "A B C"));
    specs.push_back(Spec("AB{C,D}", "ABC ABD"));
    specs.push_back(Spec("{A,B}{C,D}", "AC AD BC BD"));
    specs.push_back(Spec("{A,B{C,D}}", "A BC BD"));
    specs.push_back(Spec("{{A},{B}}", "A B"));
    specs.push_back(Spec("{ABC}", "ABC"));

    return specs;
}

void testSpec() {
    std::cout << "Running tests..." << std::endl;

    auto specs = getSpec();
    for (const auto& spec: specs) {
        std::string output_str = BraceExpander(spec.first).expand();
        std::cout << spec.first << " -> " << output_str << std::endl;
        assert( (output_str == spec.second) );
    }

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    testValidation();
    testSpec();

    return 0;
}