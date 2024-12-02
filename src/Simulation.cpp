#pragma once
#include <string>
#include <vector>
#include "Simulation.h"
#include "Auxiliary.h"
#include "fstream"
#include "Action.h"
using std::string;
using std::vector;
using namespace std;

Simulation::Simulation(bool isRunning, int planCounter) : isRunning(isRunning), planCounter(planCounter)
{
}
Simulation::Simulation(const string &configFilePath) : isRunning(true), planCounter(0), actionsLog(10, nullptr)
{
    cout << "configFilePath " << configFilePath << endl;
    std::ifstream file(configFilePath);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file at " << configFilePath << std::endl;
    }
    else
    {
        std::string line;
        while (std::getline(file, line))
        {
            // Parse the line into arguments
            std::vector<std::string> arguments = Auxiliary::parseArguments(line);
            if (arguments[0] != "#")
            {
                if (arguments[0] == "settlement")
                {
                    Settlement *s = new Settlement(arguments[1], Settlement::getSettlememtType(arguments[2]));
                    settlements.push_back(s);
                }
                else if (arguments[0] == "facility")
                {
                    string name = arguments[1];
                    FacilityType f(name, FacilityType::getFacilityCategory(arguments[2]), std::stoi(arguments[3]), std::stoi(arguments[4]), std::stoi(arguments[5]), std::stoi(arguments[6]));
                    facilitiesOptions.push_back(f);
                }
                else if (arguments[0] == "plan")
                {
                    SelectionPolicy *policy;
                    if (arguments[2] == "nve")
                    {
                        policy = new NaiveSelection();
                    }
                    else if (arguments[2] == "bal")
                    {
                        policy = new BalancedSelection(0, 0, 0);
                    }
                    else if (arguments[2] == "eco")
                    {
                        policy = new EconomySelection();
                    }
                    else
                    {
                        policy = new SustainabilitySelection();
                    }
                    plans.push_back(Plan(planCounter, this->getSettlement(arguments[1]), policy, facilitiesOptions));
                    planCounter++;
                }
                else
                    cout << "there is an error in the config file" << endl;
            }
        }
    }
}

Simulation::~Simulation()
{
    for (BaseAction *b : actionsLog)
        delete b;
    for (Settlement *s : settlements)
        delete s;
}
void Simulation::operator=(const Simulation &other)
{
    this->isRunning = other.isRunning;
    this->planCounter = other.planCounter;
    for (BaseAction *b : actionsLog)
        delete b;
    for (BaseAction *b : other.actionsLog)
        actionsLog.push_back(b->clone());
    for (Settlement *s : settlements)
        delete s;
    for (Settlement *s : other.settlements)
        settlements.push_back(s->clone());
    for (Plan p : plans)
        plans.pop_back();
    for (const Plan &p : other.plans)
        plans.push_back(p);
    for (FacilityType f : facilitiesOptions)
        facilitiesOptions.pop_back();
    for (FacilityType f : other.facilitiesOptions)
        facilitiesOptions.push_back(f);
}
void Simulation::start()
{
    string input;
    while (isRunning)
    {
        std::getline(std::cin, input);
        std::vector<std::string> words = Auxiliary::parseArguments(input);
        BaseAction *b;
        if (words[0] == "step")
        {
            int numberOfSteps = std::stoi(words[1]);
            b = new SimulateStep(numberOfSteps);
        }
        else if (words[0] == "plan")
        {
            b = new AddPlan(words[1], words[2]);
        }
        else if (words[0] == "settlement")
        {
            SettlementType setType;
            bool SettlementTypeEx = false;
            switch (std::stoi(words[2]))
            {
            case 0:
                setType = SettlementType::VILLAGE;
                SettlementTypeEx = true;
                break;
            case 1:
                setType = SettlementType::CITY;
                SettlementTypeEx = true;
                break;
            case 2:
                setType = SettlementType::METROPOLIS;
                SettlementTypeEx = true;
                break;
            }
            if (!SettlementTypeEx)
            {
                cout << "Invalid settlement type" << endl;
            }
            else
            {
                b = new AddSettlement(words[1], setType);
            }
        }
        else if (words[0] == "facility")
        {
            FacilityCategory c;
            bool CategoryEx = false;
            switch (std::stoi(words[2]))
            {
            case 0:
                c = FacilityCategory::ECONOMY;
                CategoryEx = true;
                break;
            case 1:
                c = FacilityCategory::ENVIRONMENT;
                CategoryEx = true;
                break;
            case 2:
                c = FacilityCategory::LIFE_QUALITY;
                CategoryEx = true;
                break;
            }
            if (!CategoryEx)
            {
                cout << "Invalid facility category" << endl;
            }
            else
            {
                int price = std::stoi(words[3]);
                int life_impact = std::stoi(words[4]);
                int eco_impact = std::stoi(words[5]);
                int env_impact = std::stoi(words[6]);
                b = new AddFacility(words[1], c, price, life_impact, eco_impact, env_impact);
            }
        }
        else if (words[0] == "planStatus")
        {
            b = new PrintPlanStatus(std::stoi(words[1]));
        }
        else if (words[0] == "changePolicy")
        {
            b = new ChangePlanPolicy(std::stoi(words[1]), words[2]);
        }
        else if (words[0] == "planStatus")
        {
            b = new PrintPlanStatus(std::stoi(words[1]));
        }
        else if (words[0] == "log")
        {
            b = new ChangePlanPolicy(std::stoi(words[1]), words[2]);
        }
        else if (words[0] == "close")
        {
            b = new Close();
        }
        else if (words[0] == "backup")
        {
            b = new BackupSimulation();
        }
        else if (words[0] == "restore")
        {
            b = new RestoreSimulation();
        }
        else
        {
            cout << "Wrong Syntax" << endl;
        }
        b->act(*this);
        addAction(b);
    }
}
void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy)
{
    plans.push_back(Plan(planCounter, settlement, selectionPolicy, facilitiesOptions));
    planCounter++;
}

void Simulation::addAction(BaseAction *action)
{
    actionsLog.push_back(action);
}
bool Simulation::addSettlement(Settlement *settlement)
{
    settlements.push_back(settlement);
}
bool Simulation::addFacility(FacilityType facility)
{
    facilitiesOptions.push_back(facility);
}
bool Simulation::isSettlementExists(const string &settlementName)
{
    for (Settlement *s : settlements)
    {
        if (s->getName() == settlementName)
        {
            return true;
        }
    }
    return false;
}
vector<BaseAction *> &Simulation::getActionLogs()
{
    return actionsLog;
}
bool Simulation::isFacilityExists(const string &facilityName)
{
    for (FacilityType f : facilitiesOptions)
    {
        if (f.getName() == facilityName)
        {
            return true;
        }
    }
    return false;
}
Settlement &Simulation::getSettlement(const string &settlementName)
{
    for (Settlement *s : settlements)
    {
        if (s->getName() == settlementName)
        {
            return *s;
        }
    }
}
Plan &Simulation::getPlan(const int planID)
{
    for (Plan p : plans)
    {
        if (p.getId() == planID)
        {
            return p;
        }
    }

}
void Simulation::step()
{
    for (Plan p : plans)
    {
        p.step();
    }
}
//  void Simulation::changePolicy();
void Simulation::close()
{
    isRunning = false;
    for (Plan p : plans)
        cout << p.toString() << endl;
}
Simulation *Simulation::clone() const
{
    Simulation *s = new Simulation(isRunning, planCounter);
    for (BaseAction *b : actionsLog)
    {
        s->actionsLog.push_back(b->clone());
    }
    for (Settlement *se : (*this).settlements)
    {
        (s->settlements).push_back(se->clone());
    }
    for (const Plan &p : plans)
    {
        (s->plans).push_back(p);
    }
    for (FacilityType f : facilitiesOptions)
    {
        (s->facilitiesOptions).push_back(f);
    }
    return s;
}
void Simulation::open()
{
    isRunning = true;
}
