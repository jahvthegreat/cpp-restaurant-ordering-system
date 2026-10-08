// Restaurant Ordering and Billing System - C++ Academic Project

#include <iostream>
#include <fstream>
#include <cstring>
#include "Food.h"
#include "Utils.h"
using namespace std;

namespace seneca {
    Food::Food() : m_isOrdered(false), m_specialInstructions(nullptr), m_isChildSize(false) {}

    Food::Food(const Food& src) : Billable(src), m_isOrdered(false), m_specialInstructions(nullptr), m_isChildSize(false) {
        m_isOrdered = src.m_isOrdered;
        m_isChildSize = src.m_isChildSize;
        if (src.m_specialInstructions) {
            m_specialInstructions = aloCopy(src.m_specialInstructions);
        }
    }

    Food& Food::operator=(const Food& src) {
        if (this == &src) return *this;
        
        Billable::operator=(src);
        m_isOrdered = src.m_isOrdered;
        m_isChildSize = src.m_isChildSize;
        
        delete[] m_specialInstructions;
        m_specialInstructions = src.m_specialInstructions ? aloCopy(src.m_specialInstructions) : nullptr;
        
        return *this;
    }

    Food::~Food() {
        delete[] m_specialInstructions;
    }

    ostream& Food::print(ostream& os) const {
        if (!*this) return os;

        os.fill('.');
        os.width(28);
        os.setf(ios::left);
        os << (const char*)(*this);
        os.unsetf(ios::left);

        ordered() ? (m_isChildSize ? os << "Child" : os << "Adult") : os << ".....";

        os.fill(' ');
        os.width(7);
        os.setf(ios::right | ios::fixed);
        os.precision(2);
        os << price();
        os.unsetf(ios::right);

        if (m_specialInstructions && &os == &cout) {
            os << " >> ";
            int i = 0;
            while (m_specialInstructions[i] != '\0' && i < 30) {
                os << m_specialInstructions[i++];
            }
        }
        return os;
    }

    bool Food::order() {
        bool validChoice = false;
        int choice = -1;

        do {
            cout << "         Food Size Selection\n"
                 << "          1- Adult\n"
                 << "          2- Child\n"
                 << "          0- Back\n"
                 << "         > ";
            
            cin >> choice;
            cin.ignore(10000, '\n');

            switch (choice) {
                case 0:
                    m_isOrdered = false;
                    delete[] m_specialInstructions;
                    m_specialInstructions = nullptr;
                    return false;
                case 1:
                    m_isOrdered = true;
                    m_isChildSize = false;
                    validChoice = true;
                    break;
                case 2:
                    m_isOrdered = true;
                    m_isChildSize = true;
                    validChoice = true;
                    break;
                default:
                    cout << "Invalid selection, try again." << endl;
            }
        } while (!validChoice);

        cout << "Special instructions\n> ";
        char input[256];
        cin.getline(input, 256);

        delete[] m_specialInstructions;
        m_specialInstructions = input[0] ? aloCopy(input) : nullptr;

        return true;
    }

    bool Food::ordered() const {
        return m_isOrdered;
    }

    ifstream& Food::read(ifstream& ifs) {
        if (ifs) {
            char foodName[256];
            double foodPrice;

            ifs.get(foodName, 256, ',');
            ifs.ignore();

            if (ifs >> foodPrice) {
                ifs.ignore();
                name(foodName);
                Billable::setprice(foodPrice);
                m_isOrdered = false;
                m_isChildSize = false;
                delete[] m_specialInstructions;
                m_specialInstructions = nullptr;
            }
        }
        return ifs;
    }

    double Food::price() const {
        return ordered() && m_isChildSize ? Billable::price() * 0.5 : Billable::price();
    }
}