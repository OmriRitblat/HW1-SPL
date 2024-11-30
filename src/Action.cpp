#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Action.h"
using namespace std;


        BaseAction::BaseAction(){}
        BaseAction::BaseAction(string &errorMsg,ActionStatus status):errorMsg(errorMsg),status(status){}
        ActionStatus BaseAction::getStatus() const{
            return status;
        }
        void BaseAction:: complete(){
            status=ActionStatus::COMPLETED;
        }
        void BaseAction::error(string errorMsg){
            std::cout << "Error: <"+errorMsg+">" << std::endl;
        }
        const string& BaseAction::getErrorMsg() const{
            return errorMsg;
        }

        SimulateStep::SimulateStep(const int numOfSteps):BaseAction(),numOfSteps(numOfSteps),restNum(numOfSteps){
        }
        void SimulateStep::act(Simulation &simulation){
            while (restNum>0)
            {
                simulation.step();
                restNum--;
            }
        }
        //const string toString() const override;
        //SimulateStep *clone() const override;
    
        AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy):BaseAction(),settlementName(settlementName),selectionPolicy(selectionPolicy),policy(nullptr){
            if (selectionPolicy == "nve") {
                policy = new NaiveSelection();
            }
            else if (selectionPolicy == "bal") {
                policy = new BalancedSelection(0, 0, 0);
            }
            else if (selectionPolicy == "eco") {
                policy = new EconomySelection();
            }
            else if (selectionPolicy == "env") {
                policy = new SustainabilitySelection();
            }
            else {
                error("Cannot create this plan");
                ActionStatus = ActionStatus::ERROR;
            }
}
        }
        void AddPlan::act(Simulation &simulation){
            if(!simulation.isSettlementExists(settlementName)&||ActionStatus==ActionStatus::ERROR){
                error("Cannot create this plan");
                ActionStatus=ActionStatus::ERROR;
            }
            else{
                simulation.addPlan(simulation.getSettlement(settlementName),policy);
                ActionStatus=ActionStatus::COMPLETED;
            }
        }
       //const string toString() const override;
        //AddPlan *clone() const override;


        AddSettlement::AddSettlement(const string &settlementName,SettlementType settlementType):BaseAction(),settlementName(settlementName),settlementType(settlementType){
        }
        void AddSettlement::act(Simulation &simulation) override{
            if (simulation.isSettlementExists()){
                error("Settlement already exists")
                ActionStatus=ActionStatus::ERROR;
            }
            else{
                simulation.addSettlement(new Settlement(settlementName,settlementType));
            }
        }
        //AddSettlement *clone() const override;
        //const string toString() const override;




        AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore):BaseAction(),facilityName(facilityName),facilityCategory(facilityCategory),price(price),lifeQualityScore(lifeQualityScore),economyScore(economyScore),environmentScore(environmentScore){}
        void AddFacility::act(Simulation &simulation) override{
            if (!simulation.isFacilityExists())
            {
                simulation.addFacility(FacilityType(facilityName,facilityCategory,price,lifeQualityScore,economyScore,environmentScore));
            }
            else{
                error("Facility already exists");
                ActionStatus=ActionStatus::ERROR;
            }
            
        }
        //AddFacility *clone() const override;
        //const string toString() const override;

// class PrintPlanStatus: public BaseAction {
//     public:
//         PrintPlanStatus(int planId):BaseAction(),planId(planId){
//         }
//         void act(Simulation &simulation) override;
//         PrintPlanStatus *clone() const override;
//         const string toString() const override;
//     private:
//         const int planId;
// };


// class ChangePlanPolicy : public BaseAction {
//     public:
//         ChangePlanPolicy(const int planId, const string &newPolicy):BaseAction(),planId(planId),newPolicy(newPolicy){}
//         void act(Simulation &simulation) override{
//             SelectionPolicy* policy=nullptr;
//             switch (newPolicy) {
//                 case "nve": policy=new NaiveSelection();
//                 case "bal": policy=new BalancedSelection(0,0,0);
//                 case "eco": policy=new EconomySelection();
//                 case "eco": policy=new SustainabilitySelection();
//                 }
//         }
//         ChangePlanPolicy *clone() const override;
//         const string toString() const override;
//     private:
//         const int planId;
//         const string newPolicy;
// };


// class PrintActionsLog : public BaseAction {
//     public:
//         PrintActionsLog();
//         void act(Simulation &simulation) override;
//         PrintActionsLog *clone() const override;
//         const string toString() const override;
//     private:
// };

// class Close : public BaseAction {
//     public:
//         Close();
//         void act(Simulation &simulation) override;
//         Close *clone() const override;
//         const string toString() const override;
//     private:
// };

// class BackupSimulation : public BaseAction {
//     public:
//         BackupSimulation();
//         void act(Simulation &simulation) override;
//         BackupSimulation *clone() const override;
//         const string toString() const override;
//     private:
// };


// class RestoreSimulation : public BaseAction {
//     public:
//         RestoreSimulation();
//         void act(Simulation &simulation) override;
//         RestoreSimulation *clone() const override;
//         const string toString() const override;
//     private:
// };