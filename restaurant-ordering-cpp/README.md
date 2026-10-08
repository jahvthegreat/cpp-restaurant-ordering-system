# Restaurant Ordering & Billing System (C++)

A console-based C++ restaurant ordering application developed as a multi-milestone academic project.

## Features

- Navigate a main menu and separate food/drink ordering menus
- View food and drink menus loaded from CSV files
- Choose adult/child food portions and drink sizes
- Add optional special instructions to food orders
- Create and display an itemized bill with 13% tax
- Save numbered bills to text files and begin a new bill
- Confirm exit when an unfinished bill is present

## Technologies and concepts

C++17, object-oriented programming, inheritance and virtual methods, dynamic memory management, copy constructors and assignment operators, file streams, and input validation.

## Compile and run

Requires a C++17 compiler (for example, Clang++ or G++). From this project's root directory:

```bash
clang++ -std=c++17 -Wall -Wextra -pedantic main.cpp Billable.cpp Drink.cpp Food.cpp Menu.cpp Ordering.cpp Utils.cpp -o restaurant
./restaurant
```

Run from the project folder because `foods.csv` and `drinks.csv` are loaded using relative paths. The program creates numbered `bill_###.txt` files in the current directory.

## Project structure

- `main.cpp` - application flow and menu choices
- `Menu.*` - interactive menus
- `Ordering.*` - loading items, ordering, billing, saving bills
- `Billable.*` - shared abstract interface for billable items
- `Food.*`, `Drink.*` - item-specific choices and pricing
- `Utils.*` - utility functions
- `foods.csv`, `drinks.csv` - sample menu data

## Milestones

The application was developed over five milestones: menu items, interactive navigation, billable food/drink types, ordering/billing features, then final application integration.

## Notes

This is an academic learning project. Before making it public, confirm that publishing assignment solutions is permitted by the course/instructor. The portfolio copy omits personal student identifiers and compiled/debug artifacts.

This portfolio copy includes small build and reliability fixes: the missing `<limits>` include, consistent trailing newlines in CSV files, safe deletion of bill items when none were ordered, simplified self-assignment checking, and removal of redundant constructor initializers. The application has been smoke-tested for food ordering, drink ordering, displaying/saving a bill, and clean exit, but is not exhaustively tested.
