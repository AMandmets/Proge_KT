#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

int main(int argc, char** argv)
{
    MYSQL* con = mysql_init(NULL);
    MYSQL_RES* res;
    MYSQL_ROW row;

    if (con == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", "L4ste4i40pet4j4", "raamatud", 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }

    char b[20];
    int tegevus;
    char vastus[500];
    char a[500];
    char raamat_nimi[100];
    char autor[100];
    char raamat_id[2];
    char c[500];

    printf("---Raamatukogu andmebaas---");
    printf("Valige tegevus, mida soovite ning sisestage sellele vastav number: \n");
    printf("-> 1 Raamatute kuvamine\n");
    printf("-> 2 Raamatute otsimine\n");
    printf("-> 3 Raamatute lisamine\n");

    do {
        fgets(b, sizeof b, stdin);
        tegevus = atoi(b);
        if (tegevus > 0 && tegevus < 4)
        {
            char* tegevusstr = "";
            if (tegevus == 1) {
                tegevusstr = "kuvamine";
            }
            else if (tegevus == 2) {
                tegevusstr = "otsimine";
            }
            else if (tegevus == 3) {
                tegevusstr = "lisamine";
            }
            printf("----- Valisite tegevuse raamatute %s -----\n", tegevusstr);
        }
        else {
            printf("Te ei valinud tegevust! \n");
            exit(0);
        }
    } while (tegevus < 0 || tegevus > 3);

    switch (tegevus)
    {
    case 1:
        if (mysql_query(con, "SELECT nimi, autor FROM raamatud")) {
            fprintf(stderr, "%s\n", mysql_error(con));
            exit(2);
        }
        res = mysql_use_result(con);

        while ((row = mysql_fetch_row(res)) != NULL) {
            printf("%s ----- %s \n", row[0], row[1]);
        }
        mysql_free_result(res);
        break;

    case 2:
        printf("\nSisestage raamatu nimi:");

        if (fgets(vastus, sizeof vastus, stdin)) {
            char* newline = strchr(vastus, '\n');
            if (newline) {
                *newline = 0;
            }
        }
        
        sprintf(a, "SELECT nimi, autor FROM raamatud WHERE nimi like '%%%s%%' ", vastus);

        if (mysql_query(con, a)) {
            fprintf(stderr, "%s\n", mysql_error(con));
            exit(1);
        }
        res = mysql_use_result(con);

        while ((row = mysql_fetch_row(res)) != NULL) {
            printf("%s --- %s\n", row[0], row[1]);
        }
        mysql_free_result(res);
        break;

    case 3:
        printf("Sisesta autori nimi:");
        if (fgets(autor, sizeof autor, stdin)) {
            char* newline = strchr(autor, '\n');
            if (newline) {
                *newline = 0;
            }
        }
        printf("Sisesta raamatu nimi:\n");
        if (fgets(raamat_nimi, sizeof raamat_nimi, stdin)) {
            char* newline = strchr(raamat_nimi, '\n');
            if (newline) {
                *newline = 0;
            }
        }
        printf("Sisesta raamatu id:\n");
        if (fgets(raamat_id, sizeof raamat_id, stdin)) {
            char* newline = strchr(raamat_id, '\n');
            if (newline) {
                *newline = 0;
            }
        }
        
        sprintf(c, "INSERT INTO raamatud (id, nimi, autor) VALUES ('%s', '%s', '%s')", raamat_id, raamat_nimi, autor);
        if (mysql_query(con, c)) {
            fprintf(stderr, "%s\n", mysql_error(con));
            exit(1);
        }
        
        if (mysql_query(con, "SELECT * FROM raamatud")) {
            fprintf(stderr, "%s\n", mysql_error(con));
            exit(1);
        }

        res = mysql_use_result(con);

        while ((row = mysql_fetch_row(res)) != NULL) {
            printf("%s %s %s\n", row[0], row[1], row[2]);
        }
        mysql_free_result(res);
        break;
    }


    /*if (mysql_query(con, "INSERT INTO raamatud (id, nimi, autor_eesnimi, autor_perenimi) VALUES ('3', 'Emma', 'Jane', 'Austen')"))
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }*/
    /*if (mysql_query(con, "SELECT nimi FROM raamatud WHERE autor_perenimi = 'Austen'")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(2);
    }
    res = mysql_use_result(con);

    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%s\n", row[0]);
    }
    mysql_free_result(res);
    */
    mysql_close(con);
    exit(0);
}

