//
// Created by Matthis DoQuocBao on 2023-06-07.
//

#include <Source_Code/1-Config/Includes/Code.class.hpp>

Code::Code() : _mapStatusCode(), _statusCode(200){
    buildStatusCode();
}

Code::~Code() {}

Code::Code(const Code &other) : _mapStatusCode(other._mapStatusCode), _statusCode(other._statusCode){}

Code &Code::operator=(const Code &rhs) {
    this->_mapStatusCode = rhs._mapStatusCode;
    this->_statusCode = rhs._statusCode;
    return *this;
}

void Code::buildStatusCode() {
    /**
     * https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
     */

    /**
     *  the server has received the client's request headers and is ready
     * to receive the request body. It allows the client to proceed with sending the request.
     */
    _mapStatusCode[100] = std::make_pair("Continue", "usr/local/var/www/html/100.html");

    /**
     * the server agrees to switch to a different protocol, specified in the response's "Upgrade"
     * header. For example, it can be used when a client requests an upgrade to the WebSocket protocol.
     */
    _mapStatusCode[101] = std::make_pair("Switching Protocols", "usr/local/var/www/html/101.html");

    /**
     * the server has received the client's request and is currently processing it, but the final
     * response is not yet available.
     */
    _mapStatusCode[102] = std::make_pair("Processing", "usr/local/var/www/html/102.html");

    /**
     *  the client's request has been successfully processed, and the corresponding response is being returned.
     */
    _mapStatusCode[200] = std::make_pair("OK", "usr/local/var/www/html/200.html");

    /**
     * the request has been successfully processed and a new resource has been created as a result.
     * For example, when a new record is created in a database.
     */
    _mapStatusCode[201] = std::make_pair("Created", "usr/local/var/www/html/201.html");

    /**
     * the request has been accepted for processing, but the processing is not yet complete.
     * The final response may be returned later.
     */
    _mapStatusCode[202] = std::make_pair("Accepted", "usr/local/var/www/html/202.html");

    /**
     * the request has been successfully processed, but the response does not contain any content to be returned.
     * For example, when a deletion request is successful but no additional response is needed.
     */
    _mapStatusCode[204] = std::make_pair("No Content", "usr/local/var/www/html/204.html");

    /**
     * the response contains only a portion of the requested resource. This typically occurs in
     * the case of range requests, where the client requests only a specific part of the resource.
     */
    _mapStatusCode[206] = std::make_pair("Partial Content", "usr/local/var/www/html/206.html");

    /**
     * the response may contain multiple options, and the client needs to choose from them.
     * For example, when a URL redirects to multiple other possible URLs.
     */
    _mapStatusCode[300] = std::make_pair("Multiple Choices", "usr/local/var/www/html/300.html");

    /**
     * the requested resource has been permanently moved to a new URL.
     * The client is typically instructed to update its links and use the new URL.
     */
    _mapStatusCode[301] = std::make_pair("Moved Permanently", "usr/local/var/www/html/301.html");

    /**
     *  the requested resource has been temporarily moved to a different URL.
     *  The client is typically instructed to follow the redirection.
     */
    _mapStatusCode[302] = std::make_pair("Found", "usr/local/var/www/html/302.html");

    /**
     * the requested resource has not been modified since the client's last request,
     * and therefore the response is empty. The client can use the locally cached copy of the resource.
     */
    _mapStatusCode[304] = std::make_pair("Not Modified", "usr/local/var/www/html/304.html");

    /**
     *  the requested resource has been temporarily moved to a different URL.
     *  The client is typically instructed to follow the redirection while maintaining
     *  the original request method.
     */
    _mapStatusCode[307] = std::make_pair("Temporary Redirect", "usr/local/var/www/html/307.html");

    /**
     * the requested resource has been permanently moved to a new URL. The client is typically
     * instructed to follow the redirection while maintaining the original request method.
     */
    _mapStatusCode[308] = std::make_pair("Permanent Redirect", "usr/local/var/www/html/308.html");

    /**
     * the client's request is incorrect or malformed and cannot be processed by the server.
     */
    _mapStatusCode[400] = std::make_pair("Bad Request", "usr/local/var/www/html/400.html");

    /**
     * authentication is required to access the requested resource, but the client has not
     * provided valid credentials or is not authorized to access the resource.
     */
    _mapStatusCode[401] = std::make_pair("Unauthorized", "usr/local/var/www/html/401.html");

    /**
     * the client is not authorized to access the requested resource,
     * even after successful authentication.
     */
    _mapStatusCode[403] = std::make_pair("Forbidden", "usr/local/var/www/html/403.html");

    /**
     * the requested resource could not be found on the server.
     */
    _mapStatusCode[404] = std::make_pair("Not Found", "usr/local/var/www/html/404.html");

    /**
     *  the request method used by the client is not allowed for the requested resource.
     *  For example, if a client attempts to use a POST method for a resource accept only GET methode
     */
    _mapStatusCode[405] = std::make_pair("Method Not Allowed", "usr/local/var/www/html/405.html");

    /**
     * the request cannot be completed due to a conflict with the current state of the resource.
     * For example, when there is a versioning conflict or a conflict between concurrent requests.
     */
    _mapStatusCode[409] = std::make_pair("Conflict", "usr/local/var/www/html/409.html");

    /**
     * the requested resource is no longer available on the server and there is no forwarding address.
     * It is similar to a 404 error but indicates that the resource is permanently gone.
     */
    _mapStatusCode[410] = std::make_pair("Gone", "usr/local/var/www/html/410.html");

    /**
     * the client has sent too many requests within a given time frame and has exceeded the server's
     * rate limiting policy. It is often used to prevent abuse or to ensure fair usage.
     */
    _mapStatusCode[429] = std::make_pair("Too Many Requests", "usr/local/var/www/html/429.html");

    /**
     * an unexpected error occurs on the server that prevents it from fulfilling the client's request.
     * It indicates a server-side issue.
     */
    _mapStatusCode[500] = std::make_pair("Internal Server.class Error", "usr/local/var/www/html/500.html");

    /**
     * the server does not support the functionality required to fulfill the request.
     * It typically indicates that the server lacks the capability to handle the requested method.
     */
    _mapStatusCode[501] = std::make_pair("Not Implemented", "usr/local/var/www/html/501.html");

    /**
     * the server acting as a gateway or proxy receives an invalid response from an upstream server.
     */
    _mapStatusCode[502] = std::make_pair("Bad Gateway", "usr/local/var/www/html/502.html");

    /**
     * the server is temporarily unable to handle the request due to being overloaded or undergoing maintenance.
     * It indicates a temporary unavailability of the server.
     */
    _mapStatusCode[503] = std::make_pair("Service Unavailable", "usr/local/var/www/html/503.html");

    /**
     * the server acting as a gateway or proxy does not receive a timely response from an upstream server.
     */
    _mapStatusCode[504] = std::make_pair("Gateway Timeout", "usr/local/var/www/html/504.html");

    /**
     * the server does not support the HTTP protocol version used in the request.
     */
    _mapStatusCode[505] = std::make_pair("HTTP Version Not Supported", "usr/local/var/www/html/505.html");
}

std::string Code::getStatusCode() const {
    std::string status(intToString(_statusCode));
    status += " ";
    status += _mapStatusCode.at(_statusCode).first;
    return status;
}

const std::string & Code::getStatusPage() const {
    return _mapStatusCode.at(_statusCode).second;
}

void Code::setStatusCode(int code) {
    _statusCode = code;
}

int Code::getCode() const {
    return _statusCode;
}

void Code::setDefaultPage(int code, const std::string& pathToHtmlPage) {
    if (FindCode(code))
        *const_cast<std::string *>(&_mapStatusCode.at(code).second) = pathToHtmlPage;
}

void Code::setStatus(int code, const std::string& status) {
    if (FindCode(code))
        *const_cast<std::string *>(&_mapStatusCode.at(_statusCode).first) = status;
}

void Code::setNewCode(int code, const std::string &status, const std::string &pathToHtmlPage) {
    if (!FindCode(code)){
        _mapStatusCode[code] = std::make_pair(status, pathToHtmlPage);
    }
}

bool Code::FindCode(int code) {
    return _mapStatusCode.find(code) != _mapStatusCode.end();
}


