#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class Facility;

enum class SettlementType
{
    VILLAGE,
    CITY,
    METROPOLIS,
};

class Settlement
{
public:
    Settlement(const string &name, SettlementType type);
    const string &getName() const;
    SettlementType getType() const;
    const string toString() const;
    const int maxPacilities() const;
    Settlement* clone() const;
    static SettlementType getSettlememtType(const string s);
    static string getSettlememtTypeByString(const SettlementType st);

private:
    const string name;
    SettlementType type;
};