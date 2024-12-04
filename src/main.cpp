#include "Simulation.h"
#include "Settlement.h"
#include "Facility.h"
#include "Global.h"
#include <iostream>

#include <iostream>
#include "Simulation.h"
#include "Facility.h"
#include "SelectionPolicy.h"
#include "Action.h"
#include "Auxiliary.h"

using namespace std;

Simulation *backup = nullptr;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "usage: simulation <config_path>" << endl;
        return 0;
    }
    string configurationFile = argv[1];
    Simulation simulation(configurationFile);
    simulation.start();
    if (backup != nullptr)
    {
        delete backup;
        backup = nullptr;
    }
    return 0;
}