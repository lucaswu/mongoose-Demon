#pragma once
#include <string>
#include "../inifile/xini_file.h"
class DBConfig
{
public:
    static DBConfig& Instance()
    {  
        static DBConfig mInstance;
        return mInstance;
    }

    std::string getIP() {
        return mIp;
    }

    std::string getPort() {
        return mPort;
    }

    std::string getDBName() {
        return mDBName;
    }

    std::string getUserName() {
        return mUser;
    }
    std::string getPasswd() {
        return mPasswd;
    }
private:
    DBConfig() {
        std::string fileName = "config.ini";
        xini_file_t xini_file(fileName);

        mIp = (const char*)xini_file["dataBase"]["ip"];
        mPort = (const char*)xini_file["dataBase"]["port"];
        mDBName = (const char*)xini_file["dataBase"]["dbName"];
        mUser = (const char*)xini_file["dataBase"]["user"];
        mPasswd = (const char*)xini_file["dataBase"]["passwd"];
    }

    

    std::string mIp;
    std::string mPort;
    std::string mDBName;
    std::string mUser;
    std::string mPasswd;
};