#include "Car.h"

Car::Car(int number, const FuelType& type, float amount)
        : m_carNumber(number), m_fuelType(type), m_fuelAmount(amount) {}

int Car::GetCarNumber() const {
    return m_carNumber;
}

const FuelType& Car::GetFuelType() {
    return m_fuelType;
}

float Car::GetFuelAmount() const {
    return m_fuelAmount;
}