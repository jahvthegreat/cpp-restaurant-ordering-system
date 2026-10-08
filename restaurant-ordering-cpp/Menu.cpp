// Restaurant Ordering and Billing System - C++ Academic Project

#include <iostream>
#include "Menu.h"
#include "Utils.h"
#include "constants.h"
using namespace std;

namespace seneca {
    Menu::Menu(const char* title, int type) : m_menuType(type), m_itemCount(0), m_textCount(0) {
        m_title = aloCopy(title);
        fill_n(m_items, MaximumNumberOfMenuItems, nullptr);
        fill_n(m_textItems, MaximumNumberOfMenuItems, nullptr);
    }

    Menu::~Menu() {
        delete[] m_title;
        for (size_t i = 0; i < m_textCount; delete[] m_textItems[i++]);
    }
    void Menu::add(Billable& item) {
        if (m_menuType == 3 && (m_itemCount + m_textCount < MaximumNumberOfMenuItems)) {
            m_items[m_itemCount++] = &item;
        }
    }
    void Menu::add(const char* item) {
        const int validTypes[] = {1, 2, 4};
        bool isValidType = false;
        for (int t : validTypes) {
            if (m_menuType == t) {
                isValidType = true;
                break;
            }
        }
        if (isValidType && (m_itemCount + m_textCount < MaximumNumberOfMenuItems)) {
            m_textItems[m_textCount++] = aloCopy(item);
        }
    }
    int Menu::run() const {
        const char* titles[] = {"", " ", "   ", "      "};
        const char* exitTexts[] = {
            " 0- Exit",
            " 0- End Program",
            "    0- Back to main menu",
            "       0- Back to Order",
            " 0- No"
        };
        const char* prompts[] = {
            "> ",
            "> ",
            "   > ",
            "      > ",
            "> "
        };
        cout << titles[m_menuType] << (m_menuType == 1 ? m_title + string(" ") : m_title) << endl;
        for (size_t i = 0; i < m_itemCount; i++) {
            if (m_items[i] && *m_items[i]) {
                cout << "       " << (i + 1) << "- " << (const char*)(*m_items[i]) << endl;
            }
        }
        size_t start = (m_menuType == 3) ? m_itemCount : 0;
        for (size_t i = 0; i < m_textCount; i++) {
            if (m_textItems[i]) {
                cout << (m_menuType == 3 ? "       " : " ") << (start + i + 1) << "- " << m_textItems[i] << endl;
            }
        }
        cout << exitTexts[m_menuType] << endl;
        return getInt(0, m_itemCount + m_textCount, prompts[m_menuType]);
    }
}
