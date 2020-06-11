#include <iostream>
#include "RNGSimulation.h"

int main()
{
    VRiftSimulation sim;
    sim.simulateLots(100, 50, 85, 65, 100);
    sim.printResults();
}
