#pragma once
#include <string>

class FuelType {
public:
    FuelType(const std::string& name);
    std::string GetTypeName() const;

private:
    std::string m_typeName;
};
