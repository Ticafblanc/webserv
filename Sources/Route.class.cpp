#include "../Include/Route.class.hpp"

void Route::setAllowedMethods(vector<string>& allowed_methods) throw() {
    this->_allowed_methods = allowed_methods;
}

const vector<string>& Route::getAllowedMethods(void) const throw() {
    return _allowed_methods;
}

void Route::push_method(const string& method) throw() {
    _allowed_methods.push_back(method);
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

void Route::setDefaultDirFile(string& dirFile) throw() {
    this->_defaultDirFile = dirFile;
}

const string& Route::getDefaultDirFile(void) const throw() {
    return this->_defaultDirFile;
}

void Route::setSavePath(string& path) throw() {
    this->_savePath = path;
}

const string& Route::getSavePath(void) const throw() {
    return this->_savePath;
}

void Route::setRoot(const string& root) {
    if (this->_root.size() != 0)
        throw DuplicateRoot();
    this->_root = root;
}

const string& Route::getRoot(void) const throw() {
    return this->_root;
}

const char* Route::DuplicateRoot::what() const throw() {
    return "Duplicate root directive";
}