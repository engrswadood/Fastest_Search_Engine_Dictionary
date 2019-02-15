#ifndef DB_GATEWAY_FILE
#define DB_GATEWAY_FILE

#include <my_global.h>
#include <mysql.h>
//////////////
#define USER "sultan"
#define PASSWORD "nauman"
#define DATA_BASE "token_db"
#define HOST "localhost"

///////////////////////////
MYSQL * get_connection();
void finish_with_error(MYSQL */*con*/);
void mysql_select_address(MYSQL */*con*/, char */*q*/);
void mysql_delete_address(MYSQL */*con*/, char */*q*/);
void mysql_insert_address(MYSQL */*con*/, char */*q*/);
void mysql_update_address(MYSQL */*con*/, char */*q*/);
void load_address_db();

#endif