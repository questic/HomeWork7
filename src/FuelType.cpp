#include "FuelType.h"

FuelType::FuelType(const std::string& name) : m_typeName(name) {}

std::string FuelType::GetTypeName() const {
    return m_typeName;
}
