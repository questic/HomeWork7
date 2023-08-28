#pragma once
#include "FuelType.h"

class Car {
public:
    Car(int number, const FuelType& type, float amount);
    int GetCarNumber() const;
    const FuelType& GetFuelType();
    float GetFuelAmount() const;

private:
    int m_carNumber;
    FuelType m_fuelType;
    float m_fuelAmount;
};