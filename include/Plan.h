#pragma once
#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
using std::vector;

enum class PlanStatus
{
    AVALIABLE,
    BUSY,
};

class Plan
{ 
public:
    Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions);
    Plan(const Settlement &settlement, const Plan &other, const vector<FacilityType>& facilityOptions);
    // rule of 3
    ~Plan();
    Plan();
    Plan(const Plan &other);
    Plan operator=(const Plan &other) = delete;

    // rule of 5
    Plan(Plan &&other);
    Plan &operator=(const Plan &&other) = delete;

    // getters
    const int getlifeQualityScore() const;
    const int getEconomyScore() const;
    const int getEnvironmentScore() const;
    const int getlifeQualityScoreUnderConstruction() const;
    const int getEconomyScoreUnderConstruction() const;
    const int getEnvironmentScoreUnderConstruction() const;
    string getStatusString() const;
    const vector<Facility *> &getFacilities() const;
    const int getId() const;
    const SelectionPolicy *getSelectionPolicy() const;
    const string getSettlementName() const;

    // setters
    void setSelectionPolicy(SelectionPolicy *selectionPolicy);

    // other functions
    void step();
    void addFacility(Facility *facility);
    const string toString() const;
    const string sumUpSTotring() const;
    void updateStatus();
    void updateScore(const Facility *facility);

private:
    int plan_id;
    const Settlement &settlement;
    SelectionPolicy *selectionPolicy; // What happens if we change this to a reference?
    PlanStatus status;
    vector<Facility *> facilities;
    vector<Facility *> underConstruction;
    const vector<FacilityType> &facilityOptions;
    int life_quality_score, economy_score, environment_score;

    //functions
    const int findIndexInVector(const vector<Facility *> &vec, Facility *facility) const;
};