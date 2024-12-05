
#include <string>
#include <vector>
#include "Settlement.h"
using std::string;
using std::vector;

Settlement::Settlement(const string &name, SettlementType type) : name(name),type(SettlementType::CITY)
{
   SettlementType t;
    if (type == SettlementType::CITY)
    {
        t=SettlementType::CITY;
    }
    else if(type == SettlementType::VILLAGE){
        t=SettlementType::VILLAGE;
    }
    else{
        t=SettlementType::METROPOLIS;
    }
    this->type=t; 
}
const string &Settlement::getName() const
{
    return name;
}

Settlement *Settlement::clone() const
{
    SettlementType t;
    if (this->type == SettlementType::CITY)
    {
        t=SettlementType::CITY;
    }
    else if(this->type == SettlementType::VILLAGE){
        t=SettlementType::VILLAGE;
    }
    else{
        t=SettlementType::METROPOLIS;
    }
    return new Settlement(name, t);
}
SettlementType Settlement::getType() const
{
    return type;
}
const string Settlement::toString() const
{

    return "Settlement Name: " + name + "Settlement Type: " + Settlement::getSettlememtTypeByString(type);
}

 string Settlement::getSettlememtTypeByString(const SettlementType st)
{
    string t;
    if (st == SettlementType::CITY)
        t = "CITY";
    else if (st == SettlementType::VILLAGE)
        t = "VILLAGE";
    else if (st == SettlementType::METROPOLIS)
        t = "METROPOLIS";
    return t;
}


SettlementType Settlement::getSettlememtType(const string s)
{
    if (s == "1")
        return SettlementType::CITY;
    else if (s == "0")
        return SettlementType::VILLAGE;
    else
        return SettlementType::METROPOLIS;
}

const unsigned int Settlement::maxPacilities() const
{
    int maxPacil = 0;
    if (type == SettlementType::CITY){
        maxPacil = 2;
    }
    else if (type == SettlementType::VILLAGE){
        maxPacil = 1;
    }
    else if (type == SettlementType::METROPOLIS){
        maxPacil = 3;
    }
    return maxPacil;
}