#include <iostream>
#include <string>
#include "mongoose.h"
#include "cJSON.h"

using namespace std;

std::string GetjsonData()
{
    cJSON* root = NULL;
    cJSON* family = NULL;
    cJSON* father = NULL;
    cJSON* mother = NULL;
    cJSON* birthday = NULL;
    char* output = NULL;
    char outputBuffer[1024];

    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "name", cJSON_CreateString("Zhang San"));
    cJSON_AddTrueToObject(root, "sex");
    cJSON_AddNumberToObject(root, "height", 1.8);
    family = cJSON_AddArrayToObject(root, "family");

    cJSON_AddItemToArray(family, father = cJSON_CreateObject());
    cJSON_AddItemToObject(father, "name", cJSON_CreateString("Zhang Si"));
    cJSON_AddItemToObject(father, "relationship", cJSON_CreateString("Father"));

    cJSON_AddItemToArray(family, mother = cJSON_CreateObject());
    cJSON_AddItemToObject(mother, "name", cJSON_CreateString("Li Si"));
    cJSON_AddItemToObject(mother, "relationship", cJSON_CreateString("Mother"));

    cJSON_AddItemToObject(root, "birthday", birthday = cJSON_CreateObject());
    cJSON_AddNumberToObject(birthday, "year", 2000);
    cJSON_AddNumberToObject(birthday, "month", 1);
    cJSON_AddNumberToObject(birthday, "day", 1);

   /* output = cJSON_Print(root);
    printf("cJSON_Print(): \n%s\n", output);

    output = cJSON_PrintUnformatted(root);
    printf("cJSON_PrintUnformatted(): \n%s\n", output);

    output = cJSON_PrintBuffered(root, (int)sizeof(root) + 5, 1);
    printf("cJSON_PrintBuffered(): \n%s\n", output);

    if (cJSON_PrintPreallocated(root, outputBuffer, 1000, 1))
        printf("cJSON_PrintPreallocated(): \n%s\n", outputBuffer);*/

    cJSON_PrintPreallocated(root, outputBuffer, 1000, 1);


    free(output);
    cJSON_Delete(root);

    return std::string(outputBuffer);
}
void callback(struct mg_connection* c, int ev, void* ev_data, void* fn_data) {
    switch (ev) {
    case MG_EV_HTTP_MSG:   
    {
        struct mg_http_message* hm = (struct mg_http_message*)ev_data;
        string method;
        method.assign(hm->method.ptr, hm->method.len);
        cout << method << endl;
        string uri;
        uri.assign(hm->uri.ptr, hm->uri.len);
        cout << uri << endl;
        if (mg_http_match_uri(hm, "/hello")) {
            //  if(hm->method.ptr == "GET") {
          /*  string body = "<html><body><h1>Hello Bit</h1></body></html>";
            string header = "Content-Type: text/html\r\n";
            mg_http_reply(c, 200, header.c_str(), "%s", body.c_str());*/
            //   }

            if (method == "GET") {
                string header = "Content-Type: application/json;charset:utf-8\r\n";
                string body = GetjsonData();
                mg_http_reply(c, 200, header.c_str(), "%s", body.c_str()); 
            }
        }
        //else if (mg_http_match_uri(hm, "/websocket")) {
        //    mg_ws_upgrade(c, hm, NULL);
        //}
        //else {
        //   
        //    struct mg_http_serve_opts opts ;
        //    opts.root_dir = "./web_root";
        //    mg_http_serve_dir(c, hm, &opts);
        //}
    }
    break;
    case MG_EV_WS_MSG: {
        struct mg_ws_message* wm = (struct mg_ws_message*)ev_data;
    }
                     break;
    case MG_EV_CLOSE: 
        break;
    default:
        break;
    }
    return;
}


int main() {
   
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    struct mg_connection* lst_http;
    lst_http = mg_http_listen(&mgr, "0.0.0.0:9000", callback, NULL);
    if (lst_http == NULL) {
        return -1;
    }
    while (1) {
        mg_mgr_poll(&mgr, 1000);
    }

    return 0;
}
