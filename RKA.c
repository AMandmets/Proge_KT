#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#pragma warning(disable : 4996)
#pragma execution_character_set( "utf-8" )
#define MAX 50

MYSQL_RES* res;
MYSQL_ROW row;

int valimine(MYSQL*, MYSQL_RES*, MYSQL_ROW, int);
void kuvamine(MYSQL*, MYSQL_RES*, MYSQL_ROW, int);
void otsimine(MYSQL*, MYSQL_RES*, MYSQL_ROW, int);
void lisamine_valik(MYSQL*, MYSQL_RES*, MYSQL_ROW);
void raamatu_lisa(MYSQL*, MYSQL_RES*, MYSQL_ROW);
char raamatu_nimi();
int raamatu_id();
/*char autori_nimi(char*);
int autori_id(int);
char fkohaviit(char*);
int fkohaviida_id(int);
int fkoopia_id(int);
char faasta(char*);
int flaenutatud_id(int);
char ftriipkood(char*);
char fkeel(char*);
char fsanr(char*);
int fsanr_id(int);
*/
int main(int argc, char** argv) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    MYSQL* con = mysql_init(NULL);

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
    int tegevus = 0;
    printf("------Raamatukogu andmebaas------\n");
    valimine(con, res, row, tegevus);



}
int valimine(MYSQL* con, MYSQL_RES* res, MYSQL_ROW row, int tegevus) {
    char b[20];
    printf("\nValige tegevus, mida soovite ning sisestage sellele vastav number: \n");
    printf("-> 1 Raamatute kuvamine\n");
    printf("-> 2 Raamatute lisamine\n");
    printf("-> 3 Raamatute otsimine\n");
    printf("-> 4 Lahku programmist\n");
    do {
        if (fgets(b, sizeof b, stdin)) {
            char* newline = strchr(b, '\n');
            if (newline) {
                *newline = 0;
            }
        }
        tegevus = atoi(b);
        if (tegevus > 0 && tegevus < 5)
        {
            char* tegevusstr = "";
            if (tegevus == 1) {
                tegevusstr = "raamatute kuvamine";
            }
            else if (tegevus == 2) {
                tegevusstr = "raamatute lisamine";
            }
            else if (tegevus == 3) {
                tegevusstr = "raamatute otsimine";
            }
            else if (tegevus == 4) {
                tegevusstr = "lahkumine programmist";
            }
            printf("\n----- Valisite tegevuse %s -----\n", tegevusstr);
        }
        else {
            printf("Te ei valinud tegevust! \n");
            exit(0);
        }
    } while (tegevus < 0 || tegevus > 4);

    if (tegevus == 1) {
        kuvamine(con, res, row, tegevus);
    }
    else if (tegevus == 2) {
        lisamine_valik(con, res, row);
    }
    else if (tegevus == 3) {
        otsimine(con, res, row, tegevus);
    }
    else if (tegevus == 4) {
        mysql_close(con);
        exit(0);
    }

}

void kuvamine(MYSQL* con, MYSQL_RES* res, MYSQL_ROW row, int tegevus) {
    if (mysql_query(con, "SELECT raamatud.nimi, autorid.nimi FROM raamatud JOIN raamatud_has_autorid ON raamatud.id = raamatud_has_autorid.raamatud_id JOIN autorid ON autorid.id = raamatud_has_autorid.autorid_id")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(2);
    }
    res = mysql_use_result(con);

    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%s ----- %s\n", row[0], row[1]);
    }
    mysql_free_result(res);
    valimine(con, res, row, tegevus);

}

void otsimine(MYSQL* con, MYSQL_RES* res, MYSQL_ROW row, int tegevus) {
    char vastus[100];
    char a[500];

    printf("Sisestage raamatu nimi:\n");
    if (fgets(vastus, sizeof vastus, stdin)) {
        char* newline = strchr(vastus, '\n');
        if (newline) {
            *newline = 0;
        }
    }

    sprintf(a, "SELECT raamatud.nimi, autorid.nimi FROM raamatud JOIN raamatud_has_autorid ON raamatud.id = raamatud_has_autorid.raamatud_id JOIN autorid ON autorid.id = raamatud_has_autorid.autorid_id WHERE raamatud.nimi like '%%%s%%'", vastus);
    if (mysql_query(con, a)) {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }
    res = mysql_use_result(con);
    printf("Leitud vasted: \n");
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%s --- %s\n", row[0], row[1]);
    }
    mysql_free_result(res);
    valimine(con, res, row, tegevus);
}

void lisamine_valik(MYSQL* con, MYSQL_RES* res, MYSQL_ROW row) {
    //char raamat_nimi[100];
    //char autor[100];
    //int raamat_id;
    //int autor_id;
    //char kohaviit[20];
    //int kohaviit_id;
    //int koopia_id;
    //char aasta[5];
    //int laenutatud_id;
    //char triipkood[20];
    //char keel[20];
    //char sanr[20];
    //int sanr_id;
    char n[2];
    int tegevus;
    printf("Mida soovite lisada? (Valige tegevusele vastav number)\n");
    printf("-> 1 Raamat\n");
    printf("-> 2 Autor\n");
    printf("-> 3 Zanr\n");
    printf("-> 4 Raamatule autor\n");
    printf("-> 5 Raamatule zanr\n");
    printf("-> 6 Kohaviit\n");
    printf("-> 7 Koopia\n");
    printf("-> 8 Raamatule kohaviit\n");

    do {
        if (fgets(n, sizeof n, stdin)) {
            char* newline = strchr(n, '\n');
            if (newline) {
                *newline = 0;
            }
        }
        tegevus = atoi(n);
        if (tegevus > 0 && tegevus < 9)
        {
            char* tegevusstr = "";
            if (tegevus == 1) {
                tegevusstr = "raamatu";
            }
            else if (tegevus == 2) {
                tegevusstr = "autori";
            }
            else if (tegevus == 3) {
                tegevusstr = "zanri";
            }
            else if (tegevus == 4) {
                tegevusstr = "raamatule autori";
            }
            else if (tegevus == 5) {
                tegevusstr = "raamatule zanri";
            }
            else if (tegevus == 6) {
                tegevusstr = "kohaviida";
            }
            else if (tegevus == 7) {
                tegevusstr = "koopia";
            }
            else if (tegevus == 8) {
                tegevusstr = "raamatule kohaviida";
            }
            printf("\n----- Valisite tegevuse %s lisamine -----\n", tegevusstr);
        }
        else {
            printf("Te ei valinud tegevust! \n");
            exit(0);
        }
    } while (tegevus < 0 || tegevus > 8);
    if (tegevus == 1) {
        raamatu_lisa(con, res, row);
    }
}

void raamatu_lisa(MYSQL* con, MYSQL_RES* res, MYSQL_ROW row) {
    char raamat_nimi[100];
    int raamat_id;
    *raamat_nimi = raamatu_nimi();
    raamat_id = raamatu_id();
    char l[200];
    sprintf(l, "INSERT INTO raamatud (id, nimi) VALUES ('%d', '%s')", raamat_id, raamat_nimi);
    if (mysql_query(con, l)) {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }
    lisamine_valik(con, res, row);
}

char raamatu_nimi() {
    char raamat_nimi[100];
    printf("Sisesta raamatu nimi:\n");
    if (fgets(raamat_nimi, sizeof raamat_nimi, stdin)) {
        char* newline = strchr(raamat_nimi, '\n');
        if (newline) {
            *newline = 0;
        }
    }
    //return *raamat_nimi;
}

int raamatu_id() {
    char a[10];
    int raamat_id;
    printf("Sisesta raamatu id:\n");
    if (fgets(a, sizeof a, stdin)) {
        char* newline = strchr(a, '\n');
        if (newline) {
            *newline = 0;
        }
    }
    raamat_id = atoi(a);
    return raamat_id;
}



/*char autori_nimi(char* autor) {
    printf("Sisesta autori nimi:\n");
    if (fgets(autor, sizeof autor, stdin)) {
        char* newline = strchr(autor, '\n');
        if (newline) {
            *newline = 0;
        }
    }
}

int autori_id(int autor_id) {
    char a[10];
    printf("Sisesta autori id:\n");
    if (fgets(a, sizeof a, stdin)) {
        char* newline = strchr(a, '\n');
        if (newline) {
            *newline = 0;
        }
    }
    autor_id = atoi(a);
    return autor_id;
}

char fkohaviit(char* kohaviit) {
    printf("Sisesta kohaviit:\n");
    if (fgets(kohaviit, sizeof kohaviit, stdin)) {
        char* newline = strchr(kohaviit, '\n');
        if (newline) {
            *newline = 0;
        }
    }
}

int fkohaviida_id(int kohaviit_id) {
    char a[20];
    printf("Sisesta kohaviida id:\n");
    if (fgets(a, sizeof a, stdin)) {
        char* newline = strchr(a, '\n');
        if (newline) {
            *newline = 0;
        }
    }
    kohaviit_id = atoi(a);
    return kohaviit_id;
}

int fkoopia_id(int koopia_id) {
    char a[10];
    printf("Sisesta koopia id:\n");
    if (fgets(a, sizeof a, stdin)) {
        char* newline = strchr(a, '\n');
        if (newline) {
            *newline = 0;
        }
    }
    koopia_id = atoi(a);
    return koopia_id;
}

char faasta(char* aasta) {
    printf("Sisesta aasta:\n");
    if (fgets(aasta, sizeof aasta, stdin)) {
        char* newline = strchr(aasta, '\n');
        if (newline) {
            *newline = 0;
        }
    }
}

int flaenutatud_id(int laenutatud_id) {
    char a[10];
    printf("Sisesta laenutatud id:\n");
    if (fgets(a, sizeof a, stdin)) {
        char* newline = strchr(a, '\n');
        if (newline) {
            *newline = 0;
        }
    }
    laenutatud_id = atoi(a);
    return laenutatud_id;
}

char ftriipkood(char* triipkood) {
    printf("Sisesta triipkood:\n");
    if (fgets(triipkood, sizeof triipkood, stdin)) {
        char* newline = strchr(triipkood, '\n');
        if (newline) {
            *newline = 0;
        }
    }
}

char fkeel(char* keel) {
    printf("Sisesta keel:\n");
    if (fgets(keel, sizeof keel, stdin)) {
        char* newline = strchr(keel, '\n');
        if (newline) {
            *newline = 0;
        }
    }
}

char fsanr(char* sanr) {
    printf("Sisesta žanr:\n");
    if (fgets(sanr, sizeof sanr, stdin)) {
        char* newline = strchr(sanr, '\n');
        if (newline) {
            *newline = 0;
        }
    }
}

int fsanr_id(int sanr_id) {
    char a[10];
    printf("Sisesta žanri id:\n");
    if (fgets(a, sizeof a, stdin)) {
        char* newline = strchr(a, '\n');
        if (newline) {
            *newline = 0;
        }
    }
    sanr_id = atoi(a);
    return sanr_id;
}*/
