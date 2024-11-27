#pragma once
#include <string>
#include <vector>
#include "Simulation.h"
using std::string;
using std::vector;

        Simulation::Simulation(const string &configFilePath);
        void Simulation::start(){
            string input;
            while (isRunning)
            {
                std::cin >> input;
                std::vector<std::string> words = splitStringBySpaces(input);
                switch (words[0]) {
                    case "step":
                        int numberOfSteps=std::stoi(words[1]);
                        BaseAction* b=new SimulateStep(numberOfSteps);
                        *b.act(*this)
                    case "plan":
                        BaseAction* b=new addPlan(words[1],words[2]);
                        *b.act(*this);
                        actionsLog.push_back(b);
                    case "settlement":
                        SettlementType setType;
                        bool SettlementTypeEx=false;
                        switch (std::stoi(words[2]))
                        {
                        case 0:
                            setType=SettlementType::VILLAGE;
                            SettlementTypeEx=true;
                            break;
                        case 1:
                            setType=SettlementType::CITY;
                            SettlementTypeEx=true;
                            break;
                        case 2:
                            setType=SettlementType::METROPOLIS;
                            SettlementTypeEx=true;
                            break;
                        }
                        if(!SettlementTypeEx){
                           break; 
                        }
                        BaseAction* b=new addSettlement(words[1],setType);
                        *b.act(*this);
                        actionsLog.push_back(b);
                    case "facility":
                        FacilityCategory c;
                        bool CategoryEx=false;
                        switch (std::stoi(words[2]))
                        {
                        case 0:
                            c=FacilityCategory::ECONOMY;
                            CategoryEx=true;
                            break;
                        case 1:
                            c=FacilityCategory::ENVIRONMENT;
                            CategoryEx=true;
                            break;
                        case 2:
                            c=FacilityCategory::LIFE_QUALITY;
                            CategoryEx=true;
                            break;
                        }
                        if(!CategoryEx){
                           break; 
                        }
                        int price=std::stoi(word[3]);
                        int life_impact=std::stoi(word[4]);
                        int eco_impact=std::stoi(word[5]);
                        int env_impact=std::stoi(word[6]);
                        BaseAction* b=new addFacility(words[1],c,price,life_impact,eco_impact,env_impact);
                        *b.act(*this);
                        actionsLog.push_back(b);
                    case "planStatus"://needs get id and to string in plan
                       BaseAction* b=new PrintPlanStatus("need id");
                        *b.act(*this);
                        actionsLog.push_back(b); 
                    case "changePolicy"://needs get id and to string in plan
                       BaseAction* b=new ChangePlanPolicy("need id",words[2]);
                        *b.act(*this);
                        actionsLog.push_back(b); 
                    default:      
                        cout << "wrong Syntex" << endl;
                        break;;
        }
            }
            
        }
        void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy){
            plans.push_back(Plan(planCounter,settlement,selectionPolicy,vector<FacilityType>));
            planCounter++;
        }
        void Simulation::addAction(BaseAction *action);
        bool Simulation::addSettlement(Settlement *settlement){
            settlements.push_back(settlement);
        }
        bool Simulation::addFacility(FacilityType facility){
            facilitiesOptions.push_back(facility);
        }
        bool Simulation::isSettlementExists(const string &settlementName){
            for(Settlement* s:settlements){
                    if (*s->getName()==settlementName)
                    {
                        return true;
                    }
            }
            return false;
        }
        bool Simulation::isFacilityExists(const string &facilityName){
                for(FacilityType f:facilitiesOptions){
                    if (f->getName()==facilityName)
                    {
                        return true;
                    }
                }
            return false;
        }
        Settlement &Simulation::getSettlement(const string &settlementName){
             for(Settlement* s:settlements){
                if (*s->getName()==words[1])
                {
                    return *s;
                }
             }
        }
        Plan &Simulation::getPlan(const int planID);
        void Simulation::step(){
            for(Plan p:plans){
                p.step();
            }
        }
        void Simulation::changePolicy();
        void Simulation::close();
        void Simulation::open();

    private:
        bool isRunning;
        const int planCounter; //For assigning unique plan IDs
        vector<BaseAction*> actionsLog;
        vector<Plan> plans;
        vector<Settlement*> settlements;
        vector<FacilityType> facilitiesOptions;
};