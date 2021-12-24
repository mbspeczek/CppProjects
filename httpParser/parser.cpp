#include "parser.h"
#include <sstream>
Parser::Parser(){}

ParsedMessage Parser::parse(const char* requestString){
    ParsedMessage pMessage;
    std::string request(requestString);
    std::vector<std::string> splitedRequest(Parser::splitMessageByLines(request));
    std::vector<std::string> separatedRequestLine (Parser::getHTTPSeparatedRequestLineFromSplitedRequest(splitedRequest));

    pMessage.requestMethod = Parser::getHTTPRequestMethod(separatedRequestLine);
    pMessage.requestProtocol = Parser::getHTTPRequestProtocolAndVersion(separatedRequestLine);
    pMessage.requestResourcePath = Parser::getHTTPRequestResourcePath(separatedRequestLine);
    
    pMessage.headers = Parser::getHTTPRequestHeadersFromSplitedRequest(splitedRequest);
    pMessage.body = Parser::getHTTPRequestBodySplitedByLine(splitedRequest);
    
    return pMessage;
}

std::vector<std::string> Parser::splitMessageByLines(std::string message){
    std::stringstream stream(message);
    std::string line;
    std::vector<std::string> linesVector;
    while (getline(stream, line,'\n'))
    {
        linesVector.push_back(line);
    }
    
    return linesVector;
}

std::vector<std::string> Parser::splitMassageByCharDelim(std::string message, const char delim){
    std::stringstream stream(message);
    std::string line;
    std::vector<std::string> linesVector;
    while (getline(stream, line, delim))
    {
        std::cout<<line<<std::endl;
        linesVector.push_back(line);
    }
    
    return linesVector;
}

std::vector<std::string>  Parser::getHTTPSeparatedRequestLineFromSplitedRequest(const std::vector<std::string>  & request){
    std::string requestLineParameter;
    std::stringstream requestString(request[0]);
    std::vector<std::string> requestLineParsed;

    while(getline(requestString, requestLineParameter, ' '))
    {
        requestLineParsed.push_back(requestLineParameter);
    }
    return requestLineParsed;
}

std::string Parser::getHTTPRequestProtocolAndVersion(const std::vector<std::string>  & requestLine){
    return requestLine[2];
}

std::string Parser::getHTTPRequestResourcePath(const std::vector<std::string>  & requestLine){
    return requestLine[1];
}

std::string Parser::getHTTPRequestMethod(const std::vector<std::string>  & requestLine){
    return requestLine[0];
}

StringMap Parser::getHTTPRequestHeadersFromSplitedRequest(const std::vector<std::string> & splitedRequest){
    std::map<std::string,std::string> headers;
    int i = 1;
    if(splitedRequest.size()>0){
        while(splitedRequest.at(i)!="")
        {   
            std::string line(splitedRequest.at(i));
            int delimPosition = line.find(':');
            headers.insert(std::make_pair(line.substr(0, delimPosition), line.substr(delimPosition+2, line.size()) ) );
            
            //std::cout<<i<<"/"<<splitedRequest.size()-1<<splitedRequest.at(i)<<std::endl;
            i++;
            if(i>splitedRequest.size()-1)break;
        
        }

        return headers;
    }
    
    headers.insert(std::make_pair("ERROR","ERROR"));
    return headers;
}


int Parser::getHeaderAndBodyDelimiterPosition(const std::vector<std::string> & splitedRequest){
    int delimiterPosition = 0;
    while (splitedRequest.at(delimiterPosition)!="")
    {
        delimiterPosition++;
    }
    return delimiterPosition;
}


std::vector<std::string> Parser::getHTTPRequestBodySplitedByLine(const std::vector<std::string> & splitedRequest){
    int delimiter = getHeaderAndBodyDelimiterPosition(splitedRequest) + 1;
    std::vector<std::string> bodyVector;
    for(int i = delimiter;i<splitedRequest.size();i++){
        bodyVector.push_back(splitedRequest.at(i));
    }

    return bodyVector;
}