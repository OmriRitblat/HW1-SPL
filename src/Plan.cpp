#include "Plan.h"
#include <iostream>
#include <sstream>
using namespace std;

Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions) : plan_id(planId), settlement(settlement), selectionPolicy(selectionPolicy), status(PlanStatus::AVALIABLE), facilityOptions(facilityOptions), underConstruction(settlement.maxPacilities(), nullptr), facilities(settlement.maxPacilities(), nullptr), life_quality_score(0), economy_score(0), environment_score(0)
{
    setSelectionPolicy(selectionPolicy);
}
Plan::Plan(Plan *other) : Plan((*other).getId, (*other).settlement, (*other).selectionPolicy, (*other).facilityOptions)
{
}
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
    if (selectionPolicy == this->selectionPolicy)
        cout << "Cannot change selection policy" << endl;
    else
    {
        cout << "plan ID: " << plan_id << endl;
        cout << "previousPolicy: " << (this->selectionPolicy)->toString() << endl;
        //===================================================
        // update what hapends when changing to balance policy
        delete this->selectionPolicy;
        this->selectionPolicy = selectionPolicy;
        cout << "newPolicy: " << (this->selectionPolicy)->toString() << endl;
    }
}
// void step();
string Plan::getStatusString() const
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
    return "Status" + strStatus;
}
const vector<Facility *> &Plan::getFacilities() const
{
    return facilities;
}

//================================
//================================
//================================
void Plan::addFacility(Facility *facility)
{
    // check if the facility is aleardy is the under constractor facility
    if (facility->getStatus(facility) == FacilityStatus::UNDER_CONSTRUCTIONS)
    {
        if (facility->getTimeLeft() > 0)
            facility->setTime(facility->getTimeLeft() - 1);
        else
    }
}
const string Plan::toString() const
{
    std::ostringstream output;
    output << "PlanID: " << plan_id << '\n';
    output << "SettlementName: " << settlement.getName() << '\n';
    output << "PlanStatus: " << this->getStatusString() << '\n';
    // output << "SelectionPolicy: " << SelectionPolicy.toString() << '\n';
    output << "LifeQualityScore: " << life_quality_score << '\n';
    output << "EconomyScore: " << economy_score << '\n';
    output << "EnvironmentScore: " << environment_score << '\n';

    // Collect facility info and append
    output << "Facilities:\n"
           << this->FacilityToString(this->underConstruction);
    return output.str();
}

// Updated Plan::collectFacilities
const string Plan::FacilityToString(const vector<Facility *> &facilities) const
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

Plan::~Plan()
{
    delete selectionPolicy;
    for (Facility *facility : facilities)
    {
        delete facility; // Deallocate memory for each facility
    }
    facilities.clear(); // Clear the vector (remove all elements)
    // Release memory for underConstruction
    for (Facility *facility : underConstruction)
    {
        delete facility; // Deallocate memory for each facility
    }
    delete selectionPolicy;
    cout << "Destructor: Memory deallocated" << endl;
}

Plan::Plan(Plan &&other):{

}

Plan::Plan &operator=(const Plan &other){
    
}
