//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/2-parser.hpp"

static bool extractBlocks(vecStr &split, istringstream &isStr, string &line) {
  bool ret = true;
  while (getline(isStr, line) && ret) {
    if (line.find('{') != string::npos) {
      split.back() += "\n" + line;
      ret = extractBlocks(split, isStr, line);
    } else {
      split.back() += "\n" + line;
      if (line.find('}') != string::npos) {
        if (line.size() != 1)
          return false;
        return true;
      }
    }
  }
  return ret;
}

bool splitBlocks(vecStr &split, const string &str, const string &pattern,
                 vecStr &otherInfo) {
  istringstream isStr(str);
  size_t typePattern = (pattern == "server" ? 1 : 2);
  string line;
  bool ret = true;
  while (getline(isStr, line) && ret) {
    if (line.find(pattern) != string::npos) {
      vecStr tmpSplit;
      splitPattern(tmpSplit, line, ' ');
      if (tmpSplit[0] == pattern && tmpSplit[typePattern] == "{" &&
          tmpSplit.size() == typePattern + 1) {
        split.push_back(line);
        ret = extractBlocks(split, isStr, line);
      } else
        return false;
    } else {
      istringstream iss(line);
      getline(iss >> ws, line, ';');
      otherInfo.push_back(line);
    }
  }
  return (ret);
}

void splitPattern(vecStr &split, const string &str, const char &pattern) {
  istringstream is(str);
  string toAdd;
  if (pattern == ' ') {
    while (is >> ws >> toAdd) {
      split.push_back(toAdd);
    }
  } else {
    while (getline(is >> ws, toAdd, pattern)) {
      split.push_back(toAdd);
    }
  }
}

vecStr splitStr(string str) {
  vecStr split(3);

  int i = 0;
  istringstream is(str);
  while (is.good() && i < 3) {
    is >> split[i];
    i++;
  }
  return split;
}

static bool uselessLine(string &line) {
  istringstream iss(line);
  string word;
  iss >> ws >> word;
  return word.empty();
}

static string removeSpaces(string &line) {
  if (line.empty())
    return line;
  string word;
  istringstream iss(line);
  line.clear();
  while (iss >> ws >> word)
    line += word + ' ';
  line[line.size() - 1] = '\n';
  return line;
}

static bool removeCommentary(string &line) {
  size_t commentPos;

  commentPos = line.find('#');
  if (commentPos == 0)
    return "";
  else if (commentPos != string::npos)
    line = line.substr(0, commentPos);
  return !line.empty();
}

