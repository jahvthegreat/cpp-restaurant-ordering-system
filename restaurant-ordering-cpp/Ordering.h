// Restaurant Ordering and Billing System - C++ Academic Project

#ifndef SENECA_ORDERING_H
#define SENECA_ORDERING_H

#include <iosfwd>
#include "Drink.h"
#include "Food.h"
#include "Menu.h"
#include "constants.h"

namespace seneca {
class Ordering {
    unsigned m_foodCount = 0, m_drinkCount = 0, m_billCount = 0;
    unsigned m_billNum = 1;
    Food* m_foods = nullptr;
    Drink* m_drinks = nullptr;
    Billable* m_bill[MaximumNumberOfBillItems]{};
    void printBillHeader(std::ostream& os) const;
    void printBillFooter(std::ostream& os, double total) const;
    size_t countFileRecords(const char* filename) const;
public:
    Ordering(const char* drinksFile, const char* foodsFile);
    ~Ordering();
    
    operator bool() const;
    unsigned itemCount() const;
    bool unsavedChanges() const;
    
    void showFoodMenu() const;
    void showDrinkMenu() const;
    void addFood();
    void orderDrink();
    void displayBill(std::ostream& os = std::cout) const;
    void clearBill();
};
} 

#endif // !SENECA_ORDERING_H