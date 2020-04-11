/*******************************************************************************
 ini.h

 Read INI formatted input files.

 Language: C++11
 Soham Pal
 Iowa State University
*******************************************************************************/

// INI files have the following format:
//
//     key1=value1
//     key2=value2
//     key3=value3
//
// Whitespace trimming code adapted from https://stackoverflow.com/a/25829178.

#ifndef INI_H_
#define INI_H_

#include <fstream>
#include <sstream>
#include <regex>
#include <string>
#include <unordered_map>
#include <stdexcept>

namespace io {

  inline
  std::string trim(const std::string& str) {
    std::size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
      return str;
    }
    std::size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
  }


  class INIParser {
  public:
    INIParser() {};
    INIParser(std::string filename);

    template <typename T>
    T Get(const std::string key, const T default_value) const;
    bool GetBool(const std::string key, const bool default_value) const;

  private:
    std::unordered_map<std::string, std::string> _values;
  };


  INIParser::INIParser(std::string filename) {
    std::string line, current;
    std::regex pair("(\\w+)=([^\\+]+)");

    std::ifstream file(filename);

    if (file.is_open()) {
      while (file.good()) {
        while (getline(file, line)) {

          auto tline = trim(line);

          if (tline.length() > 0) {
            std::smatch match;

            if (std::regex_search(tline, match, pair)) {
              _values[match[1]] = match[2];
              }
          }
        }
      }
      file.close();
    } else {
      throw std::runtime_error("File not read.");
    }
  }


  template <typename T>
  T INIParser::Get(const std::string key, const T default_value) const {
    T val;
    auto search = _values.find(key);
    if (search != _values.end()) {
      std::istringstream ss(search->second);
      ss >> val;
      return val;
    } else {
      return default_value;
    }
  }


  inline
  bool INIParser::GetBool(const std::string key, const bool default_value) const {
    auto search = _values.find(key);
    if (search != _values.end()) {
      auto valstr = search->second;
      std::transform(valstr.begin(), valstr.end(), valstr.begin(), ::tolower);
      if (valstr == "true" || valstr == "yes" || valstr == "1") {
        return true;
      } else if (valstr == "false" || valstr == "no" || valstr == "0") {
        return false;
      } else {
        throw std::runtime_error("Cannot convert argument to Boolean.");
      }
    } else {
      return default_value;
    }
  }
}

#endif
