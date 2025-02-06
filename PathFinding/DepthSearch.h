#pragma once
#include "Map.h"
#include <vector>
class DepthSearch
{
private:
	Map& map;

public:
	DepthSearch(Map& thismap);
	~DepthSearch();
};

