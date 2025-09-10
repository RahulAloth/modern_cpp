/*Raw String Literals
Raw string literals were introduced in C++11 to make it easier to write strings that contain characters like backslashes (\) or quotes (") without needing to escape them.
Avoid escaping characters	
*/

std::string s = R"(This is a "raw" string with \backslashes\ and "quotes")";

//Useful for regular expressions, file paths, or embedded code.
std::string regex = R"(\d{3}-\d{2}-\d{4})"; // Matches a SSN pattern

/*
std::string (Standard String Class)
std::string is part of the Standard Template Library (STL) and provides a powerful, flexible way to work with strings.

✅ Key Features:
General string manipulation	
Dynamic size (unlike C-style strings).
Rich set of member functions: length(), substr(), find(), replace(), etc.
Supports operators like +, ==, [].
*/

#include <iostream>
#include <string>

int main() {
    std::string name = "Aloth";
    name += " Rajan";
    std::cout << "Full name: " << name << std::endl;
}


/*
String Streams (std::stringstream)
std::stringstream is part of <sstream> and allows you to treat strings like streams (similar to cin/cout), which is useful for parsing and formatting.

✅ Key Features:
String parsing & formatting
Read/write to strings using stream operators (<<, >>).
Useful for converting between strings and other types.
*/


#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::stringstream ss;
    ss << "Name: " << "Aloth" << ", Age: " << 30;

    std::string result = ss.str();
    std::cout << result << std::endl;
}
// Parsing Stream example:
std::string input = "123 456";
std::stringstream ss(input);
int a, b;
ss >> a >> b; // a = 123, b = 456

