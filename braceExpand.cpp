#include "braceExpand.h"

#include <vector>
#include <string>

BraceExpander::BraceExpander(const std::string& input_str)
    : m_input_str(input_str) {
}

bool isAlpha(char c) {
    return (c >= 'a' and c <= 'z') or (c >= 'A' and c <= 'Z');
}

bool isValidSymbol(char c) {
    return c == '{' or c == '}' or c == ',';
}

const char STARTING_CHAR = ' '; // Sentinel used to mark start

RetType BraceExpander::validate(const std::string& input_str) {
    int open_braces_cnt = 0;
    char prev = STARTING_CHAR; 

    for(auto c : input_str) {
        if (!(isAlpha(c) or isValidSymbol(c))) {
            return RetType::NOT_VALID_CHAR;
        }
        if (c=='{') {
            open_braces_cnt++;
        }
        if (c=='}') {
            if (open_braces_cnt == 0) {
                return RetType::BRACES_MISMATCH;
            }
            open_braces_cnt--;
        }
        if (c==',' and open_braces_cnt <= 0) {
            return RetType::COMMA_OUTSIDE_BRACES;
        }
        if (prev != STARTING_CHAR) {
            if ( (c == '}' and (prev == '{' or prev == ',')) || 
                 (c == ',' and prev == '{') ) {
                return RetType::EMPTY_EXPR;
            }
        }
        prev = c;
    }
    if (open_braces_cnt != 0) {
        return RetType::BRACES_MISMATCH;
    }

    return RetType::SUCCESS;
}

void appendChar(char c, std::vector<std::string>& output) {
    // If empty, add an empty string to make sure char c can get added
    if (output.size() == 0) {
        output.push_back("");
    }
    for (auto& str: output) {
        str += c;
    }
}

// Do Cartersian multiplication of output with source
// output = output x source
// result is overwritten in output (old values cleared!)
void combine(const std::vector<std::string>& source,
             std::vector<std::string>& output) {
    
    std::vector<std::string> source2(output);
    output.clear();
    output.reserve(source.size() * source2.size());

    for (const auto& item1: source2) {
        for (const auto& item2: source) {
            output.push_back(item1 + item2);
        }
    }
}

// Process one expression starting at index start of string str
// expr is just one item either separated by comma or lone item inside {}
// Eg. {expr1, expr2, {expr3, expr4}}
// Returns the index of the string where processing stopped
size_t processExpr(const std::string& str, 
                   size_t start, 
                   std::vector<std::string>& output);

// Process one expression group starting at index start of string str
// expr group contains all items inside one set of matching open and close {}
// Eg. {expr1, expr2, expr3} 
// expr group would include expr1, expr2 and expr3.
// Returns the index of the string where processing stopped
size_t processExprGroup(const std::string& str, 
                        size_t start, 
                        std::vector<std::string>& output);

// Process one expression starting at index start of string str
// expr is just one item either separated by comma or lone item inside {}
// Eg. {expr1, expr2, {expr3, expr4}}
// Returns the index of the string where processing stopped
size_t processExpr(const std::string& str, 
                   size_t start, 
                   std::vector<std::string>& output) {
    size_t i = start;

    while (i < str.size()) {
        if (str[i] == '{') {
            std::vector<std::string> expr_group;
            i = processExprGroup(str, i+1, expr_group);
            combine(expr_group, output);
        }
        else if (str[i] == ',' or str[i] == '}') {
            break;
        }
        else {
            appendChar(str[i], output);
        }
        i += 1;
    }

    return i;
}

// Process one expression group starting at index start of string str
// expr group contains all items inside one set of matching open and close {}
// Eg. {expr1, expr2, expr3} 
// expr group would include expr1, expr2 and expr3.
// Returns the index of the string where processing stopped
size_t processExprGroup(const std::string& str, 
                        size_t start, 
                        std::vector<std::string>& output) {
    size_t i = start;

    while (i < str.size()) {
        std::vector<std::string> expr_output={""};
        // Process one expression at a time and append to output
        i = processExpr(str, i, expr_output);
        output.insert(output.end(), expr_output.begin(), expr_output.end());

        // Done processing once you see '}'
        if (str[i] == '}') {
            break;
        }
        i += 1;
    }

    return i;
}

std::string BraceExpander::expand() {
    std::vector<std::string> output={""};

    processExpr(m_input_str, 0, output);

    std::string output_str;

    // Turn the vector of strings to one output string
    for (const auto& term: output) {
        if (output_str.length() == 0) {
            output_str += term;
        }
        else {

            output_str += (" " + term); 
        }
    }
    return output_str;
}