
#include <string>
#include <vector>
#include <iostream>
#include "Action.h"
#include "Global.h"
#include "SelectionPolicy.h"

using namespace std;

string BaseAction::getStatusString() const
{
    string strStatus;

    if (status == ActionStatus::COMPLETED)
        strStatus = "COMPLETED";
    else
        strStatus = "ERROR";
    return strStatus;
}
BaseAction::BaseAction() : errorMsg(), status(ActionStatus::COMPLETED)
{
}
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

SimulateStep::SimulateStep(const int numOfSteps) : BaseAction(), numOfSteps(numOfSteps), restNum(0)
{
}
void SimulateStep::act(Simulation &simulation)
{
    while (restNum < numOfSteps)
    {
        simulation.step();
        restNum++;
    }
}

SimulateStep *SimulateStep::clone() const
{
    return new SimulateStep(*this);
}

const string SimulateStep::toString() const
{
    return "SimulateStep " + std::to_string(numOfSteps) + " ";
}

AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy) : BaseAction(), settlementName(settlementName), selectionPolicy(selectionPolicy), policy(nullptr)
{
    if (selectionPolicy == "nve")
    {
        this->policy = new NaiveSelection();
    }
    else if (selectionPolicy == "bal")
    {
        this->policy = new BalancedSelection(0, 0, 0);
    }
    else if (selectionPolicy == "eco")
    {
        this->policy = new EconomySelection();
    }
    else if (selectionPolicy == "env")
    {
        this->policy = new SustainabilitySelection();
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
AddPlan::~AddPlan()
{
    policy = nullptr;
}
const string AddPlan::toString() const
{
    return "AddPlan " + settlementName + selectionPolicy + policy->toString();
}
AddPlan *AddPlan::clone() const
{
    return new AddPlan(*this);
}

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
AddSettlement *AddSettlement::clone() const
{
    return new AddSettlement(*this);
}
const string AddSettlement::toString() const
{
    int index = static_cast<int>(settlementType);
    return "AddSettlement " + settlementName + " " + std::to_string(index);
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
AddFacility *AddFacility::clone() const
{
    return new AddFacility(*this);
}
const string AddFacility::toString() const
{
    return "AddFacility " + facilityName +
           FacilityType::getCategoryString(facilityCategory) +
           std::to_string(price) +
           std::to_string(lifeQualityScore) +
           std::to_string(economyScore) +
           std::to_string(environmentScore);
}

PrintPlanStatus::PrintPlanStatus(int planId) : BaseAction(), planId(planId)
{
}
void PrintPlanStatus::act(Simulation &simulation)
{
    if (simulation.planInRang(planId))
        cout << simulation.getPlan(planId).toString() << endl;
    else
    {
        error("Plan doesn’t exist”");
        BaseAction::setStatusToError();
    }
}
PrintPlanStatus *PrintPlanStatus::clone() const
{
    return new PrintPlanStatus(*this);
}
const string PrintPlanStatus::toString() const
{
    return "planStatus " + std::to_string(planId);
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
        if (simulation.getPlan(planId).getSelectionPolicy()->toString() == policy->toString())
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
ChangePlanPolicy *ChangePlanPolicy::clone() const
{
    return new ChangePlanPolicy(*this);
}
const string ChangePlanPolicy::toString() const
{
    return "ChangePlanPolicy " + planId + newPolicy;
}

PrintActionsLog::PrintActionsLog()
{
}
void PrintActionsLog::act(Simulation &simulation)
{ // simulation
    for (BaseAction *b : simulation.getActionLogs())
    {
        cout << b->toString() << " " << b->getStatusString() << endl;
    }
}
PrintActionsLog *PrintActionsLog::clone() const
{
    return new PrintActionsLog(*this);
}
const string PrintActionsLog::toString() const
{
    return "PrintActionsLog ";
}
Close::Close()
{
}
void Close::act(Simulation &simulation)
{
    simulation.close();
}
Close *Close::clone() const
{
    return new Close(*this);
}
const string Close::toString() const
{
    return "Close";
}

BackupSimulation::BackupSimulation()
{
}
void BackupSimulation::act(Simulation &simulation)
{
    if (::backup != nullptr)
    {
        delete ::backup;
    }
    // do with opertor =
    ::backup = &simulation;
}
BackupSimulation *BackupSimulation::clone() const
{
    return new BackupSimulation(*this);
}
const string BackupSimulation::toString() const
{
    return "backup";
}

RestoreSimulation::RestoreSimulation()
{
}
void RestoreSimulation::act(Simulation &simulation)
{
    if (backup!=nullptr)
    {
        simulation = *(::backup);
    }
    else
    {
        error("No backup available");
        BaseAction::setStatusToError();
    }
}
RestoreSimulation *RestoreSimulation::clone() const
{
    return new RestoreSimulation(*this);
}
const string RestoreSimulation::toString() const
{
    return "restore";
}
