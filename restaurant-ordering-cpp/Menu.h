// Restaurant Ordering and Billing System - C++ Academic Project

#ifndef SENECA_MENU_H
#define SENECA_MENU_H
#include "Billable.h"
#include "constants.h"
namespace seneca {
class Menu {
    char* m_title = nullptr;
    int m_menuType = 1;
    Billable* m_items[MaximumNumberOfMenuItems] = {};
    char* m_textItems[MaximumNumberOfMenuItems] = {};
    unsigned m_itemCount = 0;
    unsigned m_textCount = 0;
public:
    Menu(const char* title, int type = 1);
    ~Menu();
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;
    void add(Billable& item);
    void add(const char* textItem);
    int run() const;
};

}

#endif // !SENECA_MENU_H