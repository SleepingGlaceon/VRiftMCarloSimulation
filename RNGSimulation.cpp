#include "RNGSimulation.h"

static const int knockbackAR = 15;
static const int doubleAR = 15;
static const int speed = 10;
static const int huntsAdded = 25;

VRiftSimulation::VRiftSimulation()
{
    std::vector<int> steps;
    std::vector<int> floor;
    std::map<int,int> totalFloors;
}

void VRiftSimulation::simulateOneRun(int initialHunts, int addedHunts, double normalCr, double knockbackCR)
{
    Floor floorTracking;
    while(initialHunts > 0)
    {
        srand(time(NULL));
        int ar = rand()%100;
        int cr = rand()%100;
        if(ar < doubleAR)
        {
            floorTracking.addSteps(2*speed);
        }
        else if (ar < doubleAR +knockbackAR)
        {
            if(cr < knockbackCR)
            {
            floorTracking.addSteps(speed);
            }
            else
            {
            floorTracking.subtractSteps(10);
            }

        }
        else
        {
            if(cr < normalCr)
            {
                floorTracking.addSteps(speed);
            }
        }
        initialHunts--;
        initialHunts+= (floorTracking.getAndResetBonus()*huntsAdded);
    }
    floor.push_back(floorTracking.getFloor());
}

void VRiftSimulation::simulateLots(int initialHunts, int addedHunts, double normalCR, double knockbackCR, int trials)
{
    for (int i = 0; i< trials; i ++)
    {
        simulateOneRun(initialHunts,addedHunts,normalCR,knockbackCR);
    }
    for (std::vector<int>::iterator it = floor.begin(); it!=floor.end(); it++)
    {
        totalFloors[*it]++;
    }
}

void VRiftSimulation::printResults()
{
    std::cout << "results\n";
    for(std::map<int,int>::iterator it= totalFloors.begin(); it!= totalFloors.end(); it++)
    {
        std::cout << "floor" << it -> first << "  " << it->second << std::endl;
    }
}




Floor::Floor(int floor, int steps)
{
    currentFloor = floor;
    currentSteps = steps;
    bonusesToAdd = 0;
}
int Floor::getFloor()
{
    return currentFloor;
}
int Floor::getSteps()
{
    return currentSteps;
}
int Floor::getAndResetBonus()
{
    int bonus = bonusesToAdd;
    bonusesToAdd = 0;
    return bonus;
}
/*
Adds steps to the floor and adjusts the floor number accordingly
assumes that we're adding positive numbers only (no 0 or negatives)
*/
void Floor::addSteps(int steps)
{
    currentSteps += steps;
    if((currentFloor%8)==0)
    {
        currentSteps -=1;
        currentFloor++;
        bonusesToAdd++;
    }
    while((currentFloor%8)!=0) ///while not at eclipse floor, seeing if we're past the floor
    {
        int floorStepCount = (currentFloor/8)*10 +20; ///int arithmetic is intentional
        if(currentSteps>floorStepCount)
        {
            currentSteps-=floorStepCount;
            currentFloor++;
        }
        else
        {
            break;
        }
    }
    if((currentFloor%8)==0) ///if we get to eclipse floor
    {
        currentSteps = 1;
        bonusesToAdd++;
    }
}
///pushbacks only push to the start of a floor
void Floor::subtractSteps(int steps)
{
    currentSteps -= steps;
    if(currentSteps<1)
        currentSteps=1;
}
int Floor::getTotalSteps()
{
    int tempFloor = currentFloor;
    int tempSteps = currentSteps;
    while(tempFloor%8 != 0)
    {
        tempFloor--;
        tempSteps+= (tempFloor/8 * 10)+20; ///int arithmetic is intentional here
    }
    while(tempFloor/8 != 0)
    {
        tempFloor -=8;
        tempSteps+= (tempFloor/8 * 70) +71;
    }
    tempSteps--;
    return tempSteps;
}
