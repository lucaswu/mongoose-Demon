#pragma once
#include <string>
#include <mysql.h>
#include <vector>
#include <memory>
class DBConnectionMySQL
{
public:
   
    static DBConnectionMySQL& Instance()
    {
        static DBConnectionMySQL mInstance;
        return mInstance;
    }

    DBConnectionMySQL();
    std::vector<std::vector<std::string>> getDbData(std::string &sql);
    
private:
    
    
    MYSQL* connectDB();

    
};