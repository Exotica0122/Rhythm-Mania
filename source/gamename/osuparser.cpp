// COMP710 GP Framework 2022

// This include:
#include "osuparser.h"

// Local includes:
#include "logmanager.h"

// Library includes:
#include <fstream>

OsuParser::OsuParser()
{

}

OsuParser::~OsuParser()
{
	m_pOsuSettingsFile.clear();
	m_pCirclePositions.clear();
}

bool
OsuParser::LoadOsuFile(const std::string& filename)
{
	// Load in file just like ini
	LogManager::GetInstance().Log("Osu starting...");
	LogManager::GetInstance().Log(filename.c_str());

	std::string myText;

	std::ifstream MyReadFile(filename);

	std::string head = "";
	std::map<std::string, std::string> m_pKeyValue;

	while (std::getline(MyReadFile, myText)) {
		// Ignore for emptyline, note and comments 
		if (myText.empty() || myText.substr(0, myText.size() - 4) == "osu file format" || myText.substr(0, 2) == "//") {
			continue;
		}
		// when at head of section
		else if (myText.c_str()[0] == '[')
		{
			if (head != "" && m_pKeyValue.size() > 0)
			{
				// Put contents in map
				m_pOsuSettingsFile.insert({ head , m_pKeyValue });
				m_pKeyValue.clear();
			}

			head = myText.substr(1, myText.size() - 2);
		}
		// body of content
		else
		{
			std::string separator;
			// cast to char pointer
			char* c = const_cast<char*>(myText.c_str());

			if (head == "General")
			{
				separator = ": ";
			}
			else if (head == "Metadata" || head == "Difficulty")
			{
				separator = ":";
			}
			else if (head == "Colours")
			{
				separator = " : ";
			}
			else if (head == "HitObjects")
			{
				m_pCirclePositions.push_back(c);
				continue;
			}
			else {
				continue;
			}

			c = strtok(c, separator.c_str());
			while (c != NULL)
			{
				// Key
				char* key = c;
				c = strtok(NULL, separator.c_str());

				// Value
				char* value = c;
				c = strtok(NULL, separator.c_str());

				//m_pKeyValue.insert({ key, value });
			}
		}
	}

	MyReadFile.close();

	return true;
}

std::vector<std::string>
OsuParser::GetObjectPositions()
{
	return m_pCirclePositions;
}