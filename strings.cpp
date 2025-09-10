#include <iostream>
#include <sstream>
#include <string>

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

/*
std::stringstream – Read and Write
Used for both input and output operations on strings.
*/
int main() {
    std::stringstream ss;
    ss << "Aloth Rajan " << 2025;

    std::string name;
    int year;
    ss >> name >> year;

    std::cout << "Name: " << name << ", Year: " << year << std::endl;
}

/*
std::istringstream – Input Only
Used to parse a string (like reading from a file or user input).
*/
int main() {
    std::string data = "42 3.14 Rahul";
    std::istringstream iss(data);

    int i;
    double d;
    std::string name;

    iss >> i >> d >> name;

    std::cout << "Int: " << i << ", Double: " << d << ", Name: " << name << std::endl;
}
/*
std::ostringstream – Output Only
Used to build a string using stream operations.
*/
int main_ostring() {
    std::ostringstream oss;
    int age = 30;
    std::string name = "Aloth";

    oss << "Name: " << name << ", Age: " << age;

    std::string result = oss.str();
    std::cout << result << std::endl;
}


