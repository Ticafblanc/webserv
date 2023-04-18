#include "../Include/Route.class.hpp"

Route::Route() {
    _autoIndex = false;
}

Route::~Route() {}

void Route::setPrefix(string& prefix) throw() {
    this->_prefix = prefix;
}

string& Route::getPrefix(void) throw() {
    return this->_prefix;
}

void Route::setHttpRedir(string& redir) throw() {
    this->_httpRedir = redir;
} 

string& Route::getHttpRedir(void) throw() {
    return this->_httpRedir;
}

void Route::setDirectoryListing(bool state) throw() {
    this->_autoIndex = state;
}

bool Route::getDirectoryListing(void) throw() {
    return this->_autoIndex;
}

void Route::setSearchDir(string& dir) throw() {
    this->_searchDir = dir;
}

string& Route::getSearchDir(void) throw() {
    return this->_searchDir;
}

void Route::setDefaultDirFile(string& dirFile) throw() {
    this->_defaultDirFile = dirFile;
}

string& Route::getDefaultDirFile(void) throw() {
    return this->_defaultDirFile;
}

void Route::setSavePath(string& path) throw() {
    this->_savePath = path;
}

string& Route::getSavePath(void) throw() {
    return this->_savePath;
}