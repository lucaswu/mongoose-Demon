
cmake_minimum_required(VERSION 3.10.2)


project("mongoose_test")

set(CMAKE_CXX_STANDARD 17)
include_directories(third-party/mongoose)
include_directories(third-party/cJSON)
add_executable(server server/server.cpp third-party/mongoose/mongoose.c third-party/cJSON/cJSON.c)
add_executable(client client/client.cpp third-party/mongoose/mongoose.c third-party/cJSON/cJSON.c)
# target_link_libraries(main_client PRIVATE ${CPPRESTSDK_LIB})
