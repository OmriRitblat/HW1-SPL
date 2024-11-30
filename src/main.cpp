#include "Simulation.h"
#include "Settlement.h"
#include "Facility.h"
#include <iostream>

using namespace std;

// Simulation* backup = nullptr;

int main(int argc, char** argv){
    // string s("adad");
    // string &b=s;
    // SettlementType t = SettlementType::CITY;;
    // Settlement r (b, t);
    // cout << r.toString() << endl;
    // FacilityCategory fc=FacilityCategory::ECONOMY;
    // FacilityType f("adi city",fc,1,2,3,4);
    // // cout << f.toString() << endl;
    // Facility newf(f,"s");
    // cout << newf.toString() << endl;
    if(argc!=2){
        cout << "usage: simulation <config_path>" << endl;
        return 0;
    }
    string configurationFile = argv[1];
    Simulation simulation(configurationFile);
    // simulation.start();
    // if(backup!=nullptr){
    // 	delete backup;
    // 	backup = nullptr;
    // }
    return 0;
}