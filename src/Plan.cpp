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
        (*this).selectionPolicy = selectionPolicy;
        cout << "newPolicy: " << *selectionPolicy << endl;
    }
}
// void step();
void Plan::printStatus()
{
    cout << "the plan status is" << PlanStatus << endl;
}
const vector<Facility *> &Plan::getFacilities() const
{
    return facilities;
}
// void Plan::addFacility(Facility *facility)
// {
// }
// const string toString() const;