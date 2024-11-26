// #pragma once
#include <string>
#include <vector>
#include "Settlement.h"
using std::string;
using std::vector;

Settlement::Settlement(const string &name, SettlementType type):name(name),type(type){
}
 const string& Settlement::getName() const {
    return name;
 }
 
SettlementType Settlement::getType() const {
    return type;
}
const string Settlement:: toString() const{
    string t;
    if(type==SettlementType::CITY)
        t="CITY";
    else if(type==SettlementType::VILLAGE)
        t="VILLAGE";
    else if(type==SettlementType::METROPOLIS)
        t="METROPOLIS";
    return "Settlement Name: " + name + "Settlement Type: " + t;
}

const int Settlement::maxPacilities() const{
    int maxPacil=0;
    if(type==SettlementType::CITY)
        maxPacil=2;
    else if(type==SettlementType::VILLAGE)
        maxPacil=1;
    else if(type==SettlementType::METROPOLIS)
        maxPacil=3;
    return maxPacil;
}