// Restaurant Ordering and Billing System - C++ Academic Project

#include <iostream>
#include <fstream>
#include <cstring>
#include "Drink.h"
#include "Utils.h"
using namespace std;

namespace seneca {
    ostream& Drink::print(ostream& ostr) const {
        if (*this) {
            ostr.fill('.');
            ostr.width(28);
            ostr.setf(ios::left);
            ostr << (const char*)(*this);
            ostr.unsetf(ios::left);
            switch(m_drinkSize) {
                case 'S': ostr << "SML.."; break;
                case 'M': ostr << "MID.."; break;
                case 'L': ostr << "LRG.."; break;
                case 'X': ostr << "XLR.."; break;
                default: ostr << "....."; break;
            }
            ostr.fill(' ');
            ostr.width(7);
            ostr.setf(ios::right);
            ostr.setf(ios::fixed);
            ostr.precision(2);
            ostr << price();
            ostr.unsetf(ios::right);
        }
        return ostr;
    }
    bool Drink::order() {
        int selection;
        cout << "         Drink Size Selection" << endl
             << "          1- Small" << endl
             << "          2- Medium" << endl
             << "          3- Larg" << endl
             << "          4- Extra Large" << endl
             << "          0- Back" << endl
             << "         > ";
        cin >> selection;
        cin.ignore(10000, '\n');
        const char sizes[] = {'\0', 'S', 'M', 'L', 'X'};
        m_drinkSize = (selection >= 0 && selection <= 4) ? sizes[selection] : '\0';   
        return ordered();
    }
    bool Drink::ordered() const {
        return m_drinkSize != '\0';
    }
    ifstream& Drink::read(ifstream& file) {
        if (file) {
            char name[256]{};
            double price;       
            file.getline(name, 256, ',');
            if (file) {
                file >> price;
                file.ignore();
                
                if (file) {
                    this->name(name);
                    Billable::setprice(price);
                    m_drinkSize = 0;
                }
            }
        }
        return file;
    }
    double Drink::price() const {
        double basePrice = Billable::price();
        switch(m_drinkSize) {
            case 'S': return basePrice * 0.5;
            case 'M': return basePrice * 0.75;
            case 'X': return basePrice * 1.5;
            default: return basePrice;
        }
    }
}
