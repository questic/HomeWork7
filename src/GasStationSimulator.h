#pragma once
#include <vector>
#include <memory>
#include <thread>
#include "FillingColumn.h"
#include "Car.h"


class GasStationSimulator {
public:
    GasStationSimulator(int numColumns);
    void Run();
    void StopSimulation();

private:
    int m_numColumns;
    std::vector<std::unique_ptr<FillingColumn>> m_columns;
    std::thread userInputThread;
    bool m_stopSimulation;

    Car GenerateRandomCar(int carNumber);
    int FindMinQueueColumn() const;
};
