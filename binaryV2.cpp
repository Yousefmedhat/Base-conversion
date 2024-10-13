#include <iostream>
#include "converter.h"
using namespace std;

int main(){
  string original,desired;
  uint16_t input_base,desired_base;
  show_menu(0);
  cin >> input_base;
  if(input_base < 1 || input_base > 4)
    throw out_of_range("The input isn't in range");
  cout << "Enter the original number:\n";
  cin >> original;
  if(!check(original,input_base))
    throw invalid_argument("The input doesn't match with data type");
  show_menu(input_base);
  cin >> desired_base;
  if(desired_base >= 1 && desired_base <= 3)
    desired = convert(original,input_base,desired_base);
  else
    throw out_of_range("The input isn't in range");
  cout << "result number :\n" << desired;
  return 0;
}