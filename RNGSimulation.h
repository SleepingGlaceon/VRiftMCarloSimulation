#ifndef RNGSIMULATION_H_INCLUDED
#define RNGSIMULATION_H_INCLUDED
#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
class VRiftSimulation
{
private:
    std::vector<int> steps;
    std::vector<int> floor;
    std::map<int, int> totalFloors;
public:
    VRiftSimulation();
    void simulateOneRun(int initialHunts, int addedHunts, double normalCR, double knockbackCR);
    void simulateLots(int initialHunts, int addedHunts, double normalCR, double knockbackCR, int trials);
    void printResults();

};
class Floor
{
private:
    int currentFloor;
    int currentSteps;
    int bonusesToAdd;
public:
    Floor(int floor=1, int steps =1);
    int getFloor();
    int getSteps();
    int getAndResetBonus();
    void addSteps(int steps);
    void subtractSteps(int steps);
    int getTotalSteps();

};


#endif // RNGSIMULATION_H_INCLUDED
