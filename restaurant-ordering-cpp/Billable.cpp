// Restaurant Ordering and Billing System - C++ Academic Project

#include <iostream>
#include <fstream>
#include "Billable.h"
#include "Utils.h"
using namespace std;

namespace seneca {
    void Billable::setprice(double value) {
            m_price = value;
    }
    void Billable::name(const char* name) {
        if (m_name != nullptr) {
            delete[] m_name;
            m_name = nullptr;
        }
        m_name = aloCopy(name);
    }
    Billable::Billable() {
        m_name = nullptr;
        m_price = 0.0;
    }
    Billable::Billable(const Billable& src) {
        m_name = nullptr;
        m_price = 0.0;
        *this = src;
    }
    Billable& Billable::operator=(const Billable& src) {
        if (this != &src) {
            name(src.m_name);
            setprice(src.m_price);
        }
        return *this;
    }
    Billable::~Billable() {
        if (m_name) {
            delete[] m_name;
        }
    }
    double Billable::price() const {
        double result = m_price;
        return result;
    }
    Billable::operator const char* () const {
        const char* name = m_name;
        return name;
    }
    double operator+(double money, const Billable& B) {
        double total = money;
        total += B.price();
        return total;
    }
    double& operator+=(double& money, const Billable& B) {
        for (int i = 0; i < 1; i++) {
            money = money + B;
        }
        return money;
    }
}