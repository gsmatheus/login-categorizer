#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <filesystem>

namespace fs = std::filesystem;

void readUrlsFromFile(const std::string &filename, std::vector<std::string> &androidUrls, std::vector<std::string> &normalUrls)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    throw std::runtime_error("Error opening file: " + filename);
  }

  std::string line;
  while (std::getline(file, line))
  {
    if (!line.empty())
    {
      (line.rfind("android://", 0) == 0 ? androidUrls : normalUrls).push_back(line);
    }
  }
}

void extractLogins(const std::vector<std::string> &normalUrls, std::unordered_map<char, std::vector<std::string>> &loginMap)
{
  for (const auto &url : normalUrls)
  {
    size_t pos = url.find("://");
    if (pos == std::string::npos)
    {
      std::cerr << "Invalid format: " << url << "\n";
      continue;
    }

    std::string domainAndCredentials = url.substr(pos + 3);
    size_t firstColon = domainAndCredentials.find(":");
    size_t secondColon = domainAndCredentials.find(":", firstColon + 1);

    if (firstColon != std::string::npos && secondColon != std::string::npos)
    {
      std::string login = domainAndCredentials.substr(firstColon + 1, secondColon - firstColon - 1);
      if (!login.empty())
      {
        char firstChar = std::tolower(login[0]);
        if (std::isalnum(firstChar))
        {
          loginMap[firstChar].emplace_back(url);
        }
      }
      else
      {
        std::cerr << "Login is empty in URL: " << url << "\n";
      }
    }
  }
}

void saveLoginsToFile(const std::unordered_map<char, std::vector<std::string>> &loginMap)
{
  const std::string outputDir = "output";
  fs::create_directories(outputDir);

  std::cout << "\nSaving logins by initial letter in 'output' folder:\n";
  for (const auto &[key, logins] : loginMap)
  {
    std::string fileName = outputDir + "/" + key + ".txt";
    std::ofstream outFile(fileName);
    if (!outFile.is_open())
    {
      std::cerr << "Error creating file for '" << key << "'\n";
      continue;
    }

    for (const auto &login : logins)
    {
      outFile << login << "\n";
    }

    std::cout << "Logins starting with '" << key << "' saved in '" << fileName << "'\n";
  }
}

int main()
{
  try
  {
    std::vector<std::string> androidUrls;
    std::vector<std::string> normalUrls;

    readUrlsFromFile("logs.txt", androidUrls, normalUrls);

    std::unordered_map<char, std::vector<std::string>> loginMap;
    extractLogins(normalUrls, loginMap);

    saveLoginsToFile(loginMap);
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  return 0;
}
