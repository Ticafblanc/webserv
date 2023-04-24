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
    _client_body_max_size = 0;
    _client_body_max_status = false;
}

Route::~Route() {}

void Route::printAll(void) {
    cout << "Allowed methods: ";
    if (_allowed_methods.size() == 0)
        cout << "all" << endl;
    else {
        for (std::size_t i = 0; i < _allowed_methods.size(); i++) {
            cout << _allowed_methods.at(i) << " ";
        }
    }
    cout << endl;
    cout << "prefix: " << _prefix << endl;
    cout << "http code: " << _httpRedir.first << " path: " << _httpRedir.second << endl;
    cout << "max body size: " << _client_body_max_size << endl;
    cout << "autoindex status: " << _autoIndex << endl;
    cout << "search dir: " << _searchDir << endl;
    cout << "root: " << _root << endl;
    cout << "upload path: " << _uploadPath << " " << endl;
    cout << endl;
    for (std::size_t i = 0; i < _cgi.size(); i++) {
        cout << "extension: " << _cgi.at(i).first << " executable: " << _cgi.at(i).second << " ";
    }
    cout << endl;
}

void Route::setPrefix(string& prefix) throw() {
    this->_prefix = prefix;
}

const string& Route::getPrefix(void) const throw() {
    return this->_prefix;
}

void Route::setHttpRedir(std::pair<string, string> redir) throw() {
    this->_httpRedir = redir;
} 

std::pair<string, string> Route::getHttpRedir(void) const throw() {
    return this->_httpRedir;
}

void Route::setDirectoryListing(bool state) throw() {
    this->_autoIndex = state;
}

bool Route::getDirectoryListing(void) const throw() {
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
    if (this->_root.size() != 0) {
        cout << "problem is in location" << endl;
        throw DuplicateRoot();
    }
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

void Route::setBodyMaxSize(const std::size_t size) throw() {
    this->_client_body_max_size = size;
}

std::size_t Route::getBodyMaxSize(void) const throw() {
    return this->_client_body_max_size;
}

void Route::setBodyMaxStatus(const bool status) throw() {
    this->_client_body_max_status = status;
}

bool Route::getBodyMaxStatus(void) const throw() {
    return this->_client_body_max_status;
}

const char* Route::DuplicateRoot::what() const throw() {
    return "Duplicate root directive";
}

const char* Route::InvalidDirective::what() const throw() {
    return "Invalid directive detected in location block";
}