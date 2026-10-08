// Restaurant Ordering and Billing System - C++ Academic Project

#include <iostream>
#include "Menu.h"
#include "Ordering.h"
#include "constants.h"
#include "Utils.h"

using namespace seneca;
using namespace std;

int main() {
    // ordering object
    Ordering order("drinks.csv", "foods.csv");

    // check if files could open
    if (!order) {
        cout << "Failed to open data files or the data files are corrupted!" << endl;
        return 1;
    }

    // constant menu types to help with formatting
    const int MAIN_MENU = 1;
    const int ORDER_SUBMENU = 2;
    const int CONFIRM_MENU = 4;

    // main menu
    Menu mainMenu("Seneca Restaurant", MAIN_MENU);
    mainMenu.add("Order");
    mainMenu.add("Print Bill");
    mainMenu.add("Start a New Bill");
    mainMenu.add("List Foods");
    mainMenu.add("List Drinks");

    // order menu
    Menu orderMenu("Order Menu", ORDER_SUBMENU);
    orderMenu.add("Food");
    orderMenu.add("Drink");

    // confirm menu
    Menu confirmMenu("You have bills that are not saved, are you sue you want to exit?", CONFIRM_MENU);
    confirmMenu.add("Yes");

    bool exitProgram = false;
    while (!exitProgram) {
        int selection = mainMenu.run();
        switch (selection) {
            // order
            case 1:
                {
                    bool backToMain = false;
                    while (!backToMain) {
                        int orderSelection = orderMenu.run();
                        switch (orderSelection) {
                            // food
                            case 1:
                                order.addFood();
                                break;
                            // drink
                            case 2:
                                order.orderDrink();
                                break;
                            // return
                            case 0:
                                backToMain = true;
                                break;
                        }
                    }
                }
                break;
            case 2:
                order.displayBill();
                break;
            case 3:
                order.clearBill();
                break;
            case 4:
                order.showFoodMenu();
                break;
            case 5:
                order.showDrinkMenu();
                break;
            // end program
            case 0:
                if (order.unsavedChanges()) {
                    int confirmSelection = confirmMenu.run();
                    if (confirmSelection == 1) {
                        exitProgram = true;
                    }
                } 
                else {
                    exitProgram = true;
                }
                break;
        }
    }
    return 0;
}