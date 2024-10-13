#include "Converter.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>

enum {Decimal = 1,Binary,Octal,Hexa};
vector<string> names = {"Decimal", "Binary", "Octal", "Hexadecimal"};

// UI Functions
void show_menu(u16 input_type)
{
  u16 counter = 1;
  for (int i = 0; i < names.size(); i++)
  {
    if (i + 1 == input_type)
      continue;
    cout << counter++ << "- " << names[i] << "\n";
  }
  cout << (!input_type ? "From:\n" : "To:\n");
}
bool check(string input, u16 type)
{
  switch (type)
  {
  case Decimal:
    return is_decimal(input);
  case Binary:
    return is_binary(input);
  case Octal:
    return is_octal(input);
  case Hexa:
    return is_hexa(input);
  }
}
string convert(string input, u16 inputnumberal_type, u16 desired_type)
{
  string desired;
  if (inputnumberal_type == Hexa)
    capitalize(input);
  if (desired_type >= inputnumberal_type)
    desired_type++;
  switch (desired_type)
  {
  case Decimal:
    desired = to_decimal(input, inputnumberal_type);
    break;
  case Binary:
    desired = to_binary(input, inputnumberal_type);
    break;
  case Octal:
    desired = to_octal(input, inputnumberal_type);
    break;
  case Hexa:
    desired = to_hexa(input, inputnumberal_type);
    break;
  }
  return trim_zeros(desired);
}

// Checker Functions
bool is_decimal(string decimal)
{
  for (char c : decimal)
  {
    if (c > '9' || c < '0')
      return false;
  }
  return true;
}
bool is_binary(string binary)
{
  for (char c : binary)
  {
    if (!(c == '0' || c == '1'))
      return false;
  }
  return true;
}
bool is_octal(string octal)
{
  for (char c : octal)
  {
    if (c > '7' || c < '0')
      return false;
  }
  return true;
}
bool is_hexa(string hexa)
{
  for (char c : hexa)
  {
    if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F')))
      return false;
  }
  return true;
}

// Conversion Functions
string to_decimal(string inputnumber, u16 basetype)
{
  int base = basetype == Binary ? 2 : basetype == Octal ? 8 : 16;
  ll result = 0;
  reverse(inputnumber.begin(), inputnumber.end());
  int i = 0;
  for (char c : inputnumber)
  {
    result += (c > '9' ? 10 + c - 'A' : c - '0') * (ll)pow(base, i++);
  }
  return to_str(result);
}
string to_binary(string inputnumber, u16 basetype)
{
  string result;
  ll number;
  switch (basetype)
  {
  case Decimal:
    number = to_int(inputnumber);
    while (number)
    {
      result += to_str(number % 2);
      number /= 2;
    }
    reverse(result.begin(), result.end());
    break;
  case Octal:
    if (inputnumber.length() == 1)
      result = fill_zeros(to_binary(inputnumber, Decimal), Octal);
    else
      result = fill_zeros(to_binary(inputnumber.substr(0, 1), Decimal), Octal) +
                to_binary(inputnumber.substr(1, inputnumber.length() - 1), Octal);
    break;
  case Hexa:
    string current = inputnumber.substr(0, 1);
    if (inputnumber.length() == 1)
      result = fill_zeros(to_binary(current[0] > '9' ? to_string(10 + current[0] - 'A') : current, Decimal), Hexa);
    else
    {
      result = fill_zeros(to_binary(current[0] > '9' ? to_string(10 + current[0] - 'A') : current, Decimal), Hexa) +
               to_binary(inputnumber.substr(1, inputnumber.length() - 1), Hexa);
      break;
    }
  }
  return result.empty() ? "0" : result;
}
string to_octal(string inputnumber, u16 basetype)
{
  string result, segment;
  ll number;
  switch (basetype)
  {
  case Decimal:
    number = to_int(inputnumber);
    while (number)
    {
      result += to_str(number % 8);
      number /= 8;
    }
    reverse(result.begin(), result.end());
    break;
  case Binary:
    segment = inputnumber.substr(inputnumber.length() > 3 ? inputnumber.length() - 3 : 0, 3);
    if (!inputnumber.substr(0, inputnumber.length() - segment.length()).empty())
      result += to_octal(inputnumber.substr(0, inputnumber.length() - segment.length()), Binary);
    result += to_decimal(segment, Binary);
    break;
  case Hexa:
    result = to_octal(to_binary(inputnumber, Hexa), Binary);
  }
  return result.empty() ? "0" : result;
}
string to_hexa(string inputnumber, u16 basetype)
{
  string result, segment;
  ll number;
  switch (basetype)
  {
  case Decimal:
    number = to_int(inputnumber);
    while (number)
    {
      result += string() + hexa_char(to_str(number % 16));
      number /= 16;
    }
    reverse(result.begin(), result.end());
    break;
  case Binary:
    segment = inputnumber.substr(inputnumber.length() > 4 ? inputnumber.length() - 4 : 0, 4);
    if (!inputnumber.substr(0, inputnumber.length() - segment.length()).empty())
      result += to_hexa(inputnumber.substr(0, inputnumber.length() - segment.length()), Binary);
    result += hexa_char(to_decimal(segment, Binary));
    break;
  case Octal:
    result = to_hexa(to_binary(inputnumber, Octal), Binary);
    break;
  }
  return result.empty() ? "0" : result;
}

// Helper Functions
string hexa_char(string inputnumber)
{
  int n = to_int(inputnumber);
  if (n < 10)
    return to_str(n);
  else
    return string() + char(n - 10 + 'A');
}

string to_str(ll n)
{
  string result;
  while (n)
  {
    result += n % 10 + '0';
    n /= 10;
  }
  reverse(result.begin(), result.end());
  return result == "" ? "0" : result;
}
ll to_int(string n)
{
  ll result = 0;
  if (n.length() > 18)
    throw length_error("Length exceeds maximum limit");
  for (char c : n)
  {
    result *= 10;
    result += c - '0';
  }
  return result;
}

string fill_zeros(string input, u16 basetype)
{
  int len = input.length();
  string result;
  if (basetype == Octal)
    result = len == 3 ? input : len == 2 ? "0" + input : "00" + input;
  else if (basetype == Hexa)
    result = len == 4 ? input : len == 3 ? "0" + input : len == 2   ? "00" + input : "000" + input;
  return result;
}
string trim_zeros(string input)
{
  if (input.find('0') == 0)
    return trim_zeros(input.substr(1));
  else
    return input.empty() ? "0" : input;
}

void capitalize(string &input)
{
  for (int i = 0; i < input.size(); i++)
    input[i] = toupper(input[i]);
}