#pragma once
#include <vector>
#include "Facility.h"
using std::vector;

enum class SelectionPolicyType
{
    BALANCE,
    NAIVE,
    ECO,
    SUB
};
class SelectionPolicy {
    public:
        virtual const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) = 0;
        virtual const string toString() const = 0;
        virtual SelectionPolicy* clone() const = 0;
        virtual ~SelectionPolicy() = default;
        virtual SelectionPolicyType getType() const =0;
};

class NaiveSelection: public SelectionPolicy {
    public:
        NaiveSelection();
        NaiveSelection(const NaiveSelection &n);
        const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        const string toString() const override;
        NaiveSelection* clone() const override;
        ~NaiveSelection() override = default;
        SelectionPolicyType getType() const;
    private:
        int lastSelectedIndex;
};

class BalancedSelection: public SelectionPolicy {
    public:
        BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore);
        const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        const string toString() const override;
        BalancedSelection *clone() const override;
        ~BalancedSelection() override = default;
        BalancedSelection(const BalancedSelection &b);
        void addScores(int LifeQualityScore, int EconomyScore, int EnvironmentScore);
        SelectionPolicyType getType() const;
    private:
        int LifeQualityScore;
        int EconomyScore;
        int EnvironmentScore;
};

class EconomySelection: public SelectionPolicy {
    public:
        EconomySelection();
        const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        const string toString() const override;
        EconomySelection *clone() const override;
        EconomySelection(const EconomySelection &e);
        ~EconomySelection() override = default;
        SelectionPolicyType getType() const;
    private:
        unsigned int lastSelectedIndex;

};

class SustainabilitySelection: public SelectionPolicy {
    public:
        SustainabilitySelection();
        const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        const string toString() const override;
        SustainabilitySelection *clone() const override;
        ~SustainabilitySelection() override = default;
        SustainabilitySelection(const SustainabilitySelection &s);
        SelectionPolicyType getType() const;
    private:
        int lastSelectedIndex;
};