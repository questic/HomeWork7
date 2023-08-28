#include "GasStationSimulator.h"
#include <iostream>

int main() {
    GasStationSimulator simulator(3);

    std::cout << "To stop the simulation, press Enter." << std::endl;
    std::thread stopThread([&simulator]() {
        std::cin.get();
        simulator.StopSimulation();
    });

    simulator.Run();

    stopThread.join();

    return 0;
}
