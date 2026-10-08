// Restaurant Ordering and Billing System - C++ Academic Project

#ifndef SENECA_FOOD_H
#define SENECA_FOOD_H

#include "Billable.h"
namespace seneca {
class Food : public Billable {
    bool m_isOrdered = false;
    char* m_specialInstructions = nullptr;
    bool m_isChildSize = false;
public:
    Food();
    ~Food();
    Food& operator=(const Food& src);
    std::ostream& print(std::ostream& os = std::cout) const override;
    std::ifstream& read(std::ifstream& ifs) override;
    Food(const Food& src);
    bool order() override;
    bool ordered() const override;
    double price() const override;
};

}

#endif // !SENECA_FOOD_H