// COMP710 GP Framework 2022
#ifndef __INIPARSER_H__
#define __INIPARSER_H__

// Local includes:
#include <string>
#include <map>

// Forward declarations:


//using namespace std;

// Class declaration:
class IniParser
{
	// Member methods:
public:
	IniParser();
	~IniParser();
	bool LoadIniFile(const std::string& filename);
	std::string GetValueAsString(const std::string& iniSection, const std::string& key);
	int GetValueAsInt(const std::string& iniSection, const std::string& key);
	float GetValueAsFloat(const std::string& iniSection, const std::string& key);
	bool GetValueAsBoolean(const std::string& iniSection, const std::string& key);
protected:
private:
	// Member data:
	std::map<std::string, std::map<std::string, std::string>> m_pIniParsedFile;
public:
protected:
	
private:
};
#endif // __INIPARSER_H__