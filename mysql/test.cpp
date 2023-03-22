#include "../inifile/xini_file.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <locale>
#include <mysql.h>


int main()
{
    std::string fileName = "config.ini";
    xini_file_t xini_file(fileName);

    std::string ip = (const char*)xini_file["dataBase"]["ip"];
    std::string port = (const char*)xini_file["dataBase"]["port"];
    std::string dbName = (const char*)xini_file["dataBase"]["dbName"];
    std::string user = (const char*)xini_file["dataBase"]["user"];
    std::string passwd = (const char*)xini_file["dataBase"]["passwd"];

    printf("ip:%s\nport:%s\ndbName:%s\nuser:%s\npasswd:%s\n", ip.c_str(), port.c_str(), dbName.c_str(), user.c_str(), passwd.c_str());

    
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        printf("error!\n");
        return -1;
    }

    auto ret = mysql_real_connect(conn, ip.c_str(), user.c_str(), passwd.c_str(), dbName.c_str(), atoi(port.c_str()), NULL, 0);
    if (ret == NULL) {
        printf("mysql_real_connect error!");
        return -1;
    }

    if (mysql_query(conn, "select * from tb_futures")) {
        printf("error:%s\n",mysql_error(conn));
        return -1;
    }

  
    res = mysql_use_result(conn);
    printf("id\tcontractNumber\theyue\tkaipingcang\tduokong\tnumber\tprice\tinDate\tcomment \n");
    while( (row = mysql_fetch_row(res) )!= NULL) {
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",(const char*)row[0]
            , (const char*)row[1]
            , (const char*)row[2]
            , (const char*)row[3]
            , (const char*)row[4]
            , (const char*)row[5]
            , (const char*)row[6]
            , (const char*)row[7]
            , (const char*)row[8]);
    }
    

    return 0;

}