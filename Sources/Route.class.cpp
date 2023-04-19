#include "../Include/Route.class.hpp"

void Route::setAllowedMethods(vector<string>& allowed_methods) throw() {
    this->_allowed_methods = allowed_methods;
}

const vector<string>& Route::getAllowedMethods(void) const throw() {
    return _allowed_methods;
}

void Route::pushMethod(const string& method) throw() {
    _allowed_methods.push_back(method);
}

void Route::checkMethod(const string& method) {
    string methods[] = {"GET", "POST", "DELETE"};
    int opt = -1;
    for (std::size_t i = 0; i < methods->size(); i++) {
        if (methods[i] == method)
            opt = i;
    }
    if (opt == -1)
        throw InvalidDirective();
}

Route::Route() {
    _autoIndex = false;
}

Route::~Route() {}

void Route::setPrefix(string& prefix) throw() {
    this->_prefix = prefix;
}

const string& Route::getPrefix(void) const throw() {
    return this->_prefix;
}

void Route::setHttpRedir(string& redir) throw() {
    this->_httpRedir = redir;
} 

const string& Route::getHttpRedir(void) const throw() {
    return this->_httpRedir;
}

void Route::setDirectoryListing(bool state) throw() {
    this->_autoIndex = state;
}

const bool Route::getDirectoryListing(void) const throw() {
    return this->_autoIndex;
}

void Route::setSearchDir(string& dir) throw() {
    this->_searchDir = dir;
}

const string& Route::getSearchDir(void) const throw() {
    return this->_searchDir;
}

void Route::setIndex(vector<string>& index) throw() {
    this->_index = index;
}

const vector<string>& Route::getIndex(void) const throw() {
    return this->_index;
}

void Route::setFile(string& file) throw() {
    _index.push_back(file);
}

void Route::setUploadDir(string& directory) throw() {
    this->_uploadPath = directory;
}

const string& Route::getUploadDir(void) const throw() {
    return this->_uploadPath;
}

void Route::setRoot(const string& root) {
    if (this->_root.size() != 0)
        throw DuplicateRoot();
    this->_root = root;
}

const string& Route::getRoot(void) const throw() {
    return this->_root;
}

void Route::setCGI(const vector<std::pair<string, string> >& cgi) throw() {
    this->_cgi = cgi;
}

const vector<std::pair<string, string> >& Route::getCGI(void) const throw() {
    return this->_cgi;
}

void Route::pushCGI(const std::pair<string, string>& CGIPair) throw() {
    this->_cgi.push_back(CGIPair);
}

const char* Route::DuplicateRoot::what() const throw() {
    return "Duplicate root directive";
}

const char* Route::InvalidDirective::what() const throw() {
    return "Invalid directive detected in location block";
}