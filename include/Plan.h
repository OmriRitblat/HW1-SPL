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

    // rule of 3
    ~Plan();
    Plan(Plan &other);
    //void operator=(const Plan &other) = delete;

    // rule of 5
    Plan(Plan &&other);
    Plan &operator=(const Plan &&other) = delete;

    // getters
    const int getlifeQualityScore() const;
    const int getEconomyScore() const;
    const int getEnvironmentScore() const;
    string getStatusString() const;
    const vector<Facility *> &getFacilities() const;
    const int getId() const;
    const SelectionPolicy *getSelectionPolicy() const;

    // setters
    void setSelectionPolicy(SelectionPolicy *selectionPolicy);

    // other functions
    void step();
    void addFacility(Facility *facility);
    void NewFunction(Facility *facility);
    const string toString() const;

    //===================
    // should it be private??
    const string FacilityToString(const vector<Facility *> &facilities) const;
    const int findIndexInVector(const vector<Facility *> &vec, Facility *facility) const;
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
};