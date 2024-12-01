#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Action.h"
using namespace std;

string BaseAction::getStatusString() const
{
    string strStatus;
    switch (status)
    {
    case ActionStatus::COMPLETED:
        strStatus = "COMPLETED";
    case ActionStatus::ERROR:
        strStatus = "ERROR";
    default:
        strStatus = "Unknown";
    }
    return "Status: " + strStatus;
}
BaseAction::BaseAction() {}
BaseAction::BaseAction(string &errorMsg, ActionStatus status) : errorMsg(errorMsg), status(status) {}
ActionStatus BaseAction::getStatus() const
{
    return status;
}
void BaseAction::complete()
{
    status = ActionStatus::COMPLETED;
}
void BaseAction::setStatusToError()
{
    status = ActionStatus::ERROR;
}
void BaseAction::error(string errorMsg)
{
    std::cout << "Error: <" + errorMsg + ">" << std::endl;
}
const string &BaseAction::getErrorMsg() const
{
    return errorMsg;
}

SimulateStep::SimulateStep(const int numOfSteps) : BaseAction(), numOfSteps(numOfSteps), restNum(numOfSteps)
{
}
void SimulateStep::act(Simulation &simulation)
{
    while (restNum > 0)
    {
        simulation.step();
        numOfSteps--;
    }
}
const string toString() const override;
SimulateStep *clone() const override;

private:
const int numOfSteps;

class AddPlan : public BaseAction
{
public:
    AddPlan(const string &settlementName, const string &selectionPolicy) : BaseAction(), settlementName(settlementName), selectionPolicy(selectionPolicy), policy = nullptr
    {
        switch (selectionPolicy)
        {
        case "nve":
            policy = new NaiveSelection();
        case "bal":
            policy = new BalancedSelection(0, 0, 0);
        case "eco":
            policy = new EconomySelection();
        case "eco":
            policy = new SustainabilitySelection(); // check and change to string
        default:
            error("Cannot create this plan");
            ActionStatus = ActionStatus::ERROR;
        }
    }
    const string SimulateStep::toString() const
    {
        return "SimulateStep " + numOfSteps + BaseAction::getStatusString(getStatus());
    }
    // SimulateStep *clone() const override;

    AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy) : BaseAction(), settlementName(settlementName), selectionPolicy(selectionPolicy), policy(nullptr)
    {
        if (selectionPolicy == "nve")
        {
            policy = new NaiveSelection();
        }
        else if (selectionPolicy == "bal")
        {
            policy = new BalancedSelection(0, 0, 0);
        }
        else if (selectionPolicy == "eco")
        {
            policy = new EconomySelection();
        }
        else if (selectionPolicy == "env")
        {
            policy = new SustainabilitySelection();
        }
        else
        {
            error("Cannot create this plan");
            BaseAction::setStatusToError();
        }
    }
    void AddPlan::act(Simulation &simulation)
    {
        if (!simulation.isSettlementExists(settlementName) || BaseAction::getStatus() == ActionStatus::ERROR)
        {
            error("Cannot create this plan");
            BaseAction::setStatusToError();
        }
        else
        {
            simulation.addPlan(simulation.getSettlement(settlementName), policy);
        }
    }
    const string AddPlan::toString() const
    {
        return "AddPlan " + settlementName + selectionPolicy + policy->toString() + BaseAction::getStatusString(getStatus());
    }
    // AddPlan *clone() const override;

    AddSettlement::AddSettlement(const string &settlementName, SettlementType settlementType) : BaseAction(), settlementName(settlementName), settlementType(settlementType)
    {
    }
    void AddSettlement::act(Simulation &simulation)
    {
        if (simulation.isSettlementExists(settlementName))
        {
            error("Settlement already exists");
            BaseAction::setStatusToError();
        }
        else
        {
            simulation.addSettlement(new Settlement(settlementName, settlementType));
        }
    }
    // AddSettlement *clone() const override;
    const string AddSettlement::toString() const
    {
        return "AddSettlement " + settlementName + settlementType + BaseAction::getStatusString(getStatus());
    }

    AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore) : BaseAction(), facilityName(facilityName), facilityCategory(facilityCategory), price(price), lifeQualityScore(lifeQualityScore), economyScore(economyScore), environmentScore(environmentScore) {}
    void AddFacility::act(Simulation &simulation)
    {
        if (!simulation.isFacilityExists(facilityName))
        {
            simulation.addFacility(FacilityType(facilityName, facilityCategory, price, lifeQualityScore, economyScore, environmentScore));
        }
        else
        {
            error("Facility already exists");
            BaseAction::setStatusToError();
        }
    }
    // AddFacility *clone() const override;
    const string AddFacility::toString() const
    {
        return "AddFacility " + facilityName + facilityCategory + price + lifeQualityScore + economyScore + environmentScore + BaseAction::getStatusString(getStatus());
    }

    PrintPlanStatus::PrintPlanStatus(int planId) : BaseAction(), planId(planId)
    {
    }
    void PrintPlanStatus::act(Simulation &simulation)
    {
        if (&simulation.getPlan(planId))
        {
            simulation.getPlan(planId).toString();
        }
        else
        {
            error("Plan doesn’t exist”");
            BaseAction::setStatusToError();
        }
    }
    // PrintPlanStatus* PrintPlanStatus::clone() const override;
    const string PrintPlanStatus::toString() const
    {
        return "PrintPlanStatus " + planId + BaseAction::getStatusString(getStatus());
    }

    ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy) : BaseAction(), planId(planId), newPolicy(newPolicy) {}
    void ChangePlanPolicy::act(Simulation &simulation)
    {
        SelectionPolicy *policy = nullptr;
        if (newPolicy == "nve")
        {
            policy = new NaiveSelection();
        }
        else if (newPolicy == "bal")
        {
            policy = new BalancedSelection(simulation.getPlan(planId).getlifeQualityScore() + simulation.getPlan(planId).getlifeQualityScoreUnderConstruction(), simulation.getPlan(planId).getEconomyScore() + simulation.getPlan(planId).getEconomyScoreUnderConstruction(), simulation.getPlan(planId).getEnvironmentScore() + simulation.getPlan(planId).getEnvironmentScoreUnderConstruction());
        }
        else if (newPolicy == "eco")
        {
            policy = new EconomySelection();
        }
        else if (newPolicy == "env")
        {
            policy = new SustainabilitySelection();
        }
        if (policy != nullptr)
        {
            if (simulation.getPlan(planId).getSelectionPolicy().toString() == policy->toString())
            {
                error("Cannot change selection policy");
                BaseAction::setStatusToError();
            }
            else
            {
                simulation.getPlan(planId).setSelectionPolicy(policy);
            }
        }
        else
        {
            error("Cannot change selection policy");
            BaseAction::setStatusToError();
        }
    }
    //         ChangePlanPolicy *clone() const override;
    const string ChangePlanPolicy::toString() const
    {
        return "ChangePlanPolicy " + planId + newPolicy + BaseAction::getStatusString(getStatus());
    }

    PrintActionsLog::PrintActionsLog() {}
    void PrintActionsLog::act(Simulation &simulation)
    { // simulation
        for (BaseAction *b : simulation.getActionLogs())
        {
            cout << *b->toString() << endl;
        }
    }
    // PrintActionsLog* PrintActionsLog::clone() const override;
    const string PrintActionsLog::toString() const
    {
        return "PrintActionsLog " + BaseAction::getStatusString(getStatus());
    }

    class Close : public BaseAction
    {
    public:
        Close::Close()
        {
        }
        void Close::act(Simulation &simulation)
        {
            simulation.close();
        }
        // Close * Close::clone() const;
        const string Close::toString() const
        {
        }

        BackupSimulation::BackupSimulation()
        {
        }
        void BackupSimulation::act(Simulation &simulation)
        {
            if (!backup)
            {
                delete backup;
            }
            backup = simulation.clone();
        }
        // BackupSimulation *clone() const override;
        // const string toString() const override;

        RestoreSimulation::RestoreSimulation()
        {
        }
        void RestoreSimulation::act(Simulation &simulation)
        {
            if (backup)
            {
                simulation = backup;
            }
            else
            {
                error("No backup available");
                BaseAction::setStatusToError();
            }
        }
        // RestoreSimulation *clone() const override;
        // const string toString() const override;
