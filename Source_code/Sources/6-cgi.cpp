//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/6-cgi.hpp"

CGI::CGI(Headers &headers) : _headers(&headers), _pid(), _time() {}

CGI::~CGI() {}

bool CGI::launchChild() {
  _pid = fork();
  if (_pid == -1)
    throw ErrnoException("error launch child");
  if (_pid == 0) {
//    dup2(_headers->getClient()->getSdIn()[STDIN_FILENO], STDIN_FILENO);
//    close(_headers->getClient()->getSdOut()[STDIN_FILENO]);
//    dup2(_headers->getClient()->getSdOut()[STDOUT_FILENO], STDOUT_FILENO);
//    close(_headers->getClient()->getSdIn()[STDOUT_FILENO]);
//    execve(_headers->getCgiEnv()[0], _headers->getCgiEnv().data(),
//           _headers->getCgiEnv().data());
    //check free and sigpipe
    exit(EXIT_FAILURE);
  }
  return true;
}

//    write(fd[1], _request.getContent().c_str(),
//    _request.getContent().length());
//close(fd[1]);
//waitpid(-1, NULL, 0);
//_freeArgs(args);
//_freeArgs(exec_args);
//  }
//  Log("End CGI");
//  //  return (readFile("/tmp/webserv_cgi"));
//  return "";
//}

/**
 * Get exec args (script name and file to treat)
 * @return char ** of execve args
 */
char **CGI::_getExecArgs() {
  char **args;

  if (!(args = (char **)malloc(sizeof(char *) * 3)))
    return (0);
  //  args[0] = _newStr(_cgi_path);
  //  args[1] = _newStr(_ressource_path);
  args[2] = 0;
  return (args);
}

/**
 * Free the CGI args array
 * @param args the char ** to free
 */
void CGI::_freeArgs(char **args) {
  size_t i;

  i = 0;
  while (args[i])
    free(args[i++]);
  free(args);
}

/**
 * Get the char** representation of CGI arguments
 * @param args arguments to convert
 * @return a char** that represents CGI aguments, should be free later
 */
char **CGI::_convertParams(std::map<std::string, std::string> args) {
  char **result;
  std::map<std::string, std::string>::iterator it;
  size_t i;

  if (!(result = (char **)malloc(sizeof(char *) * (args.size() + 1))))
    return (0);
  it = args.begin();
  i = 0;
  while (it != args.end()) {
    result[i++] = _newStr(it->first + "=" + it->second);
    ++it;
  }
  result[args.size()] = 0;
  return (result);
}

/**
 * Get a char* from a std::string
 * @param source the string to copy
 * @return char* representing the source string, needs to be freed later
 */
char *CGI::_newStr(std::string source) {
  char *res;

  if (!(res = (char *)malloc(sizeof(char) * (source.size() + 1))))
    return (0);
  for (size_t i = 0; i < source.size(); ++i)
    res[i] = source[i];
  res[source.size()] = 0;
  return (res);
}

/**
 * Get the CGI params
 * @return a map of the CGI param to execute
 * @todo implement AUTH_TYPE, REMOTE_ADDR, REMOTE_IDENT, REMOTE_USER
 */
std::map<std::string, std::string> CGI::_getParams() {
  std::map<std::string, std::string> args;
  //  std::string tmp;
  //  size_t i;
  //  size_t j;
  //
  //  args["GATEWAY_INTERFACE"] = "CGI/1.1";
  //  args["PATH_TRANSLATED"] = _ressource_path;
  //  args["QUERY_STRING"] = _getQueryString();
  //  args["REQUEST_METHOD"] = _request.getRequestLine()._method;
  //  args["CONTENT_LENGTH"] = uIntegerToString(_request.getContent().length());
  //  for (size_t u = 0; u < _request.getHeaderFields().size(); u++)
  //    if (_request.getHeaderFields()[u]._field_name == "Content-Type") {
  //      DEBUG("CONTENT GIVEN = " <<
  //      _request.getHeaderFields()[u]._field_value) args["CONTENT_TYPE"] =
  //      _request.getHeaderFields()[u]._field_value;
  //    }
  //  args["REQUEST_URI"] =
  //      _removeQueryArgs(_request.getRequestLine()._request_target);
  //  args["REMOTE_IDENT"] = "";
  //  args["REDIRECT_STATUS"] = "200";
  ////  args["REMOTE_ADDR"] = _request.getClientIP();
  //  args["SCRIPT_NAME"] =
  //      _location.path +
  //      ((_location.path[_location.path.length() - 1] == '/') ? "" : "/") +
  //      replace(_ressource_path, _location.root, "");
  //  args["PATH_INFO"] =
  //      _removeQueryArgs(_request.getRequestLine()._request_target);
  //  args["SCRIPT_FILENAME"] = _ressource_path;
  //  args["SERVER_NAME"] = _conf.host;
  //  args["SERVER_PORT"] = uIntegerToString(_conf.port);
  //  args["SERVER_PROTOCOL"] = "HTTP/1.1";
  //  args["SERVER_SOFTWARE"] = "webserv/1.0";
  //  for (size_t a = 0; a < _request.getHeaderFields().size(); ++a) {
  //    tmp = _request.getHeaderFields()[a]._field_name;
  //    tmp = replace(tmp, "-", "_");
  //    for (size_t b = 0; b < tmp.size(); ++b)
  //      tmp[b] = toupper(tmp[b]);
  //    args["HTTP_" + tmp] = _request.getHeaderFields()[a]._field_value;
  //  }
  //  i = 0;
  //  while (envp[i]) {
  //    j = 0;
  //    while (envp[i][j] && envp[i][j] != '=')
  //      j++;
  //    args[std::string(envp[i], 0, j)] =
  //        std::string(envp[i], j + 1, std::string(envp[i]).size() - j);
  //    ++i;
  //  }
  return (args);
}

std::string CGI::_getScriptName() {
  //  size_t i;

  //  i = 0;
  //  while (_request.getRequestLine()._request_target[i] &&
  //         _request.getRequestLine()._request_target[i] != '?')
  //    ++i;
  return ""; /* (std::string(_request.getRequestLine()._request_target, 0,
                i));*/
}

/**
 * Get query string (everything after ? in url)
 * @return the query string
 * @example "index.php?a=42&page_id=32&c=21" -> "a=42&page_id=32&c=21"
 */
std::string CGI::_getQueryString() {
  //  size_t i;
  //
  //  i = 0;
  //  while (_request.getRequestLine()._request_target[i] &&
  //         _request.getRequestLine()._request_target[i] != '?')
  //    ++i;
  //  if (_request.getRequestLine()._request_target[i] == '?')
  //    ++i;
  //  return (std::string(_request.getRequestLine()._request_target, i, -i));
  return "";
}

/**
 * Remove query
 * @param query the string to remove query from
 * @return the string without query params
 * @example "/php/index.php?a=1&page_id=2" -> "/php/index.php"
 */
std::string CGI::_removeQueryArgs(std::string query) {
  size_t i;

  i = 0;
  while (query[i] && query[i] != '?')
    ++i;
  return (std::string(query, 0, i));
}
