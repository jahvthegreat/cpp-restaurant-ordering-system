// Restaurant Ordering and Billing System - C++ Academic Project

#ifndef SENECA_DRINK_H
#define SENECA_DRINK_H
#include "Billable.h"

namespace seneca {
class Drink : public Billable {char m_drinkSize = '\0';
public:
    std::ostream& print(std::ostream& os = std::cout) const override;
    bool order() override;
    bool ordered() const override;
    std::ifstream& read(std::ifstream& ifs) override;
    double price() const override;
};

}

#endif // !SENECA_DRINK_H