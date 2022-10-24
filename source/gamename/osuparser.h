// COMP710 GP Framework 2022
#ifndef __OSUPARSER_H__
#define __OSUPARSER_H__

// Local includes:
#include <string>
#include <vector>
#include <map>

// Forward declarations:


//using namespace std;

// Class declaration:
class OsuParser
{
	// Member methods:
public:
	OsuParser();
	~OsuParser();
	bool LoadOsuFile(const std::string& filename);
	std::vector<std::string> GetObjectPositions();
protected:
private:
	// Member data:
	std::map<std::string, std::map<std::string, std::string>> m_pOsuSettingsFile;
	std::vector<std::string> m_pCirclePositions;
public:
protected:

private:
};
#endif // __OSUPARSER_H__