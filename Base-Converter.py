def main():
  convert = {1 : 10 , 2 : 2, 3: 8 , 4 : 16}
  show_menu(0)
  
  # Get original base input
  while (original_base := int(input())) not in range(1,5):
    pass

  original_number = input_Number(convert[original_base])
  show_menu(original_base)

  # Get desired base input
  while (desired := int(input())) not in range(1,4):  
    pass 

  formatSpecifier = {1:"d",2 : "b",3 : "o",4 : "X"}
  print("The result is :",format(original_number,formatSpecifier[desired + 1 if desired >= original_base else desired]))

# Ask user for input until a number that matches the base is received
def input_Number(base):
  try:
    user_input = input("Enter the original number: ")
    return  int(user_input,base)
  except ValueError:
    return input_Number(base)

# Shows the menu excluding already chosen base
def show_menu(input_type):
  names = ["Decimal", "Binary", "Octal", "Hexadecimal"]
  options = [name for i, name in enumerate(names, start=1) if i != input_type]
  
  for index, name in enumerate(options, start=1):
    print(f"{index}- {name}")

  print("From:" if input_type == 0 else "To:")

main()