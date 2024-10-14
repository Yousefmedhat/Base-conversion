#include <iostream>
#include "Converter.h"
using namespace std;

int main(){
  string original,desired;
  uint16_t input_base,desired_base;
  show_menu(0);
  do{
    cin >> input_base;
  } while(input_base > 4 || input_base < 1);
  do{
    cout << "Enter the original number: ";
    cin >> original;
  } while(!check(original,input_base));
  show_menu(input_base);
  do
  {
    cin >> desired_base;
  } while(desired_base > 3 || desired_base < 1);
  desired = convert(original,input_base,desired_base);
  cout << "result number : " << desired;
  return 0;
}