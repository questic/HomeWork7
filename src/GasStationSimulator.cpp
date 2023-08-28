#include "GasStationSimulator.h"
#include <thread>
#include <random>

GasStationSimulator::GasStationSimulator(int numColumns) : m_numColumns(numColumns) {
    m_columns.reserve(numColumns);
    for (int i = 0; i < numColumns; ++i) {
        m_columns.emplace_back(std::make_unique<FillingColumn>(i + 1));
    }
}

void GasStationSimulator::Run() {
    std::vector<std::thread> columnThreads;
    for (auto& column : m_columns) {
        columnThreads.emplace_back(&FillingColumn::RefuelCar, column.get());
    }

    std::thread carGeneratorThread([this] {
        int carNumber = 1;
        while (!m_stopSimulation) {
            Car car = GenerateRandomCar(carNumber);

            int selectedColumn = FindMinQueueColumn();
            m_columns[selectedColumn]->EnqueueCar(car);

            std::this_thread::sleep_for(std::chrono::seconds(3));
            ++carNumber;
        }
    });


    for (auto& thread : columnThreads) {
        thread.detach();
    }

    carGeneratorThread.join();
}

void GasStationSimulator::StopSimulation() {
    m_stopSimulation = true;
}

Car GasStationSimulator::GenerateRandomCar(int carNumber) {
    FuelType fuelType("Default Fuel");
    float fuelAmount;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> fuelAmountDist(5.0, 60.0);
    fuelAmount = fuelAmountDist(gen);

    switch (carNumber % 3) {
        case 0:
            fuelType = FuelType("Diesel");
            break;
        case 1:
            fuelType = FuelType("AI-92");
            break;
        case 2:
            fuelType = FuelType("AI-95");
            break;
    }

    return Car(carNumber, fuelType, fuelAmount);
}

int GasStationSimulator::FindMinQueueColumn() const {
    int minQueueSize = m_columns[0]->GetQueueSize();
    int selectedColumn = 0;

    for (size_t i = 1; i < m_columns.size(); ++i) {
        int queueSize = m_columns[i]->GetQueueSize();
        if (queueSize < minQueueSize) {
            minQueueSize = queueSize;
            selectedColumn = i;
        }
    }

    return selectedColumn;
}