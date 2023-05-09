#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    MYSQL* con = mysql_init(NULL);
    MYSQL_RES* res;
    MYSQL_ROW row;

    if(con == NULL){
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }

    if(mysql_real_connet(con, "server", "username", "password", "raamatukogu", 3306, NULL, 0) == NULL){
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }

    printf("Raamatukogu andmebaas\n");

    if(mysql_query(con, "SELECT * FROM raamatud")){
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }

    res = mysql_use_result(con);
    while((row = mysql_fetch_row(res)) != NULL ){
        printf("%s\n", row[1]);
    }
    mysql_free_result(res);

    mysql_close(con);
    exit(0);
}