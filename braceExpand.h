#include <string>

enum class RetType { 
    SUCCESS,
    NOT_VALID_CHAR,
    BRACES_MISMATCH,
    COMMA_OUTSIDE_BRACES,
    EMPTY_EXPR
};

class BraceExpander {
public:
    BraceExpander(const std::string& input_str);

    //validate the user input 
    static RetType validate(const std::string& input_str);

    // Perform expansion of the input string and return the output as string
    std::string expand();

private:
    std::string m_input_str;
};