#include "Plan.h"
#include <algorithm> // for find function in vector
#include <iostream>
#include <sstream>
using namespace std;

Plan::Plan(const int planId, const Settlement & settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions) : plan_id(planId), settlement(settlement), selectionPolicy(selectionPolicy), status(PlanStatus::AVALIABLE), facilities(), underConstruction(), facilityOptions(facilityOptions), life_quality_score(0), economy_score(0), environment_score(0)
{
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
    underConstruction.clear();
}
Plan::Plan(const Plan &other) : Plan(other.plan_id, other.settlement, nullptr, other.facilityOptions)
{
    selectionPolicy = other.selectionPolicy->clone();
    for (Facility *f : other.facilities)
        facilities.push_back(f->clone());
    for (Facility *f : other.underConstruction)
        underConstruction.push_back(f->clone());
    this->life_quality_score = other.life_quality_score;
    this->economy_score = other.economy_score;
    this->environment_score = other.environment_score;
}
Plan::Plan(Plan &&other) : Plan(other.plan_id, other.settlement, other.selectionPolicy, other.facilityOptions)
{
    underConstruction = other.underConstruction;
    facilities = other.facilities;
    other.selectionPolicy = nullptr;
    other.facilities.clear();
    other.underConstruction.clear();
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
const int Plan::getlifeQualityScoreUnderConstruction() const
{
    int sum = 0;
    for (Facility *f : this->underConstruction)
    {
        if (f)
            sum += (*f).getLifeQualityScore();
    }
    return sum;
}
const int Plan::getEconomyScoreUnderConstruction() const
{
    int sum = 0;
    for (Facility *f : this->underConstruction)
    {
        if (f)
            sum += (*f).getEconomyScore();
    }
    return sum;
}
const int Plan::getEnvironmentScoreUnderConstruction() const
{
    int sum = 0;
    for (Facility *f : underConstruction)
    {
        if (f)
            sum += (*f).getEnvironmentScore();
    }
    return sum;
}
const SelectionPolicy *Plan::getSelectionPolicy() const
{
    return selectionPolicy;
}
void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy)
{
    if (selectionPolicy == this->selectionPolicy)
        cout << "Cannot change selection policy" << endl;
    else
    {
        cout << "plan ID: " << plan_id << endl;
        cout << "previousPolicy: " << (this->selectionPolicy)->toString() << endl;
        this->selectionPolicy = selectionPolicy->clone();
        cout << "newPolicy: " << (this->selectionPolicy)->toString() << endl;
    }
}
void Plan::step()
{
    if (this->status == PlanStatus::AVALIABLE)
    {
        unsigned int index(underConstruction.size());
        while (index < settlement.maxPacilities())
        {
            FacilityType type = selectionPolicy->selectFacility(facilityOptions);
            Facility *facility = new Facility(type, settlement.getName());
            this->addFacility(facility);
            index++;
        }
    }
    for (unsigned int i=0;i<underConstruction.size();i++)
    {
        if (underConstruction[i]->step() == FacilityStatus::OPERATIONAL){
            this->addFacility(underConstruction[i]);
        }
    }
    this->updateStatus();
}
string Plan::getStatusString() const
{
    string strStatus;
    switch (status)
    {
    case PlanStatus::AVALIABLE:
        strStatus = "AVALIABLE";
        break; // Prevent fall-through
    case PlanStatus::BUSY:
        strStatus = "BUSY";
        break; // Prevent fall-through
    default:
        strStatus = "Unknown";
        break;
    }

    return strStatus;
}
const vector<Facility *> &Plan::getFacilities() const
{
    return facilities;
}
const int Plan::findIndexInVector(const vector<Facility *> &vec, Facility *facility) const
{
    auto it = std::find(vec.begin(), vec.end(), facility); // Find the pointer
    if (it != vec.end())
    {
        return std::distance(vec.begin(), it); // Return the index
    }
    return -1; // Pointer not found
}

void Plan::addFacility(Facility *facility) ////////////////////////////////////////////////////////////////////////////////////////////
{
    // check where to add the Facility
    // if the facility already in the under constructer it shloud move to the facilities vector
    int indexInVector(this->findIndexInVector(underConstruction, facility));
    if (indexInVector > -1)
    {
        this->updateScore(facility);
        facilities.push_back(facility);
        //        delete underConstruction[indexInVector];
        underConstruction.erase(underConstruction.begin() + indexInVector);
    }
    // else the facility enters the under construction vector
    else
    {
        underConstruction.push_back(facility);
    }
}

void Plan::updateScore(const Facility *facility)
{
    this->economy_score += facility->getEconomyScore();
    this->environment_score += facility->getEnvironmentScore();
    this->life_quality_score += facility->getLifeQualityScore();
}

void Plan::updateStatus()
{
    if (settlement.maxPacilities() > underConstruction.size())
        status = PlanStatus::AVALIABLE;
    else
        status = PlanStatus::BUSY;
}

const string Plan::toString() const
{
    std::ostringstream output;
    output << "PlanID: " << plan_id << '\n';
    output << "SettlementName: " << settlement.getName() << '\n';
    output << "PlanStatus: " << this->getStatusString() << '\n';
    output << "SelectionPolicy: " << selectionPolicy->toString() << '\n';
    output << "LifeQualityScore: " << life_quality_score << '\n';
    output << "EconomyScore: " << economy_score << '\n';
    output << "EnvironmentScore: " << environment_score << '\n';
    for (Facility *facility : underConstruction)
    {
        output << facility->toString() << '\n';
    }
    return output.str();
}

// Updated Plan::collectFacilities
// const string Plan::FacilityToString(const vector<Facility *> &facilities)
// {
//     std::ostringstream facilityOutput;
//     for (Facility *facility : facilities)
//     {
//         if (facility)
//         { // Ensure pointer is not null
//             facilityOutput << facility->toString() << '\n';
//         }
//     }
//     return facilityOutput.str();
// }
const int Plan::getId() const
{
    return plan_id;
}
