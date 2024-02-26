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

std::string readFile(std::string file) {
  char buffer[BUFFER_SIZE + 1] = {0};
  int fd;
  int i;
  int res;
  std::string result;

  fd = open(file.c_str(), O_RDONLY);
  if (fd < -1) {
    std::cout << "Error" << std::endl;
    throw ParsingException(0, "The file " + file + " does not exists.");
  }
  while ((res = read(fd, buffer, BUFFER_SIZE)) > 0) {
    result += buffer;
    i = 0;
    while (i < BUFFER_SIZE)
      buffer[i++] = 0;
  }
  if (res < 0)
    throw ParsingException(0, "Error while reading " + file + ".");
  close(fd);
  return (result);
}

bool readFile(const string &file, string &fileString) {
  ifstream fileStream(file.c_str());
  string line;

  if (!fileStream.is_open())
    return false;
  while (getline(fileStream, line)) {
    if (!uselessLine(line) && removeCommentary(line))
      fileString += removeSpaces(line);
  }
  return (true);
}

bool checkWordFormat(const string &str) {
  string validChar = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
                     "0123456789-._~:/?#[]@!$&'()*+,;=";

  for (string::const_iterator i = str.begin(); i != str.end(); ++i) {
    if (validChar.find(*i) == std::string::npos) {
      return (false);
    }
  }
  return (true);
}

bool isExecutablePath(const string& path, const string& extension) {
  if (extension.empty() || path.length() < extension.length() || path.substr(path.length() - extension.length()) != extension) {
    return false;
  }
  struct stat attributs;
  if (stat(path.c_str(), &attributs) == 0)
    if (attributs.st_mode & S_IXUSR)
      return true;
  return false;
}

std::vector<unsigned char> readBinaryFile(std::string file) {
  char buffer[BUFFER_SIZE + 1] = {0};
  int fd;
  int i;
  int res;
  std::vector<unsigned char> result;

  fd = open(file.c_str(), O_RDONLY);
  if (fd < -1) {
    std::cout << "Error" << std::endl;
    throw ParsingException(0, "The file " + file + " does not exists.");
  }
  while ((res = read(fd, buffer, BUFFER_SIZE)) > 0) {
    for (size_t j = 0; j < (size_t)res; ++j)
      result.push_back(buffer[j]);
    i = 0;
    while (i < BUFFER_SIZE)
      buffer[i++] = 0;
  }
  if (res < 0)
    throw ParsingException(0, "Error while reading " + file + ".");
  close(fd);
  return (result);
}

std::string getLine(std::string source, size_t n) {
  size_t i;
  size_t j;
  size_t line_count;

  if (n >= countLines(source))
    return (std::string());
  line_count = 0;
  i = 0;
  while (line_count < n) {
    if (source[i++] == '\n')
      ++line_count;
  }
  while (std::isspace(source[i]) && source[i] != '\n')
    ++i;
  j = 0;
  while (source[i + j] && source[i + j] != '\n')
    ++j;
  while (j > 0 && std::isspace(source[i + j - 1]))
    --j;
  return (std::string(source, i, j));
}

size_t countLines(std::string source) {
  size_t i;
  size_t lines;

  i = 0;
  lines = 1;
  while (source[i]) {
    if (source[i++] == '\n')
      ++lines;
  }
  return (lines);
}

std::vector<std::string> parseProperty(std::string source, size_t line,
                                       std::string object) {
  std::vector<std::string> result;
  std::string l;

  l = getLine(source, line);
  if (l[l.size() - 1] != ';')
    throw ParsingException(line, "Expected ';'.");
  l = std::string(l, 0, l.size() - 1);
  result = splitWhitespace(l);
  if (result.size() <= 1)
    throw ParsingException(line, "Properties should have at least one value.");
  //  if (!isPropertyNameValid(result[0],result object == "server" ?
  //  server_properties
  //                                                         :
  //                                                         route_properties))
  throw ParsingException(
      line, "'" + result[0] + "' is not a valid property for " + object + ".");
  return (result);
}

std::vector<std::string> splitWhitespace(std::string str) {
  std::vector<std::string> res;
  size_t i;
  size_t j;

  i = 0;
  j = 0;
  while (str[i]) {
    if (std::isspace(str[i])) {
      if (i == j)
        ++j;
      else {
        res.push_back(std::string(str, j, i - j));
        j = i + 1;
      }
    }
    ++i;
  }
  if (i != j)
    res.push_back(std::string(str, j, i - j));
  return (res);
}

bool isPropertyNameValid(std::string name, const char **valid_names) {
  size_t i;

  i = 0;
  while (valid_names[i]) {
    if (name == valid_names[i])
      return (true);
    ++i;
  }
  return (false);
}

size_t uIntegerParam(std::string param, size_t line) {
  ssize_t value;
  istringstream convert(param);

  if (!(convert >> value))
    throw ParsingException(line, "'" + param + "' is not a positive integer.");
  if (value < 0)
    throw ParsingException(line, "'" + param + "' is not a positive integer.");
  return (value);
}

std::string uIntegerToString(size_t n) {
  std::ostringstream convert;

  convert << n;
  return (convert.str());
}

std::string replace(std::string source, std::string to_replace,
                    std::string new_value) {
  size_t start_pos = 0;
  while ((start_pos = source.find(to_replace, start_pos)) !=
         std::string::npos) {
    source.replace(start_pos, to_replace.length(), new_value);
    start_pos += new_value.length();
  }
  return (source);
}

int pathType(std::string path, time_t *file_date) {
  struct stat buffer;
  struct timezone tz;
  struct timeval t;

  gettimeofday(&t, &tz);
  int exist = stat(path.c_str(), &buffer);
  if (file_date)
    *file_date = buffer.st_mtime + tz.tz_minuteswest * 60;
  if (exist == 0) {
    if (S_ISREG(buffer.st_mode))
      return (1);
    else
      return (2);
  } else
    return (0);
}

std::string itoa(int nb) {
  std::string s;
  std::stringstream out;
  out << nb;
  s = out.str();
  return (s);
}
