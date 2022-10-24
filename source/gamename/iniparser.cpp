// COMP710 GP Framework 2022

// This include:
#include "iniparser.h"

// Local includes:
#include "logmanager.h"

// Library includes:
#include <fstream>

IniParser::IniParser()
{

}

IniParser::~IniParser()
{
	m_pIniParsedFile.clear();
}

bool 
IniParser::LoadIniFile(const std::string& filename)
{
	LogManager::GetInstance().Log("Ini starting...");
	LogManager::GetInstance().Log(filename.c_str());

	std::string myText;

	std::ifstream MyReadFile(filename);

	std::string head = "";
	std::map<std::string, std::string> m_pKeyValue;

	while (std::getline(MyReadFile, myText)) {
		if (myText.empty()) {
			continue;
		}
		// when at head of section
		if (myText.c_str()[0] == '[')
		{
			if (head != "")
			{
				m_pIniParsedFile.insert({ head , m_pKeyValue});
				m_pKeyValue.clear();
			}
			head = myText.substr(1, myText.size() - 2);
		}
		// body of content
		else 
		{
			// cast to char pointer
			char* c = const_cast<char*>(myText.c_str());
			c = strtok(c, ": ");
			while (c != NULL)
			{
				// Key
				char* key = c;
				c = strtok(NULL, ": ");

				// Value
				char* value = c;
				c = strtok(NULL, ": ");

				m_pKeyValue.insert({key, value});
			}			
		}
	}
	m_pIniParsedFile.insert({ head , m_pKeyValue });

	// Close the file
	MyReadFile.close();

	//for (auto& t : m_pIniParsedFile)
	//{
	//	LogManager::GetInstance().Log(t.first.c_str());
	//	LogManager::GetInstance().Log("-----------");
	//	for (auto& t2: t.second)
	//	{
	//		LogManager::GetInstance().Log(t2.first.c_str());
	//		LogManager::GetInstance().Log(t2.second.c_str());
	//	}
	//	LogManager::GetInstance().Log("-----------");
	//}

	return true;
}

std::string 
IniParser::GetValueAsString(const std::string& iniSection, const std::string& key)
{
	return m_pIniParsedFile.at(iniSection).at(key);
}

int
IniParser::GetValueAsInt(const std::string& iniSection, const std::string& key)
{
	return stoi(m_pIniParsedFile.at(iniSection).at(key));
}

float 
IniParser::GetValueAsFloat(const std::string& iniSection, const std::string& key)
{
	return std::stof(m_pIniParsedFile.at(iniSection).at(key));
}

bool 
IniParser::GetValueAsBoolean(const std::string& iniSection, const std::string& key)
{
	return m_pIniParsedFile.at(iniSection).at(key) == "true";
}