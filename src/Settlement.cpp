
#include <string>
#include <vector>
#include "Settlement.h"
using std::string;
using std::vector;

Settlement::Settlement(const string &name, SettlementType type) : name(name), type(type)
{
}
const string &Settlement::getName() const
{
    return name;
}

Settlement *Settlement::clone() const
{
    return new Settlement(name, type);
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

const int Settlement::maxPacilities() const
{
    int maxPacil = 0;
    if (type == SettlementType::CITY)
        maxPacil = 2;
    else if (type == SettlementType::VILLAGE)
        maxPacil = 1;
    else if (type == SettlementType::METROPOLIS)
        maxPacil = 3;
    return maxPacil;
}