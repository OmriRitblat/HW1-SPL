#pragma once
#include <string>
#include <vector>
#include "Settlement.h"
using std::string;
using std::vector;


Settlement::Settlement(const string &name, SettlementType type):name(name),type(type){
}