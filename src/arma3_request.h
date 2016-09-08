#pragma once

#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Arma3_request
{
public:
	Arma3_request(const char* request)
	{
		_request = decomposeRequest(request);
	}
	~Arma3_request()
	{

	}
	string getElement(unsigned int position)
	{
		if (position >= _request.size()) return "";
		return _request.at(position);
	}
private:
	vector<string> _request;
	vector<string> decomposeRequest(const std::string &request)
	{
		unsigned int pos;
		std::string newString = request;
		vector<string> decomposed;

		while ((pos = newString.find("$")) != std::string::npos) {
			
			decomposed.push_back(newString.substr(0, pos));
			newString.erase(0, pos + 1);
		}

		if (newString.find("$") == std::string::npos) {
			decomposed.push_back(newString);
			return decomposed;
		}

		return decomposed;
	}
};

