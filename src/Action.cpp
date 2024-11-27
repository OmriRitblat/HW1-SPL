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
        const string &getErrorMsg() const{
            return errorMsg;
        }

        SimulateStep::SimulateStep(const int numOfSteps):BaseAction(),numOfSteps(numOfSteps){
        }
        void act(Simulation &simulation) override;
        const string toString() const override;
        SimulateStep *clone() const override;
    private:
        const int numOfSteps;
};

class AddPlan : public BaseAction {
    public:
        AddPlan(const string &settlementName, const string &selectionPolicy);
        void act(Simulation &simulation) override;
        const string toString() const override;
        AddPlan *clone() const override;
    private:
        const string settlementName;
        const string selectionPolicy;
};


class AddSettlement : public BaseAction {
    public:
        AddSettlement(const string &settlementName,SettlementType settlementType);
        void act(Simulation &simulation) override;
        AddSettlement *clone() const override;
        const string toString() const override;
    private:
        const string settlementName;
        const SettlementType settlementType;
};



class AddFacility : public BaseAction {
    public:
        AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore);
        void act(Simulation &simulation) override;
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
        PrintPlanStatus(int planId);
        void act(Simulation &simulation) override;
        PrintPlanStatus *clone() const override;
        const string toString() const override;
    private:
        const int planId;
};


class ChangePlanPolicy : public BaseAction {
    public:
        ChangePlanPolicy(const int planId, const string &newPolicy);
        void act(Simulation &simulation) override;
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