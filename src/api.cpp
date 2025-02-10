#include "api.h"
#include <iostream>

nlohmann::json search_city(std::string API_KEY, std::string city)
{
	cpr::Parameters parameters{
		{"key", API_KEY},
		{"q", city}
	};

	cpr::Response response = cpr::Get(cpr::Url{ "http://api.weatherapi.com/v1/current.json" },
		parameters);
	return nlohmann::json::parse(response.text);
}