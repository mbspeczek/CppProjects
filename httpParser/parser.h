#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>

typedef std::map<std::string,std::string> StringMap;

struct ParsedMessage{
    std::string                 requestMethod;
    std::string                 requestProtocol;
    std::string                 requestResourcePath;
    StringMap                   headers;
    std::vector<std::string>    body;
};

class Parser{
public:
Parser();
ParsedMessage               parse(const char* request);

std::vector<std::string>    splitMessageByLines(std::string message);
std::vector<std::string>    splitMassageByCharDelim(std::string message, const char delim);

std::vector<std::string>    getHTTPSeparatedRequestLineFromSplitedRequest(const std::vector<std::string>  & splitedRequest);
std::string                 getHTTPRequestMethod(const std::vector<std::string>  & requestLine);
std::string                 getHTTPRequestProtocolAndVersion(const std::vector<std::string>  & requestLine);
std::string                 getHTTPRequestResourcePath(const std::vector<std::string>  & requestLine);


StringMap                   getHTTPRequestHeadersFromSplitedRequest(const std::vector<std::string> & splitedRequest);
std::vector<std::string>    getHTTPRequestBodySplitedByLine(const std::vector<std::string> & splitedRequest);
int                         getHeaderAndBodyDelimiterPosition(const std::vector<std::string> & splitedRequest);
protected:
private:

};



#endif