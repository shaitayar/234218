#include "company.h"

int Company::getID() const{
    return this->ID;
}

int Company::getValue() const{
    return this->value;
}

void Company::setValue(int new_value) {
    this->value=new_value;
}