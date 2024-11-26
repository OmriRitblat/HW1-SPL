#pragma once
#include <vector>
#include "SelectionPolicy.h"
using std::vector;


        NaiveSelection::NaiveSelection():SelectionPolicy(),lastSelectedIndex(-1){}
NaiveSelection::NaiveSelection(const NaiveSelection& n) : SelectionPolicy(n), lastSelectedIndex(n.lastSelectedIndex) {
}   
     const FacilityType& NaiveSelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
            lastSelectedIndex++;
            return facilitiesOptions[lastSelectedIndex];
        }
        //const string NaiveSelection::NaiveSelection():toString() const override;
      NaiveSelection* NaiveSelection::clone() const {
    return new NaiveSelection(*this); 
}
        BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore):SelectionPolicy(),LifeQualityScore(LifeQualityScore),EconomyScore(EconomyScore),EnvironmentScore(EnvironmentScore){}
        const FacilityType& BalancedSelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
            int d_min=INT32_MAX,life,economy,enviroment,index=0,min_index;
            for(FacilityType f:facilitiesOptions){
                index++;
                life=f.getEnvironmentScore() + LifeQualityScore;
                economy=f.getEconomyScore() + EnvironmentScore;
                enviroment =f.getEnvironmentScore()+ EnvironmentScore;
                int diff1 = std::abs(life - economy);
                int diff2 = std::abs(economy - enviroment);
                int diff3 = std::abs(life - enviroment);
                int max_diff=0;
                if (diff2 > max_diff) {
                     max_diff = diff2;
                }
                if (diff3 > max_diff) {
                     max_diff = diff3;
                 }
                if(max_diff<d_min){
                    d_min=max_diff;
                    min_index=index;
                }
            }
            return facilitiesOptions[min_index];
        }
        // const string toString() const override;
        BalancedSelection* BalancedSelection::clone() const {
            return new BalancedSelection(*this); 
}

        BalancedSelection::BalancedSelection(const BalancedSelection &b):SelectionPolicy(),LifeQualityScore(b.LifeQualityScore),EconomyScore(b.EconomyScore),EnvironmentScore(b.EnvironmentScore){
        }

        EconomySelection::EconomySelection():lastSelectedIndex(-1){

        }
        const FacilityType& EconomySelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
            lastSelectedIndex++;
            const vector<FacilityType>* p=&facilitiesOptions;
            p+=lastSelectedIndex;
            for(FacilityType t:*p){
                lastSelectedIndex++;
                if(t.getCategory()==FacilityCategory::ECONOMY){
                    return t;
                }
            }
        }
       // const string toString() const override;
        EconomySelection *EconomySelection::clone() const{
            return new EconomySelection(*this);
        }
        EconomySelection::EconomySelection(const EconomySelection &e):SelectionPolicy(),lastSelectedIndex(e.lastSelectedIndex) {
        }

        SustainabilitySelection::SustainabilitySelection():SelectionPolicy(),lastSelectedIndex(-1){}
        const FacilityType& SustainabilitySelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
            lastSelectedIndex++;
            const vector<FacilityType>* p=&facilitiesOptions;
            p+=lastSelectedIndex;
            for(FacilityType t:*p){
                lastSelectedIndex++;
                if(t.getCategory()==FacilityCategory::ENVIRONMENT){
                    return t;
                }
            }
        }
        //const string toString() const override;
        SustainabilitySelection *SustainabilitySelection::clone() const{
            return new SustainabilitySelection(*this);
        }
        SustainabilitySelection::SustainabilitySelection(const SustainabilitySelection &s):SelectionPolicy(),lastSelectedIndex(s.lastSelectedIndex){}