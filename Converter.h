#include <string>
using namespace std;
typedef long long ll;
typedef uint16_t u16;

//UI
void show_menu(u16); // show the menu excluding already chosen base
bool check(string,u16); // checks if the input is matches the chosen base
string convert(string,u16,u16); // convert the input from one base to another
string trim_zeros(string);     // trim the leading zeros from start of string

//Checking
bool is_decimal(string); // return ture if the number is decimal false othewise
bool is_binary(string);  // return ture if the number is binary false othewise
bool is_octal(string);   // return ture if the number is octal false othewise
bool is_hexa(string);    // return ture if the number is hexa false   othewise

//Conversion
string to_decimal(string,u16); // convert from a base to decimal
string to_binary(string,u16);  // convert from a base to binary
string to_octal(string,u16);   // convert from a base to octal
string to_hexa(string,u16);    // convert from a base to hexa

string hexa_char(string); // converts a decimal number to the equivalent hexa character

//Helper
string to_str(ll);             // converts an decimal number to string
ll to_int(string);             // converst a string to long long decimal number
string fill_zeros(string,u16); // fill zeros for binary number to match its eqivalent
// hexa(4 bytes) or octal(3 bytes) representaion


