module;
#include <vector>

export module country;

//import <vector>; // not working in Unreal

import city;

export class Country {
public:
	std::vector<City> Cities;

	Country() {}

	void InitDev() {
		Cities.reserve(3);

		Cities.push_back(City());
		Cities.push_back(City());
		Cities.push_back(City());
	}
};