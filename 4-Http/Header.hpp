//
// Created by Matthis DoQuocBao on 2023-06-07.
//

#ifndef WEBSERVER_HEADER_HPP
#define WEBSERVER_HEADER_HPP

#include "0-Main/Includes/Headers.hpp"
struct  requestHeader{
    std::map<std::string, std::string (HttpMessage::*)()>  _map_token_list_action_information;
    request_header() {
        values.push_back("Accept: ");
        values.push_back("Accept-Charset: ");
        values.push_back("Accept-Datetime: ");
        values.push_back("Accept-Encoding: ");
        values.push_back("Accept-Language: ");
        values.push_back("Accept-Patch: ");
        values.push_back("Accept-Ranges: ");
        values.push_back("Access-Control-Allow-Credentials: ");
        values.push_back("Access-Control-Allow-Headers: ");
        values.push_back("Access-Control-Allow-Methods: ");
        values.push_back("Access-Control-Allow-Origin: ");
        values.push_back("Access-Control-Expose-Headers: ");
        values.push_back("Access-Control-Max-Age: ");
        values.push_back("Access-Control-Request-Method: ");
        values.push_back("Access-Control-Request-Headers: ");
        values.push_back("Age: ");
        values.push_back("Allow: ");
        values.push_back("Alt-Svc: ");
        values.push_back("Authorization: ");
        values.push_back("Cache-Control: ");
        values.push_back("Connection: ");
        values.push_back("Content-Disposition: ");
        values.push_back("Content-Encoding: ");
        values.push_back("Content-Language: ");
        values.push_back("Content-Length: ");
        values.push_back("Content-Location: ");
        values.push_back("Content-MD5: ");
        values.push_back("Content-Range: ");
        values.push_back("Content-Type: ");
        values.push_back("Cookie: ");
        values.push_back("DASL: ");
        values.push_back("Date: ");
        values.push_back("DAV: ");
        values.push_back("Depth: ");
        values.push_back("Destination: ");
        values.push_back("DNT (Do Not Track): ");
        values.push_back("ETag: ");
        values.push_back("Expect: ");
        values.push_back("Expires: ");
        values.push_back("Forwarded: ");
        values.push_back("From: ");
        values.push_back("Host: ");
        values.push_back("If: ");
        values.push_back("If-Match: ");
        values.push_back("If-Modified-Since: ");
        values.push_back("If-None-Match: ");
        values.push_back("If-Range: ");
        values.push_back("If-Unmodified-Since: ");
        values.push_back("IM (Instance Manipulation): ");
        values.push_back("Last-Modified: ");
        values.push_back("Link: ");
        values.push_back("Location: ");
        values.push_back("Lock-Token: ");
        values.push_back("Max-Forwards: ");
        values.push_back("MIME-Version: ");
        values.push_back("Origin: ");
        values.push_back("Overwrite: ");
        values.push_back("P3P (Platform for Privacy Preferences): ");
        values.push_back("Pragma: ");
        values.push_back("Prefer: ");
        values.push_back("Preference-Applied: ");
        values.push_back("Proxy-Authenticate: ");
        values.push_back("Proxy-Authorization: ");
        values.push_back("Proxy-Connection: ");
        values.push_back("Range: ");
        values.push_back("Referer: ");
        values.push_back("Retry-After: ");
        values.push_back("Server: ");
        values.push_back("Set-Cookie: ");
        values.push_back("SLUG: ");
        values.push_back("SOAPAction: ");
        values.push_back("Status-URI: ");
        values.push_back("Strict-Transport-Security: ");
        values.push_back("TE: ");
        values.push_back("Timeout: ");
        values.push_back("Trailer: ");
        values.push_back("Transfer-Encoding: ");
        values.push_back("Upgrade: ");
        values.push_back("User-Agent: ");
        values.push_back("Variant-Vary: ");
        values.push_back("Vary: ");
        values.push_back("Via: ");
        values.push_back("WWW-Authenticate: ");
        values.push_back("X-Forwarded-For: ");
        values.push_back("X-Forwarded-Proto: ");
        values.push_back("X-Frame-Options: ");
        values.push_back("X-XSS-Protection: ");
    }
};


#endif //WEBSERVER_HEADER_HPP
