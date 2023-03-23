#include "dBConnection_mysql.h"
#include "DBconfig.h"
#include <string>

DBConnectionMySQL::DBConnectionMySQL()
{
	
}

MYSQL* DBConnectionMySQL::connectDB()
{
	DBConfig config = DBConfig::Instance();
	std::string ip = config.getIP();
	std::string port = config.getPort();
	std::string dbName = config.getDBName();
	std::string useName = config.getUserName();
	std::string userPasswd = config.getPasswd();

	MYSQL *conn = mysql_init(NULL);
	if (conn == NULL) {
		printf("mysql_init error!\n");
		return nullptr;
	}

	conn = mysql_real_connect(conn, ip.c_str(), useName.c_str(), userPasswd.c_str(), dbName.c_str(), atoi(port.c_str()), NULL, 0);
	if (conn == NULL) {
		printf("mysql_real_connect error:%s\n", mysql_error(conn));
		return nullptr;
	}
	mysql_set_character_set(conn, "utf8");
	return conn;
}

std::vector<std::vector<std::string>> DBConnectionMySQL::getDbData(std::string &sql)
{
	std::vector<std::vector<std::string>> data;
	if (sql.empty() ){
		return data;
	}

	auto conn = connectDB();
	if (!conn) {
		return data;
	}


	auto ret = mysql_query(conn,sql.c_str());
	if (ret != 0) {
		printf("mysql_query[%s]:%s\n",sql.c_str(), mysql_error(conn));
		return data;
	}

	auto res = mysql_use_result(conn);
	if (res == nullptr) {
		printf("mysql_use_result error:%s\n", mysql_error(conn));
		return data;
	}

	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)) != NULL) {
		std::vector<std::string> rowData;
		auto num_fields = mysql_num_fields(res);

		for (int i = 0; i < num_fields; i++) {
			std::string value = std::string((const char*)row[i]);
			rowData.emplace_back(std::move(value));
		}
		data.emplace_back(std::move(rowData));
	}

	mysql_free_result(res);
	mysql_close(conn);

	return data;
}