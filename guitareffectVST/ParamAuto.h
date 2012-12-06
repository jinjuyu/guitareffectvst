#pragma once
#include <string>
using namespace std;
enum EffNameType;
struct ParamAuto
{
	EffNameType type;
	int paramNum; // real parameter value used in changepar
	string typeStr;
	string paramStr;
};