#include "Converter.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>

enum {Decimal = 1,Binary,Octal,Hexa};
vector <string> names = {"Decimal","Binary","Octal","Hexadecimal"};

string to_str(ll n){
  string answer;
  while(n){
    answer += n % 10 + '0';
    n /= 10;
  }
  reverse(answer.begin(),answer.end());
  return answer == ""? "0" : answer;
} 
ll to_int(string n){
  ll answer = 0;
  if(n.length() > 18)
  throw length_error("Length exceeds maximum limit");
  for(char c : n){
    answer *= 10;
    answer += c - '0';
  }
  return answer;
}

string fill_zeros(string n,u16 mode){
  int len = n.length();
  string answer;
  if(mode == Octal)
    answer = len == 3 ? n : len == 2 ? "0" + n : "00" + n;
  else if(mode == Hexa)
    answer = len == 4 ? n : len == 3 ? "0" + n : len == 2 ? "00" + n : "000" + n;
  return answer;
}
bool is_decimal(string decimal){
  for(char c : decimal){
    if (c >'9' || c  < '0')
      return false;
  }
  return true;
}
bool is_binary(string binary){
  for (char c : binary)
  {
    if (!(c == '0' || c == '1'))
      return false;
  }
  return true;
}
bool is_octal(string octal){
  for (char c : octal)
  {
    if(c > '7' || c < '0')
      return false;
  }
  return true;
}
bool is_hexa(string hexa){
  for (char c : hexa)
  {
    if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F')))
      return false;
  }
  return true;
}

string to_decimal(string origin,u16 mode){
  int base = mode == Binary? 2 : mode == Octal ? 8 : 16;
  ll answer = 0;
  reverse(origin.begin(),origin.end());
  int i = 0;
  for(char c : origin){
    answer += (c > '9'?10 + c - 'A' :c - '0') * (ll)pow(base,i++);
  }
  return to_str(answer);
}
string to_binary(string origin,u16 mode){
  string answer;
  ll number;
  switch(mode){
    case Decimal:
      number = to_int(origin);
      while(number){
        answer += to_str(number % 2);
        number /= 2;
      }
      reverse(answer.begin(),answer.end());
      break;
    case Octal:
      if (origin.length() == 1) answer = fill_zeros(to_binary(origin,Decimal),Octal);
      else
      answer = fill_zeros(to_binary(origin.substr(0,1),Decimal),Octal)
      +
      to_binary(origin.substr(1,origin.length() - 1),Octal);
      break;
    case Hexa:
      string current = origin.substr(0,1);
      if (origin.length() == 1) answer = fill_zeros(to_binary(current[0] > '9' ? to_string(10 + current[0] - 'A') : current,Decimal),Hexa);
      else{
      answer = fill_zeros(to_binary(current[0] > '9' ? to_string(10 + current[0] - 'A') : current,Decimal),Hexa)
      +
      to_binary(origin.substr(1,origin.length() - 1),Hexa);
      break;
    }
  }
  return answer.empty() ? "0" : answer;
}
string to_octal(string origin,u16 mode){
  string answer,part;
  ll number;
  switch(mode){
    case Decimal:
      number = to_int(origin);
      while(number){
        answer += to_str(number % 8);
        number /= 8;
      }
      reverse(answer.begin(),answer.end());
      break;
    case Binary:
      part = origin.substr(origin.length() > 3? origin.length() - 3 : 0,3);
      if(!origin.substr(0,origin.length()- part.length()).empty())answer += to_octal(origin.substr(0,origin.length()- part.length()),Binary);
      answer += to_decimal(part,Binary);
      break;
    case Hexa:
      answer = to_octal(to_binary(origin,Hexa),Binary);
  }
  return answer.empty()? "0" : answer;
}
string to_hexa(string origin,u16 mode){
  string answer,part;
  ll number;
  switch(mode){
    case Decimal:
      number = to_int(origin);
      while(number){
        answer += string() + hexa_char(to_str(number % 16));
        number /= 16;
      }
      reverse(answer.begin(),answer.end());
      break;
    case Binary:
      part =  origin.substr(origin.length() > 4 ? origin.length() - 4 : 0,4);
      if(!origin.substr(0,origin.length()- part.length()).empty())answer += to_hexa(origin.substr(0,origin.length()- part.length()),Binary);
      answer += hexa_char(to_decimal(part,Binary));
      break;
    case Octal:
      answer = to_hexa(to_binary(origin,Octal),Binary);
      break;
  }
  return answer.empty()? "0" : answer;
}
string hexa_char(string origin){
  int n = to_int(origin);
  if(n < 10)
    return to_str(n);
  else
    return string() + char(n - 10 + 'A');
}

void show_menu(u16 input_type){
  u16 counter = 1;
  for (int i = 0; i < names.size(); i++)
  {
    if(i + 1 == input_type)
      continue;
    cout << counter++ << "- " << names[i] << "\n";
  }
  cout << (!input_type ? "From:\n" : "To:\n");
}
bool check(string input,u16 type){
  switch (type){
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

string convert(string input,u16 original_type,u16 desired_type){
  string desired;
  if(desired_type >= original_type)
    desired_type++;
  switch(desired_type){
    case Decimal:
      desired = to_decimal(input,original_type);
      break;
    case Binary:
      desired = to_binary(input,original_type);
      break;
    case Octal:
      desired = to_octal(input,original_type);
      break;
    case Hexa:
      desired = to_hexa(input,original_type);
      break;
  }
  return trim_zeros(desired);
}

string trim_zeros(string input){
  if(input.find('0') == 0)
    return trim_zeros(input.substr(1));
  else 
    return input.empty() ? "0" : input;
}

