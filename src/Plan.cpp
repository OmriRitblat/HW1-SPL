#include "Plan.h"
#include <iostream>
using namespace std;

// Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions) : plan_id(planId), settlement(settlement), selectionPolicy(selectionPolicy), status(PlanStatus::AVALIABLE), facilities(facilityOptions), underConstruction(settlement.maxPacilities(), nullptr), life_quality_score(0), economy_score(0), environment_score(0){
// }
const int Plan::getlifeQualityScore() const
{
    return life_quality_score;
}
const int Plan::getEconomyScore() const
{
    return economy_score;
}
const int Plan::getEnvironmentScore() const
{
    return environment_score;
}
void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy)
{
    if (*selectionPolicy == *(*this).selectionPolicy)
        cout << "Cannot change selection policy" << endl;
    else
    {
        cout << "plan ID: " << plan_id << endl;
        cout << "previousPolicy: " << *selectionPolicy << endl;
        //===================================================
        // update what hapends when changing to balance policy
        *(*this).selectionPolicy = *selectionPolicy;
        cout << "newPolicy: " << *selectionPolicy << endl;
    }
}
// void step();
void Plan::printStatus()
{
    string strStatus;
    switch (status)
    {
    case PlanStatus::AVALIABLE:
        strStatus = "AVALIABLE";
    case PlanStatus::BUSY:
        strStatus = "BUSY";
    default:
        strStatus = "Unknown";
    }
    cout << "Status" << strStatus << endl;
}
const vector<Facility *> &Plan::getFacilities() const
{
    return facilities;
}
// void Plan::addFacility(Facility *facility)
// {
// }
const string Plan::toString() const
{
    std::ostringstream output;
    output << "PlanID: " << plan_id << '\n';
    output << "SettlementName: " << settlement.getName() << '\n';
    output << "PlanStatus: " << status << '\n';
    // output << "SelectionPolicy: " << SelectionPolicy.toString() << '\n';
    output << "LifeQualityScore: " << life_quality_score << '\n';
    output << "EconomyScore: " << economy_score << '\n';
    output << "EnvironmentScore: " << environment_score << '\n';

    // Collect facility info and append
    output << "Facilities:\n"
           << collectFacilities(underConstruction);
    return output.str();
}

// Updated Plan::collectFacilities
string Plan::collectFacilities(const std::vector<Facility *> &facilities) const
{
    std::ostringstream facilityOutput;
    for (const auto &facility : facilities)
    {
        if (facility)
        { // Ensure pointer is not null
            facilityOutput << facility->toString() << '\n';
        }
    }
    return facilityOutput.str();
}