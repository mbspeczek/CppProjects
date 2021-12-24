#include <iostream>
#include "parser.h"

int main(){

    Parser parser;
    

    char request[] = "GET /favicon.ico HTTP/1.1\nHost: 192.168.1.13:50000\nConnection: keep-alive\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/95.0.4638.69 Safari/537.36 OPR/81.0.4196.61\nAccept: image/avif,image/webp,image/apng,image/svg+xml,image/*,*/*;q=0.8\nReferer: http://192.168.1.13:50000/\nAccept-Encoding: gzip, deflate\nAccept-Language: pl-PL,pl;q=0.9,en-US;q=0.8,en;q=0.7\n\nbody\nbody2\n\0";
    char msg[]= "HTTP/1.1 200 OK\nContent-Length: 179\nContent-Type: text/html\n\n<!DOCTYPE html><html><head><title>Test page with form</title></head><body><h1>test</h1><form action='#' method='POST'><input type='text'><input type='submit'></form></body></html>\r";
                    
    ParsedMessage pMessage(parser.parse(msg));
    
    std::cout<<pMessage.requestMethod<<" "<<pMessage.requestProtocol<<" "<<pMessage.requestResourcePath<<std::endl;

    for(auto &i: pMessage.headers){
        std::cout<<i.first<<" "<<i.second<<std::endl;
    }
    for(auto &i: pMessage.body){
        std::cout<<i<<std::endl;
    }


    /*
    auto splittedRequest = parser.splitMessageByLines(request);

    for( auto &i: splittedRequest){
        std::cout<<i<<std::endl;
    }    

    auto headers = parser.getHTTPRequestHeadersFromSplitedRequest(splittedRequest);

    for(auto &header: headers){
        std::cout<<header.first<<" "<<header.second<<std::endl;
    }

    std::cout<<headers["Host"]<<std::endl;
   
    std::vector<std::string> vectorOfStrings = {"ada","koza","","piesek"};

    std::cout<<parser.getHeaderAndBodyDelimiterPosition(vectorOfStrings);

    std::vector<std::string> bodyvec(parser.getHTTPRequestBodySplitedByLine(splittedRequest));

    for( auto & bodyLine: bodyvec){
        std::cout<<bodyLine<<std::endl;
    }
    */

    return 0;
}

