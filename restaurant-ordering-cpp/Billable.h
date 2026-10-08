// Restaurant Ordering and Billing System - C++ Academic Project

#ifndef SENECA_BILLABLE_H
#define SENECA_BILLABLE_H
#include <iosfwd>
#include <iostream>

namespace seneca {

class Billable {
    char* m_name = nullptr;
    double m_price = 0.0;

protected:
    void setprice(double val); //{ m_price = val; }
    void name(const char* n);

public:
    Billable();
    Billable(const Billable& src);
    virtual ~Billable();
    
    Billable& operator=(const Billable& src);
    
    virtual double price() const;
    virtual std::ostream& print(std::ostream& ostr = std::cout) const = 0;
    virtual bool order() = 0;
    virtual bool ordered() const = 0;
    virtual std::ifstream& read(std::ifstream& file) = 0;
    
    operator const char* () const;
};

double operator+(double money, const Billable& B);
double& operator+=(double& money, const Billable& B);

} 

#endif // !SENECA_BILLABLE_H