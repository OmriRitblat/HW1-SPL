#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Action.h"


        BaseAction::BaseAction(){}
        BaseAction::BaseAction(string &errorMsg,ActionStatus status):errorMsg(errorMsg),status(status){}
        ActionStatus BaseAction::getStatus() const{
            return status;
        }
        virtual void BaseAction:: act(Simulation& simulation)=0;
        virtual const BaseAction:: string toString() const=0;
        virtual BaseAction* BaseAction:: clone() const = 0;
        virtual BaseAction:: ~BaseAction() = default;
        void BaseAction:: complete(){
            status=COMPLETED;
        }
        void BaseAction::error(string errorMsg){
            cout << "Error: <"errorMsg+">" << endl;
        }
        const string& BaseAction::getErrorMsg() const{
            return errorMsg;
        }

        SimulateStep::SimulateStep(const int numOfSteps):BaseAction(),numOfSteps(numOfSteps){
        }
        void SimulateStep::act(Simulation &simulation) override{
            while (numOfSteps>0)
            {
                simulation.step();
                numOfSteps--;
            }
            
        }
        const string toString() const override;
        SimulateStep *clone() const override;
    private:
        const int numOfSteps;

class AddPlan : public BaseAction {
    public:
        AddPlan(const string &settlementName, const string &selectionPolicy):BaseAction(),settlementName(settlementName),selectionPolicy(selectionPolicy),policy=nullptr{
            switch (selectionPolicy) {
                case "nve": policy=new NaiveSelection();
                case "bal": policy=new BalancedSelection(0,0,0);
                case "eco": policy=new EconomySelection();
                case "eco": policy=new SustainabilitySelection();
                default:   
                    error("Cannot create this plan");  
                    ActionStatus=ActionStatus::ERROR;
            }
        }
        void act(Simulation &simulation) override{
            if(!simulation.isSettlementExists()){
                error("Cannot create this plan");
                ActionStatus=ActionStatus::ERROR;
            }
            else{
                simulation.addPlan(simulation.getSettlement(settlementName),policy);
                ActionStatus=ActionStatus::COMPLETED;
            }
        }
        const string toString() const override;
        AddPlan *clone() const override;
    private:
        const string settlementName;
        const string selectionPolicy;
        SelectionPolicy* policy;
};


class AddSettlement : public BaseAction {
    public:
        AddSettlement(const string &settlementName,SettlementType settlementType):BaseAction(),settlementName(settlementName),settlementType(settlementType){
        }
        void act(Simulation &simulation) override{
            if (simulation.isSettlementExists()){
                error("Settlement already exists")
                ActionStatus=ActionStatus::ERROR;
            }
            else{
                simulation.addSettlement(new Settlement(settlementName,settlementType));
            }
        }
        AddSettlement *clone() const override;
        const string toString() const override;
    private:
        const string settlementName;
        const SettlementType settlementType;
};



class AddFacility : public BaseAction {
    public:
        AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore)
        :BaseAction(),facilityName(facilityName),facilityCategory(facilityCategory),price(price),lifeQualityScore(lifeQualityScore),economyScore(economyScore),environmentScore(environmentScore){}
        void act(Simulation &simulation) override{
            if (!simulation.isFacilityExists())
            {
                simulation.addFacility(FacilityType(facilityName,facilityCategory,price,lifeQualityScore,economyScore,environmentScore));
            }
            else{
                error("Facility already exists");
                ActionStatus=ActionStatus::ERROR;
            }
            
        }
        AddFacility *clone() const override;
        const string toString() const override;
    private:
        const string facilityName;
        const FacilityCategory facilityCategory;
        const int price;
        const int lifeQualityScore;
        const int economyScore;
        const int environmentScore;

};

class PrintPlanStatus: public BaseAction {
    public:
        PrintPlanStatus(int planId):BaseAction(),planId(planId){
        }
        void act(Simulation &simulation) override;
        PrintPlanStatus *clone() const override;
        const string toString() const override;
    private:
        const int planId;
};


class ChangePlanPolicy : public BaseAction {
    public:
        ChangePlanPolicy(const int planId, const string &newPolicy):BaseAction(),planId(planId),newPolicy(newPolicy){}
        void act(Simulation &simulation) override{
            SelectionPolicy* policy=nullptr;
            switch (newPolicy) {
                case "nve": policy=new NaiveSelection();
                case "bal": policy=new BalancedSelection(0,0,0);
                case "eco": policy=new EconomySelection();
                case "eco": policy=new SustainabilitySelection();
                }
        }
        ChangePlanPolicy *clone() const override;
        const string toString() const override;
    private:
        const int planId;
        const string newPolicy;
};


class PrintActionsLog : public BaseAction {
    public:
        PrintActionsLog();
        void act(Simulation &simulation) override;
        PrintActionsLog *clone() const override;
        const string toString() const override;
    private:
};

class Close : public BaseAction {
    public:
        Close();
        void act(Simulation &simulation) override;
        Close *clone() const override;
        const string toString() const override;
    private:
};

class BackupSimulation : public BaseAction {
    public:
        BackupSimulation();
        void act(Simulation &simulation) override;
        BackupSimulation *clone() const override;
        const string toString() const override;
    private:
};


class RestoreSimulation : public BaseAction {
    public:
        RestoreSimulation();
        void act(Simulation &simulation) override;
        RestoreSimulation *clone() const override;
        const string toString() const override;
    private:
};