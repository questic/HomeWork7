#include "FillingColumn.h"
#include <iostream>
#include <random>
#include <thread>

FillingColumn::FillingColumn(int number) : m_columnNumber(number) {}

void FillingColumn::EnqueueCar(const Car& car) {
    std::unique_lock<std::mutex> lock(m_queueMutex);
    m_carQueue.push(car);

    bool isRefueling = !m_carQueue.empty();

    m_queueCV.notify_one();
    lock.unlock();

    if (isRefueling) {
        std::unique_lock<std::mutex> printLock(m_printMutex);
        std::cout << "Car " << car.GetCarNumber() << " is in the queue on column " << m_columnNumber << std::endl;
    }
}

int FillingColumn::GetQueueSize() {
    std::unique_lock<std::mutex> lock(m_queueMutex);
    return m_carQueue.size();
}

void FillingColumn::RefuelCar() {
    while (true) {
        std::unique_lock<std::mutex> lock(m_queueMutex);
        m_queueCV.wait(lock, [this] { return !m_carQueue.empty(); });

        Car car = m_carQueue.front();
        m_carQueue.pop();
        lock.unlock();

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 5);
        int refuelTime = dis(gen);

        std::this_thread::sleep_for(std::chrono::seconds(refuelTime));

        {
            std::unique_lock<std::mutex> printLock(m_printMutex);
            std::cout << "Start refueling car " << car.GetCarNumber() << " at column " << m_columnNumber << std::endl;
            std::cout << "Car " << car.GetCarNumber() << " paid for " << car.GetFuelAmount() << " $ of fuel of type " << car.GetFuelType().GetTypeName() << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(3));

        {
            std::unique_lock<std::mutex> printLock(m_printMutex);
            std::cout << "End refueling car " << car.GetCarNumber() << " at column " << m_columnNumber << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(dis(gen)));
    }
}
