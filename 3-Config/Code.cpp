//
// Created by Matthis DoQuocBao on 2023-06-07.
//

#include "Code.hpp"

Code::Code() : _mapStatusCode(), _statusCode(200){
    setStatusCode();
}

Code::~Code() {}

Code::Code(Code &other) : _mapStatusCode(other._mapStatusCode){}

Code &Code::operator=(const Code &rhs) {
    this->_mapStatusCode = rhs._mapStatusCode;
    return *this;
}

void Code::setStatusCode() {
    /**
     * https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
     */

    /**
     *  the server has received the client's request headers and is ready
     * to receive the request body. It allows the client to proceed with sending the request.
     */
    _mapStatusCode[100] = "Continue";

    /**
     * the server agrees to switch to a different protocol, specified in the response's "Upgrade"
     * header. For example, it can be used when a client requests an upgrade to the WebSocket protocol.
     */
    _mapStatusCode[101] = "Switching Protocols";

    /**
     * the server has received the client's request and is currently processing it, but the final
     * response is not yet available.
     */
    _mapStatusCode[102] = "Processing";

    /**
     *  the client's request has been successfully processed, and the corresponding response is being returned.
     */
    _mapStatusCode[200] = "200 OK";

    /**
     * the request has been successfully processed and a new resource has been created as a result.
     * For example, when a new record is created in a database.
     */
    _mapStatusCode[201] = "Created";

    /**
     * the request has been accepted for processing, but the processing is not yet complete.
     * The final response may be returned later.
     */
    _mapStatusCode[202] = "Accepted";

    /**
     * the request has been successfully processed, but the response does not contain any content to be returned.
     * For example, when a deletion request is successful but no additional response is needed.
     */
    _mapStatusCode[204] = "No Content";

    /**
     * the response contains only a portion of the requested resource. This typically occurs in
     * the case of range requests, where the client requests only a specific part of the resource.
     */
    _mapStatusCode[206] = "Partial Content";

    /**
     * the response may contain multiple options, and the client needs to choose from them.
     * For example, when a URL redirects to multiple other possible URLs.
     */
    _mapStatusCode[300] = "Multiple Choices";

    /**
     * the requested resource has been permanently moved to a new URL.
     * The client is typically instructed to update its links and use the new URL.
     */
    _mapStatusCode[301] = "Moved Permanently";

    /**
     *  the requested resource has been temporarily moved to a different URL.
     *  The client is typically instructed to follow the redirection.
     */
    _mapStatusCode[302] = "Found";

    /**
     * the requested resource has not been modified since the client's last request,
     * and therefore the response is empty. The client can use the locally cached copy of the resource.
     */
    _mapStatusCode[304] = "Not Modified";

    /**
     *  the requested resource has been temporarily moved to a different URL.
     *  The client is typically instructed to follow the redirection while maintaining
     *  the original request method.
     */
    _mapStatusCode[307] = "Temporary Redirect";

    /**
     * the requested resource has been permanently moved to a new URL. The client is typically
     * instructed to follow the redirection while maintaining the original request method.
     */
    _mapStatusCode[308] = "Permanent Redirect";

    /**
     * the client's request is incorrect or malformed and cannot be processed by the server.
     */
    _mapStatusCode[400] = "Bad Request";

    /**
     * authentication is required to access the requested resource, but the client has not
     * provided valid credentials or is not authorized to access the resource.
     */
    _mapStatusCode[401] = " Unauthorized";

    /**
     * the client is not authorized to access the requested resource,
     * even after successful authentication.
     */
    _mapStatusCode[403] = "Forbidden";

    /**
     * the requested resource could not be found on the server.
     */
    _mapStatusCode[404] = "Not Found";

    /**
     *  the request method used by the client is not allowed for the requested resource.
     *  For example, if a client attempts to use a POST method for a resource accept only GET methode
     */
    _mapStatusCode[405] = "Method Not Allowed";

    /**
     * the request cannot be completed due to a conflict with the current state of the resource.
     * For example, when there is a versioning conflict or a conflict between concurrent requests.
     */
    _mapStatusCode[409] = "Conflict";

    /**
     * the requested resource is no longer available on the server and there is no forwarding address.
     * It is similar to a 404 error but indicates that the resource is permanently gone.
     */
    _mapStatusCode[410] = "Gone";

    /**
     * the client has sent too many requests within a given time frame and has exceeded the server's
     * rate limiting policy. It is often used to prevent abuse or to ensure fair usage.
     */
    _mapStatusCode[429] = "Too Many Requests";

    /**
     * an unexpected error occurs on the server that prevents it from fulfilling the client's request.
     * It indicates a server-side issue.
     */
    _mapStatusCode[500] = "Internal Server Error";

    /**
     * the server does not support the functionality required to fulfill the request.
     * It typically indicates that the server lacks the capability to handle the requested method.
     */
    _mapStatusCode[501] = "Not Implemented";

    /**
     * the server acting as a gateway or proxy receives an invalid response from an upstream server.
     */
    _mapStatusCode[502] = "Bad Gateway";

    /**
     * the server is temporarily unable to handle the request due to being overloaded or undergoing maintenance.
     * It indicates a temporary unavailability of the server.
     */
    _mapStatusCode[503] = "Service Unavailable";

    /**
     * the server acting as a gateway or proxy does not receive a timely response from an upstream server.
     */
    _mapStatusCode[504] = "Gateway Timeout";

    /**
     * the server does not support the HTTP protocol version used in the request.
     */
    _mapStatusCode[505] = "HTTP Version Not Supported";
}

std::string &Code::getStatusCode() {
    return _mapStatusCode[_statusCode];
}