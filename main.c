#include <stdio.h>

int provjeriZatvoreneKvadrate(
    int vrsta, int stupac, char smjer,
    int REDOVI, int KOLONE,
    int horizontalne_crte[6][5],
    int vertikalne_crte[5][6],
    char kvadratici[5][5],
    int trenutniIgrac)
{

    int zatvoreni = 0;

    if (smjer == 'h')
    {
        if (vrsta > 0)
        {
            int r = vrsta - 1;
            int k = stupac;

            if (horizontalne_crte[r][k] &&
                vertikalne_crte[r][k] &&
                vertikalne_crte[r][k + 1] &&
                horizontalne_crte[vrsta][stupac])
            {
                if (kvadratici[r][k] == ' ')
                {
                    kvadratici[r][k] = (trenutniIgrac == 1) ? 'X' : 'O';
                    zatvoreni++;
                }
            }
        }

        // Kvadrat ispod
        if (vrsta < REDOVI - 1)
        {
            int r = vrsta;
            int k = stupac;

            if (horizontalne_crte[vrsta][stupac] &&
                vertikalne_crte[r][k] &&
                vertikalne_crte[r][k + 1] &&
                horizontalne_crte[r + 1][k])
            {
                if (kvadratici[r][k] == ' ')
                {
                    kvadratici[r][k] = (trenutniIgrac == 1) ? 'X' : 'O';
                    zatvoreni++;
                }
            }
        }
    }
    else if (smjer == 'v')
    {
        // Kvadrat lijevo
        if (stupac > 0)
        {
            int r = vrsta;
            int k = stupac - 1;

            if (vertikalne_crte[r][k] &&
                horizontalne_crte[r][k] &&
                horizontalne_crte[r + 1][k] &&
                vertikalne_crte[r][stupac])
            {
                if (kvadratici[r][k] == ' ')
                {
                    kvadratici[r][k] = (trenutniIgrac == 1) ? 'X' : 'O';
                    zatvoreni++;
                }
            }
        }

        // Kvadrat desno
        if (stupac < KOLONE - 1)
        {
            int r = vrsta;
            int k = stupac;

            if (vertikalne_crte[r][stupac] &&
                horizontalne_crte[r][k] &&
                horizontalne_crte[r + 1][k] &&
                vertikalne_crte[r][k + 1])
            {
                if (kvadratici[r][k] == ' ')
                {
                    kvadratici[r][k] = (trenutniIgrac == 1) ? 'X' : 'O';
                    zatvoreni++;
                }
            }
        }
    }

    return zatvoreni;
}


void ispisiMrezu(int REDOVI, int KOLONE,
                 int horizontalne_crte[][5], int vertikalne_crte[][6],
                 char kvadratici[][5])
{
    // Printa red brojeva na vrhu ploče (0 do KOLONE tj. 0 do 5)
    printf("    ");
    for (int j = 0; j <= KOLONE; j++)
        printf(" %2d ", j);
    printf("\n");

    for (int i = 0; i <= REDOVI * 2; i++)
    {
        if (i % 2 == 0)
            printf(" %2d ", i / 2);
        else
            printf("    ");

        for (int j = 0; j <= KOLONE * 2; j++)
        {
            if (i % 2 == 0 && j % 2 == 0)
            {
                printf(".");
            }
            else if (i % 2 == 0 && j % 2 == 1)
            {
                int red = i / 2;
                int kol = j / 2;
                if (kol < KOLONE && horizontalne_crte[red][kol] == 1)
                    printf(" \033[34m●\033[0m ");
                else if (kol < KOLONE && horizontalne_crte[red][kol] == 2)
                    printf(" \033[31m●\033[0m ");
                else
                    printf("   ");
            }
            else if (i % 2 == 1 && j % 2 == 0)
            {
                int red = i / 2;
                int kol = j / 2;
                if (red < REDOVI && vertikalne_crte[red][kol] == 1)
                    printf("\033[34m●\033[0m");
                else if (red < REDOVI && vertikalne_crte[red][kol] == 2)
                    printf("\033[31m●\033[0m");
                else
                    printf(" ");
            }
            else
            {
                int red = i / 2;
                int kol = j / 2;
                if (red < REDOVI && kol < KOLONE && kvadratici[red][kol] != ' ')
                    printf(" %c ", kvadratici[red][kol]);
                else
                    printf("   ");
            }
        }
        // Printa red brojeva na kraju svakog reda (0 do REDOVI tj. 0 do 5)
        if (i % 2 == 0)
            printf(" %2d", i / 2);
        printf("\n");
    }
    // Printa red brojeva na dnu ploče (0 do KOLONE tj. 0 do 5)
    printf("    ");
    for (int j = 0; j <= KOLONE; j++)
        printf(" %2d ", j);
    printf("\n");
}

int main()
{
    int izbor;

    printf("\t\tKvadratići\n");

    printf("\nPravila igre\n\n\n");
    printf("1. Igraju 2 i samo 2 igrača.\n");
    printf("2.Nacrtana je mreža točkica u pravokutnom obliku.\n");
    printf("3. Igrači naizmjence crtaju jednu crtu između dvije susjedne točkice — crta može biti horizontalna ili vertikalna.\n");
    printf("4. Kvadrat je zatvoren kada su nacrtane sve četiri njegove strane.\n");
    printf("5. Igrač koji zatvori kvadrat upisuje svoj znak unutar kvadrata i dobiva dodatni potez.\n");
    printf("6. Igra završava kada su sve crte nacrtane i svi kvadratići zatvoreni.\n");
    printf("7. Pobjednik je igrač s najviše zatvorenih kvadrata.\n");
    printf("8. Igra nije samo u osvajanju kvadrata, nego u umijeću predviđanja protivnikovih poteza — jer prava pobjeda pripada onome tko vlada mrežom i umom!\n");

    printf("\nŽelite li započeti igru? (1 = da, 0 = ne): ");
    scanf("%d", &izbor);

    if (izbor == 1)
    {
        printf("\nIgra započela!\n");

        int REDOVI = 5;
        int KOLONE = 5;

        int horizontalne_crte[6][5];
        int vertikalne_crte[5][6];
        char kvadratici[5][5];

        for (int i = 0; i < REDOVI + 1; i++)
            for (int j = 0; j < KOLONE; j++)
                horizontalne_crte[i][j] = 0;

        for (int i = 0; i < REDOVI; i++)
            for (int j = 0; j < KOLONE + 1; j++)
                vertikalne_crte[i][j] = 0;

        for (int i = 0; i < REDOVI; i++)
            for (int j = 0; j < KOLONE; j++)
                kvadratici[i][j] = ' ';

        int igraGotova = 0;
        int trenutniIgrac = 1; // 1 = X, 2 = O

        int bodoviIgrac1 = 0;
        int bodoviIgrac2 = 0;

        while (!igraGotova)
        {
            ispisiMrezu(REDOVI, KOLONE, horizontalne_crte, vertikalne_crte, kvadratici);

            printf("\nNa potezu je igrač %d (%c)\n", trenutniIgrac, (trenutniIgrac == 1 ? 'X' : 'O'));

            int vrsta, stupac;
            char smjer;

            printf("Unesite vrstu (0 - %d): ", REDOVI);
            scanf("%d", &vrsta);

            printf("Unesite stupac (0 - %d): ", KOLONE);
            scanf("%d", &stupac);

            printf("Unesite smjer (h = horizontalno, v = vertikalno): ");
            scanf(" %c", &smjer);

            int valjanPotez = 0;

            if (smjer == 'h' && vrsta >= 0 && vrsta <= REDOVI && stupac >= 0 && stupac < KOLONE)
            {
                if (horizontalne_crte[vrsta][stupac] == 0)
                {
                    horizontalne_crte[vrsta][stupac] = trenutniIgrac; // zabilježi broj igrača
                    valjanPotez = 1;
                }
                else
                {
                    printf("Ta horizontalna crta je već postavljena!\n");
                }
            }
            else if (smjer == 'v' && vrsta >= 0 && vrsta < REDOVI && stupac >= 0 && stupac <= KOLONE)
            {
                if (vertikalne_crte[vrsta][stupac] == 0)
                {
                    vertikalne_crte[vrsta][stupac] = trenutniIgrac; // zabilježi broj igrača
                    valjanPotez = 1;
                }
                else
                {
                    printf("Ta vertikalna crta je već postavljena!\n");
                }
            }
            else
            {
                printf("Neispravan unos poteza!\n");
            }

            if (valjanPotez)
            {
                int zatvoreniKvadrati = provjeriZatvoreneKvadrate(vrsta, stupac, smjer, REDOVI, KOLONE,
                                                                  horizontalne_crte, vertikalne_crte, kvadratici,
                                                                  trenutniIgrac);

                if (zatvoreniKvadrati > 0)
                {
                    printf("Igrač %d je zatvorio %d kvadrat(a)!\n", trenutniIgrac, zatvoreniKvadrati);

                    if (trenutniIgrac == 1)
                        bodoviIgrac1 += zatvoreniKvadrati;
                    else
                        bodoviIgrac2 += zatvoreniKvadrati;

                    // Igrač dobiva dodatni potez, ne mijenjamo trenutnog igrača
                }
                else
                {
                    // Promjena igrača
                    trenutniIgrac = (trenutniIgrac == 1) ? 2 : 1;
                }
            }

            // Provjera završetka igre (ako su sve crte nacrtane)
            int sveCrteNacrtane = 1;
            for (int i = 0; i < REDOVI + 1 && sveCrteNacrtane; i++)
                for (int j = 0; j < KOLONE && sveCrteNacrtane; j++)
                    if (horizontalne_crte[i][j] == 0)
                        sveCrteNacrtane = 0;

            for (int i = 0; i < REDOVI && sveCrteNacrtane; i++)
                for (int j = 0; j < KOLONE + 1 && sveCrteNacrtane; j++)
                    if (vertikalne_crte[i][j] == 0)
                        sveCrteNacrtane = 0;

            if (sveCrteNacrtane)
                igraGotova = 1;
        }

        printf("\nIgra je završena!\n");
        ispisiMrezu(REDOVI, KOLONE, horizontalne_crte, vertikalne_crte, kvadratici);

        printf("Rezultat:\nIgrač 1 (X): %d\nIgrač 2 (O): %d\n", bodoviIgrac1, bodoviIgrac2);

        if (bodoviIgrac1 > bodoviIgrac2)
            printf("Pobjednik je igrač 1 (X)!\n");
        else if (bodoviIgrac2 > bodoviIgrac1)
            printf("Pobjednik je igrač 2 (O)!\n");
        else
            printf("Neriješeno je!\n");
    }
    else
    {
        printf("Igra nije započela.\n");
    }

    return 0;
}
