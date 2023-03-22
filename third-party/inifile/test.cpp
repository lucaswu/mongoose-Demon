#include "xini_file.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <locale>

int main()
{
    std::string fileName = "config.ini";
    xini_file_t xini_file(fileName);

    std::string ip = (const char*)xini_file["dataBase"]["ip"];
    std::string port = (const char*)xini_file["dataBase"]["port"];
    std::string dbName = (const char*)xini_file["dataBase"]["dbName"];
    std::string user = (const char*)xini_file["dataBase"]["user"];
    std::string passwd = (const char*)xini_file["dataBase"]["passwd"];

    printf("ip:%s\nport:%s\ndbName:%s\nuser:%s\npasswd:%s\n",ip.c_str(), port.c_str(),dbName.c_str(),user.c_str(),passwd.c_str());

    printf("over!\n");
    
}