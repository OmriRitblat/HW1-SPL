
#include <vector>
#include "SelectionPolicy.h"
#include <algorithm> 
#include <cmath>      
using std::vector;
using std::max;

NaiveSelection::NaiveSelection() : SelectionPolicy(), lastSelectedIndex(0) {}
NaiveSelection::NaiveSelection(const NaiveSelection &n) : SelectionPolicy(), lastSelectedIndex(n.lastSelectedIndex)
{
}
const FacilityType &NaiveSelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
    if (facilitiesOptions.size() <= (unsigned)lastSelectedIndex)
    {
        lastSelectedIndex = 0;
    }
    lastSelectedIndex++;
    return facilitiesOptions[lastSelectedIndex-1];
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
    int d_min = INT32_MAX, life, economy, enviroment, min_index, lifeFinal,ecoFinal,envFinal;
    for (int i=0;i<facilitiesOptions.size();i++)
    {
        life = facilitiesOptions[i].getLifeQualityScore() + LifeQualityScore;
        economy = facilitiesOptions[i].getEconomyScore() + EconomyScore;
        enviroment = facilitiesOptions[i].getEnvironmentScore() + EnvironmentScore;
        int diff1 = std::abs(life - economy);
        int diff2 = std::abs(economy - enviroment);
        int diff3 = std::abs(life - enviroment);
        int max=std::max({diff1, diff2, diff3});
        if(d_min>max){
            d_min = max;
            min_index = i;
            lifeFinal=life;
            ecoFinal=economy;
            envFinal=enviroment;
        }
    }
    LifeQualityScore=lifeFinal;
    EconomyScore=ecoFinal;
    EnvironmentScore=envFinal;
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
EconomySelection::EconomySelection() :SelectionPolicy(), lastSelectedIndex(0)
{
}
const FacilityType &EconomySelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
    int start =facilitiesOptions.size()-lastSelectedIndex;
    for(unsigned int i=lastSelectedIndex; i<facilitiesOptions.size();i++)
    {
        if (facilitiesOptions.size() <= i)
        {
            i = 0;
        }
        if (facilitiesOptions[i].getCategory() == FacilityCategory::ECONOMY)
        {
            lastSelectedIndex=i+1;
            return facilitiesOptions[i];
        }
        if(i==facilitiesOptions.size()-1){
            i=0;
        }
        if(i==start){
            break;
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
SustainabilitySelection::SustainabilitySelection() : SelectionPolicy(), lastSelectedIndex(0) {}
const FacilityType &SustainabilitySelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
    int start =facilitiesOptions.size()-lastSelectedIndex;
    for(unsigned int i=lastSelectedIndex; i<facilitiesOptions.size();i++)
    {
        if (facilitiesOptions.size() <= i)
        {
            i=0;
        }
        if (facilitiesOptions[i].getCategory() == FacilityCategory::ENVIRONMENT)
        {
            lastSelectedIndex=i+1;
            return facilitiesOptions[i];
        }
        if(i==facilitiesOptions.size()-1){
            i=0;
        }
        if(i==start){
            break;
        }
    }
    }
const string SustainabilitySelection::toString() const 
{
    return "env";
}
SustainabilitySelection *SustainabilitySelection::clone() const
{
    return new SustainabilitySelection(*this);
}
SustainabilitySelection::SustainabilitySelection(const SustainabilitySelection &s) : SelectionPolicy(), lastSelectedIndex(s.lastSelectedIndex) {}
SelectionPolicyType SustainabilitySelection::getType() const
{
    return SelectionPolicyType::ENV;
}