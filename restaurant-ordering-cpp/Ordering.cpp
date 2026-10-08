// Restaurant Ordering and Billing System - C++ Academic Project

#include <fstream>
#include <iomanip>
#include <cstdio>
#include "Ordering.h"
#include "Utils.h"
#include "constants.h"
#include "Menu.h"

namespace seneca {
namespace {
    void createBillFilename(char* name, unsigned num) {
        std::sprintf(name, "bill_%03u.txt", num);
        //std::snprintf(name, 40, "bill_%03u.txt", num);
    }
}
// size_t Ordering::countFileRecords(const char* file) const {
//     size_t count = 0;
//     std::ifstream in(file);
//     if (in.is_open()) {
//         while (!in.eof()) {
//             std::string line;
//             std::getline(in, line);
//             if (!line.empty()) ++count;
//         }
//     }
//     return count;
// }
size_t Ordering::countFileRecords(const char* file) const {
    size_t count = 0;
    std::ifstream in(file);
    if (in.is_open()) {
        std::string line;
        while (std::getline(in, line)) {
            // Only count non-empty lines that contain a comma
            if (!line.empty() && line.find(',') != std::string::npos) {
                ++count;
            }
        }
    } else {
        std::cerr << "Error: Could not open file " << file << std::endl;
    }
    return count;
}
// Ordering::Ordering(const char* drinksFile, const char* foodsFile) : m_drinks(nullptr), m_foods(nullptr), 
//     m_drinkCount(0), m_foodCount(0), m_billCount(0), m_billNum(1) {
//     const size_t drinkRecs = countFileRecords(drinksFile);
//     const size_t foodRecs = countFileRecords(foodsFile);
//     if (drinkRecs > 0 && foodRecs > 0) {
//         std::ifstream drinkFile(drinksFile), foodFile(foodsFile);
//         if (drinkFile && foodFile) {
//             try {
//                 m_drinks = new Drink[drinkRecs];
//                 m_foods = new Food[foodRecs];
//                 size_t i = 0;
//                 while (i < drinkRecs) {
//                     if (!m_drinks[i].read(drinkFile) || !m_drinks[i]) break;
//                     ++m_drinkCount;
//                     ++i;
//                 }
//                 for (i = 0; i < foodRecs; ++i) {
//                     if (!m_foods[i].read(foodFile) || !m_foods[i]) break;
//                     ++m_foodCount;
//                 }
//                 if (m_drinkCount != drinkRecs || m_foodCount != foodRecs) {
//                     delete[] m_drinks; 
//                     delete[] m_foods;
//                     m_drinks = nullptr;
//                     m_foods = nullptr;
//                 }
//             } catch (...) {
//                 delete[] m_drinks;
//                 delete[] m_foods;
//                 throw;
//             }
//         }
//     }
// }
Ordering::Ordering(const char* drinksFile, const char* foodsFile) {
    const size_t drinkRecs = countFileRecords(drinksFile);
    const size_t foodRecs = countFileRecords(foodsFile);
    
    if (drinkRecs == 0 || foodRecs == 0) {
        return; // Early return if files are empty or can't be opened
    }

    std::ifstream drinkFile(drinksFile), foodFile(foodsFile);
    if (!drinkFile.is_open() || !foodFile.is_open()) {
        return; // Early return if files can't be opened
    }

    try {
        m_drinks = new Drink[drinkRecs];
        m_foods = new Food[foodRecs];
        
        size_t i = 0;
        while (i < drinkRecs && m_drinks[i].read(drinkFile)) {
            if (m_drinks[i]) {
                ++m_drinkCount;
                ++i;
            }
        }

        for (i = 0; i < foodRecs && m_foods[i].read(foodFile); ++i) {
            if (m_foods[i]) {
                ++m_foodCount;
            }
        }

        // If we didn't read all records, clean up
        if (m_drinkCount != drinkRecs || m_foodCount != foodRecs) {
            delete[] m_drinks; 
            delete[] m_foods;
            m_drinks = nullptr;
            m_foods = nullptr;
            m_drinkCount = 0;
            m_foodCount = 0;
        }
    } catch (...) {
        delete[] m_drinks;
        delete[] m_foods;
        m_drinks = nullptr;
        m_foods = nullptr;
        throw;
    }
}
Ordering::~Ordering() {
    delete[] m_foods;
    delete[] m_drinks;
    for (unsigned i = 0; i < m_billCount; ++i) {
        delete m_bill[i];
    }
}
Ordering::operator bool() const { 
    return m_drinks != nullptr && m_foods != nullptr; 
}
unsigned Ordering::itemCount() const { 
    return m_billCount; 
}
bool Ordering::unsavedChanges() const { 
    return m_billCount != 0; 
}
void Ordering::showFoodMenu() const {
    if (!this->operator bool()) {
        std::cout << "Ordering system not initialized properly.\n";
        return;
    }
    std::cout << "List Of Avaiable Meals\n"
              << "========================================\n";
    unsigned i = 0;
    do {
        m_foods[i].print(std::cout) << '\n';
    } while (++i < m_foodCount);
    std::cout << "========================================\n";
}
void Ordering::showDrinkMenu() const {
    if (!*this) {
        std::cout << "Ordering system not initialized properly.\n";
        return;
    }
    std::cout << "List Of Avaiable Drinks\n"
              << "========================================\n";
    for (auto i = 0u; i < m_drinkCount; ) {
        m_drinks[i].print(std::cout) << '\n';
        i++;
    }
    std::cout << "========================================\n";
}
void Ordering::addFood() {
    bool invalid = !*this || m_billCount >= MaximumNumberOfBillItems;
    if (invalid) {
        std::cout << (!*this ? "Ordering system not initialized properly.\n" 
                             : "Cannot add more items, the bill is full.\n");
        return;
    }

    Menu menu("Food Menu", 3);
    unsigned i = 0;
    while (i < m_foodCount) {
        menu.add(m_foods[i]);
        i++;
    }   
    const int choice = menu.run();
    if (choice > 0 && choice <= static_cast<int>(m_foodCount)) {
        Food* item = new Food(m_foods[choice-1]);
        if (item->order()) {
            m_bill[m_billCount] = item;
            m_billCount++;
        } else {
            delete item;
        }
    }
}
void Ordering::orderDrink() {
    if (!*this) {
        std::cout << "Ordering system not initialized properly.\n";
        return;
    }
    if (m_billCount >= MaximumNumberOfBillItems) {
        std::cout << "Cannot add more items, the bill is full.\n";
        return;
    }
    Menu menu("Drink Menu", 3);
    for (auto i = 0u; i < m_drinkCount; ) {
        menu.add(m_drinks[i]);
        ++i;
    }
    const int choice = menu.run();
    if (choice > 0) {
        if (choice <= static_cast<int>(m_drinkCount)) {
            Drink* item = new Drink(m_drinks[choice-1]);
            if (item->order()) {
                m_bill[m_billCount++] = item;
            } else {
                delete item;
            }
        }
    }
}
void Ordering::printBillHeader(std::ostream& os) const {
    os << "Bill # " << std::setfill('0') << std::setw(3) 
       << m_billNum << " =============================\n";
    os.fill(' ');
}
void Ordering::printBillFooter(std::ostream& os, double total) const {
    const double tax = total * Tax;
    const double grandTotal = total + tax;
    constexpr int width = 40;
    
    os << std::fixed << std::setprecision(2)
       << "                     Total:" << std::setw(width-24) << total << '\n'
       << "                     Tax:" << std::setw(width-21) << tax << '\n'
       << "                     Total+Tax:" << std::setw(width-28) << grandTotal << '\n'
       << "========================================\n";
    
    os.unsetf(std::ios::fixed);
    os.precision(6);
}
void Ordering::displayBill(std::ostream& os) const {
    if (!*this) {
        if (&os == &std::cout) {
            std::cout << "Ordering system not initialized properly.\n";
        }
        return;
    }
    if (m_billCount == 0 && &os == &std::cout) {
        std::cout << "Bill is empty!\n";
        return;
    }
    double total = 0.0;
    printBillHeader(os);
    for (auto i = 0u; i < m_billCount; ) {
        m_bill[i]->print(os) << '\n';
        total += m_bill[i]->price();
        i++;
    }
    printBillFooter(os, total);
}
void Ordering::clearBill() {
    if (!*this) {
        std::cout << "Ordering system not initialized properly.\n";
        return;
    }
    if (m_billCount > 0) {
        char filename[40];
        createBillFilename(filename, m_billNum);   
        std::ofstream out(filename);
        if (out) {
            displayBill(out);
            std::cout << "Saved bill number " << m_billNum << '\n';
        } else {
            std::cerr << "Error: Could not save bill to file " << filename << '\n';
        }
        for (auto i = 0u; i < m_billCount; ++i) {
            delete m_bill[i];
        }
        m_billCount = 0;
        m_billNum++;
    }
    std::cout << (m_billCount > 0 ? "Starting bill number " : "Current bill number is ")
              << m_billNum << '\n';
    std::cout.fill(' ');
}
}