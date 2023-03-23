
cmake_minimum_required(VERSION 3.10.2)


project("mongoose_test")

set(CMAKE_CXX_STANDARD 17)
include_directories(third-party/mongoose)
include_directories(third-party/cJSON)
include_directories(third-party/inifile)
include_directories(mysql)

set(MYSQL_INSTALL "D:/Program Files/mysql-8.0.32-winx64/mysql-8.0.32-winx64")
include_directories(${MYSQL_INSTALL}/include)
find_library(MYSQL_LIB libmysql HINTS ${MYSQL_INSTALL} PATH_SUFFIXES lib)
message("*****(MYSQL_LIB)*****=${MYSQL_LIB}")
message("*****(MYSQL_INSTALL)*****=${MYSQL_INSTALL}")


add_executable(mysql mysql/test.cpp mysql/dBConnection_mysql.cpp mysql/dBConnection_mysql.h  mysql/DBconfig.h)
target_link_libraries(mysql PRIVATE ${MYSQL_LIB})



add_executable(server server/server.cpp third-party/mongoose/mongoose.c third-party/cJSON/cJSON.c mysql/dBConnection_mysql.cpp mysql/dBConnection_mysql.h  mysql/DBconfig.h)
target_link_libraries(server PRIVATE ${MYSQL_LIB})

add_executable(client client/client.cpp third-party/mongoose/mongoose.c third-party/cJSON/cJSON.c)

add_executable(inifile_test third-party/inifile/test.cpp)



# target_link_libraries(main_client PRIVATE ${CPPRESTSDK_LIB})
