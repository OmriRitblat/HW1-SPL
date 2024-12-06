#pragma once
#include <string>
#include <vector>
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"
using std::string;
using std::vector;

class BaseAction;
class SelectionPolicy;

class Simulation
{
public:
    Simulation(bool isRunning, int planCounter);
    Simulation(const string &configFilePath);
    // rule of 3
    Simulation& operator=(const Simulation &other);
    Simulation(const Simulation &other);
    ~Simulation();

    // rule of 5
    Simulation& operator=(Simulation &&other);
    Simulation(const Simulation &&other);

    void start();
    void addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy);
    void addAction(BaseAction *action);
    bool addSettlement(Settlement *settlement);
    bool addFacility(FacilityType facility);
    bool isSettlementExists(const string &settlementName);
    bool isFacilityExists(const string &facilityName);
    Settlement &getSettlement(const string &settlementName);
    Plan &getPlan(const int planID);
    void step();
    void close();
    void open();
    vector<BaseAction *> &getActionLogs();
    const bool planInRang(int planId) const;

private:
    bool isRunning;
    int planCounter; // For assigning unique plan IDs
    vector<BaseAction *> actionsLog;
    vector<Plan> plans;
    vector<Settlement *> settlements;
    vector<FacilityType> facilitiesOptions;
};