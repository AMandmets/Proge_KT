#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    if (mysql_real_connect(con, "84.50.64.44", "root", "Koertelemeeldibjalutada!1", "raamatukogu", 3306, NULL, 0) == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }

    printf("------Tere tulemast raamatukogu andmebaasi!------\n");
    int tegevus;
    char *vastus[100];
    printf("Valige tegevus, mida soovite ning sisestage sellele vastav number: \n");
    printf("1 Raamatute kuvamine\n");
    printf("2 Raamatute otsimine\n");
    printf("3 Raamatute lisamine\n");
    
    do {
        if(scanf("%d", &tegevus) > 0 && tegevus < 4)
        {
            printf("Valisite tegevuse %d \n", tegevus);
        }
        else printf("Te ei valinud tegevust! \n");

    } while (tegevus < 0 || tegevus > 3);

    switch(tegevus)
    {
        case 1:
            if (mysql_query(con, "SELECT * FROM raamatud")) {
                fprintf(stderr, "%s\n", mysql_error(con));
                exit(1);
            }
        break;

        case 2:
            printf("Sisestage raamatu nimi: \n");
            scanf_s("%s", vastus, (unsigned)_countof(vastus));

            if (mysql_query(con, "SELECT * FROM raamatud WHERE raamatud.nimi = vastus")) {
                fprintf(stderr, "%s\n", mysql_error(con));
                exit(1);
            }
        break;
    } 


    res = mysql_use_result(con);

    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%s\n", row[1]);
    }
    mysql_free_result(res); 

    mysql_close(con);
    exit(0);
}