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
        void BaseAction::setStatusToError(){
            status = ActionStatus::ERROR;
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
        const string SimulateStep::toString() const {
            return "SimulateStep";
        }
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
            else if (selectionPolicy == "eco_sustainability") {
                policy = new SustainabilitySelection();
            }
            else {
                error("Cannot create this plan");
                 BaseAction::setStatusToError();
            }
}
        void AddPlan::act(Simulation &simulation){
            if(!simulation.isSettlementExists(settlementName)|| BaseAction::getStatus()==ActionStatus::ERROR){
                error("Cannot create this plan");
                 BaseAction::setStatusToError();
            }
            else{
                simulation.addPlan(simulation.getSettlement(settlementName),policy);
            }
        }
        const string AddPlan::toString() const{
            return "AddPlan";
        }
        //AddPlan *clone() const override;


        AddSettlement::AddSettlement(const string &settlementName,SettlementType settlementType):BaseAction(),settlementName(settlementName),settlementType(settlementType){
        }
        void AddSettlement::act(Simulation &simulation){
            if (simulation.isSettlementExists(settlementName)){
                error("Settlement already exists");
                 BaseAction::setStatusToError();
            }
            else{
                simulation.addSettlement(new Settlement(settlementName,settlementType));
            }
        }
        //AddSettlement *clone() const override;
        const string  AddSettlement::toString() const{
            return " AddSettlement";
        }




        AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore):BaseAction(),facilityName(facilityName),facilityCategory(facilityCategory),price(price),lifeQualityScore(lifeQualityScore),economyScore(economyScore),environmentScore(environmentScore){}
        void AddFacility::act(Simulation &simulation){
            if (!simulation.isFacilityExists(facilityName))
            {
                simulation.addFacility(FacilityType(facilityName,facilityCategory,price,lifeQualityScore,economyScore,environmentScore));
            }
            else{
                error("Facility already exists");
                 BaseAction::setStatusToError();
            }
            
        }
        //AddFacility *clone() const override;
        const string AddFacility::toString() const{
            return "AddFacility";
        }

                PrintPlanStatus::PrintPlanStatus(int planId):BaseAction(),planId(planId){
                }
                void PrintPlanStatus::act(Simulation &simulation){
                    if(&simulation.getPlan(planId)){
                        simulation.getPlan(planId).toString();
                    }
                    else{
                        error("Plan doesn’t exist”");
                        BaseAction::setStatusToError();
                }
                }
               // PrintPlanStatus* PrintPlanStatus::clone() const override;
             const string PrintPlanStatus:: toString() const{
                return "PrintPlanStatus";
             }


                    ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy):BaseAction(),planId(planId),newPolicy(newPolicy){}
                    void ChangePlanPolicy::act(Simulation &simulation) {
                        SelectionPolicy* policy = nullptr;
                        if (newPolicy == "nve") {
                            policy = new NaiveSelection();
                        } else if (newPolicy == "bal") {
                            policy = new BalancedSelection(0, 0, 0);
                        } else if (newPolicy == "eco") {
                            policy = new EconomySelection();
                        } else if (newPolicy == "eco_sustainability") {//fix
                            policy = new SustainabilitySelection();
                        }
                        if (policy != nullptr) {
                            if( simulation.getPlan(planId).getSelectionPolicy().toString()==policy->toString()){
                                error("Cannot change selection policy");
                                BaseAction::setStatusToError();
                            }
                            else{
                                simulation.getPlan(planId).setSelectionPolicy(policy);
                            }
                        } else {
                            error("Cannot change selection policy");
                            BaseAction::setStatusToError();
                        }
                    }
            //         ChangePlanPolicy *clone() const override;
            //         const string toString() const override;

                    PrintActionsLog::PrintActionsLog(){}
                    void PrintActionsLog::act(Simulation &simulation){//simulation

                    }
                    PrintActionsLog* PrintActionsLog::clone() const override;
                    const string PrintActionsLog::toString() const override;

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