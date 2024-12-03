
#include <vector>
#include "SelectionPolicy.h"
using std::vector;

NaiveSelection::NaiveSelection() : SelectionPolicy(), lastSelectedIndex(-1) {}
NaiveSelection::NaiveSelection(const NaiveSelection &n) : SelectionPolicy(), lastSelectedIndex(n.lastSelectedIndex)
{
}
const FacilityType &NaiveSelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
    lastSelectedIndex++;
    if (facilitiesOptions.size() <= (unsigned)lastSelectedIndex)
    {
        lastSelectedIndex = 0;
    }
    return facilitiesOptions[lastSelectedIndex];
}
const string NaiveSelection::toString() const
{
    return "nve";
}
NaiveSelection *NaiveSelection::clone() const
{
    return new NaiveSelection(*this);
}
SelectionPolicyType NaiveSelection::getType() const
{
    return SelectionPolicyType::NAIVE;
}
BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore) : SelectionPolicy(), LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore) {}
const FacilityType &BalancedSelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
    int d_min = INT32_MAX, life, economy, enviroment, index = 0, min_index;
    for (FacilityType f : facilitiesOptions)
    {
        index++;
        life = f.getEnvironmentScore() + LifeQualityScore;
        economy = f.getEconomyScore() + EnvironmentScore;
        enviroment = f.getEnvironmentScore() + EnvironmentScore;
        int diff1 = std::abs(life - economy);
        int diff2 = std::abs(economy - enviroment);
        int diff3 = std::abs(life - enviroment);
        int max_diff = 0;
        if (diff2 > max_diff)
        {
            max_diff = diff2;
        }
        if (diff3 > max_diff)
        {
            max_diff = diff3;
        }
        if (max_diff < d_min)
        {
            d_min = max_diff;
            min_index = index;
        }
    }
    return facilitiesOptions[min_index];
}
const string BalancedSelection::toString() const
{
    return "bal";
}
BalancedSelection *BalancedSelection::clone() const
{
    return new BalancedSelection(*this);
}

BalancedSelection::BalancedSelection(const BalancedSelection &b) : SelectionPolicy(), LifeQualityScore(b.LifeQualityScore), EconomyScore(b.EconomyScore), EnvironmentScore(b.EnvironmentScore)
{
}
SelectionPolicyType BalancedSelection::getType() const
{
    return SelectionPolicyType::BALANCE;
}
EconomySelection::EconomySelection() : lastSelectedIndex(-1)
{
}
void BalancedSelection::addScores(int LifeQualityScore, int EconomyScore, int EnvironmentScore)
{
    this->LifeQualityScore = this->LifeQualityScore + LifeQualityScore;
    this->EconomyScore = this->EconomyScore + EconomyScore;
    this->EnvironmentScore = this->EnvironmentScore + EnvironmentScore;
}
const FacilityType &EconomySelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
    for (unsigned int i = lastSelectedIndex + 1; i <facilitiesOptions.size(); i++)
    {
        if (facilitiesOptions.size() <= i)
        {
            i = 0;
        }
        if (facilitiesOptions[i].getCategory() == FacilityCategory::ECONOMY)
        {
            lastSelectedIndex = i;
            return facilitiesOptions[i];
        }
    }
}
const string EconomySelection::toString() const
{
    return "eco";
}
EconomySelection *EconomySelection::clone() const
{
    return new EconomySelection(*this);
}
EconomySelection::EconomySelection(const EconomySelection &e) : SelectionPolicy(), lastSelectedIndex(e.lastSelectedIndex)
{
}
SelectionPolicyType EconomySelection::getType() const
{
    return SelectionPolicyType::ECO;
}
SustainabilitySelection::SustainabilitySelection() : SelectionPolicy(), lastSelectedIndex(-1) {}
const FacilityType &SustainabilitySelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
    lastSelectedIndex++;
    if (facilitiesOptions.size() <= (unsigned) lastSelectedIndex)
    {
        lastSelectedIndex = 0;
    }
    const vector<FacilityType> *p = &facilitiesOptions;
    p += lastSelectedIndex;
    for (FacilityType t : *p)
    {
        lastSelectedIndex++;
        if (t.getCategory() == FacilityCategory::ENVIRONMENT)
        {
            return t;
        }
    }
}
const string SustainabilitySelection::toString() const
{
    return "sub";
}
SustainabilitySelection *SustainabilitySelection::clone() const
{
    return new SustainabilitySelection(*this);
}
SustainabilitySelection::SustainabilitySelection(const SustainabilitySelection &s) : SelectionPolicy(), lastSelectedIndex(s.lastSelectedIndex) {}
SelectionPolicyType SustainabilitySelection::getType() const
{
    return SelectionPolicyType::SUB;
}