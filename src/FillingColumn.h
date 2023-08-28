#pragma once
#include "Car.h"
#include <queue>
#include <mutex>
#include <condition_variable>

class FillingColumn {
public:
    FillingColumn(int number);
    void EnqueueCar(const Car& car);
    int GetQueueSize();
    void RefuelCar();

private:
    int m_columnNumber;
    std::queue<Car> m_carQueue;
    std::mutex m_queueMutex;
    std::condition_variable m_queueCV;
    std::mutex m_printMutex;
};
