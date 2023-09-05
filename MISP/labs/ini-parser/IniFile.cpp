#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

#include "IniFile.h"

void strip(std::string& str)
{
    while (!str.empty() && str[0] == ' ')
    {
        str.erase(0, 1);
    }
    while (!str.empty() &&  str[str.size() - 1] == ' ')
    {
        str.pop_back();
    }
}

bool boolCheck(std::string str)
{
    for (int i = 0; i < str.size(); ++i) 
    {
        str[i] = str[i] >= 'A' && str[i] <= 'Z' ? str[i] + 32 : str[i];
    } 
    for (auto it = trueValues.begin(); it != trueValues.end(); ++it)
    {
        if (str == *it)
        {
            return true;
        }
    }
    return false;
}

std::string parseSection(std::string str)
{
    str = str.substr(1, str.size() - 2);
    if (str.find('[') != std::string::npos || str.find(']') != std::string::npos || str.find('=') != std::string::npos)
    {
        return "";
    }
    strip(str);
    return str;
}

std::pair<std::string, std::string> parseKey(std::string str)
{
    if (str.find('[') != std::string::npos || str.find(']') != std::string::npos)
    {
        return {};
    }
    std::string key = str.substr(0, str.find('='));
    std::string value = str.substr(str.find('=') + 1);
    strip(key);
    strip(value);
    if (key.empty() || value.empty())
    {
        return {};
    }
    return {key, value};
}

IniFile::IniFile(const std::string& path) : filePath(path)
{
    std::ifstream file = std::ifstream(path);
    if (!file.is_open())
    {
        return;
    }

    std::string lastSection = "";
    while (file)
    {
        std::string line;
        getline(file, line, '\n');
        line = line.substr(0, line.find(';'));
        strip(line);
        if (line == "")
        {
            continue;
        }
        if (line[0] == '[' && line[line.size() - 1] == ']')
        {
            std::string secName = parseSection(line);
            if (secName == "")
            {
                continue;
            }
            data[secName];
            lastSection = secName;

        }
        else if (line.find('=') != std::string::npos)
        {

            if(lastSection != "")
            {
                auto key = parseKey(line);
                if (key == std::pair<std::string, std::string>())
                {
                    continue;
                }

                if(data[lastSection].find(key.first) != data[lastSection].end())
                {
                    data[lastSection].erase(key.first);
                }

                data[lastSection].insert(parseKey(line));
            }
        }
    }       
}

IniFile::~IniFile()
{
    save();
}

void IniFile::save()
{
    std::ofstream file = std::ofstream(filePath);
    if (!file.is_open())
    {
        return;
    }

    for (auto it1 = data.begin(); it1 != data.end(); ++it1)
    {
        auto keys = it1->second;
        file << "[" + it1->first + "]\n";
        if (!keys.empty())
        {
            for (auto it2 = keys.begin(); it2 != keys.end(); ++it2)
            {
                file << it2->first + "=" + it2->second + "\n";
            }
        }
        file << std::endl;
    }
}

int IniFile::readInt(const std::string& section, const std::string& key, int def)
{
    if (!isSectionExist(section) || !isKeysExist(section, key))
    {
        return def;
    }
    return std::stoi(data[section][key]);
}

double IniFile::readDouble(const std::string& section, const std::string& key, double def)
{
    if (!isSectionExist(section) || !isKeysExist(section, key))
    {
        return def;
    }
    return std::stod(data[section][key]);
}

std::string IniFile::readString(const std::string& section, const std::string& key, const std::string& def)
{
    if (!isSectionExist(section) || !isKeysExist(section, key))
    {
        return def;
    }
    return data[section][key];
}

bool IniFile::readBool(const std::string& section, const std::string& key, bool def)
{
    if (!isSectionExist(section) || !isKeysExist(section, key))
    {
        return def;
    }
    return boolCheck(data[section][key]);
}

void IniFile::writeInt(const std::string& section, const std::string& key, int value)
{
    if (isKeysExist(section, key))
    {
        data[section].erase(key);
    }
    data[section].insert({key, std::to_string(value)});
}

void IniFile::writeDouble(const std::string& section, const std::string& key, double value)
{
    if (isKeysExist(section, key))
    {
        data[section].erase(key);
    }
    data[section].insert({key, std::to_string(value)});
}

void IniFile::writeString(const std::string& section, const std::string& key, const std::string& value)
{
    if (isKeysExist(section, key))
    {
        data[section].erase(key);
    }
    data[section].insert({key, value});
}

void IniFile::writeBool(const std::string& section, const std::string& key, bool value)
{
    if (isKeysExist(section, key))
    {
        data[section].erase(key);
    }
    data[section].insert({key, value ? "true" : "false"});
}

bool IniFile::isSectionExist(const std::string& section)
{
    return data.find(section) != data.end();
}

bool IniFile::isKeysExist(const std::string& section, const std::string& key)
{
    if (!isSectionExist(section))
    {
        return false;
    }
    return data[section].find(key) != data[section].end();
}

size_t IniFile::getSectionsCount()
{
    return data.size();
}

size_t IniFile::getKeysCount(const std::string& section)
{
    if (!isSectionExist(section))
    {
        return 0;
    }
    return data[section].size();
}

SectionsMap IniFile::getSections() const
{
    return data;
}

bool IniFile::deleteSection(const std::string& section)
{
    if (!isSectionExist(section))
    {
        return false;
    }
    data.erase(section);
    return true;
}

bool IniFile::deleteKey(const std::string& section, const std::string& key)
{
    if (!isSectionExist(section) || !isKeysExist(section, key))
    {
        return false;
    }
    data[section].erase(key);
    return true;
}


