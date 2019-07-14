#include <stdio.h>

#include <stdlib.h>

int main()

{

    char tempstr[10];

    int user, cpu = 0, i, j, usermv, cpumv, dmgmul;

    char moves[14][20] = {/*0*/ "tackle", /*1*/ "scratch", /*2*/ "ember", /*3*/ "water gun", /*4*/ "vine whip", /*5*/ "growl", /*6*/ "tail whip", /*7*/ "sand tomb", /*8*/ "thundershock", /*9*/ "hydro pump", /*10*/ "fire blast", /*11*/ "solar beam", /*12*/ "thunder", /*13*/ "earthquake"};

    char atktyp[14] = {'n', 'n', 'f', 'w', 'g', 'n', 'n', 'G', 'e', 'w', 'f', 'g', 'e', 'G'};

    int atkpwr[14] = {30, 40, 40, 40, 40, 0, 0, 40, 40, 80, 80, 80, 80, 80};

    int atkpp[14] = {10, 10, 6, 6, 6, 4, 4, 6, 6, 3, 3, 3, 3, 3};

    int atkppuser[14] = {10, 10, 6, 6, 6, 4, 4, 6, 6, 3, 3, 3, 3, 3};

    int atkppcpu[14] = {10, 10, 6, 6, 6, 4, 4, 6, 6, 3, 3, 3, 3, 3};

    struct pokemon
    {

        char name[20];

        int atk;

        int def;

        int spd;

        int hp;

        int moveset[4];

        char typ;
    };

    struct pokemon p[5] = {{"pikachu", 11, 8, 11, 100, {0, 6, 8, 12}, 'e'}, {"sandshrew", 10, 12, 8, 100, {1, 5, 7, 13}, 'G'}, {"bulbasaur", 11, 9, 10, 100, {0, 4, 5, 11}, 'g'}, {"charmander", 13, 8, 9, 100, {1, 2, 5, 10}, 'f'}, {"squirtle", 10, 13, 7, 100, {0, 3, 6, 9}, 'w'}};

    printf("1.pikachu\n2.sandshrew\n3.bulbasaur\n4.charmander\n5.squirtle\n");

    printf("choose your pokemon: ");

    scanf("%d", &user);

    user = user - 1;

    srand(time(NULL));

    while (cpu == user)

    {
        cpu = rand() % 5;
    }

    system("cls");

    printf("you chose %s\n\n", p[user].name);

    printf("cpu chose %s\n\n", p[cpu].name);

    printf("press enter to continue...........");

    fflush(stdin);

    gets(tempstr);

    system("cls");

    for (;;)

    {

        printf("%s\nHP: %d\n", p[cpu].name, p[cpu].hp);

        for (i = 0; i < (p[cpu].hp) / 2; i++)

            printf("%c", 177);

        printf("\n\n");

        printf("%s\nHP: %d\n", p[user].name, p[user].hp);

        for (i = 0; i < (p[user].hp) / 2; i++)

            printf("%c", 177);

        printf("\n");

        for (i = 0; i < 4; i++)

        {

            printf("%d: %d/%d ", i + 1, atkppuser[p[user].moveset[i]], atkpp[p[user].moveset[i]]);

            puts(moves[p[user].moveset[i]]);
        }

        scanf("%d", &usermv);

        while (usermv > 4 || usermv < 1)

        {

            printf("invalid input try again\n");

            scanf("%d", &usermv);
        }

        while (atkppuser[p[user].moveset[usermv - 1]] == 0)

        {

            if (atkppuser[p[user].moveset[usermv - 1]] == 0)

                printf("no pp left. try again\n");

            scanf("%d", &usermv);
        }

        usermv = usermv - 1;

        cpumv = rand() % 4;

        while (atkppcpu[p[cpu].moveset[cpumv]] == 0)

        {

            cpumv = rand() % 4;
        }

        system("cls");

        if (chkspd(p[user].spd, p[cpu].spd) == 1)

        {

            printf("\n\n%s used ", p[user].name);

            puts(moves[p[user].moveset[usermv]]);

            atkppuser[p[user].moveset[usermv]]--;

            dmgmul = calcdmgmul(p[cpu].typ, atktyp[p[user].moveset[usermv]]);

            p[cpu].hp = p[cpu].hp - (dmgmul * atkpwr[p[user].moveset[usermv]]) / 10 - (((dmgmul * atkpwr[p[user].moveset[usermv]]) / 10) * (p[user].atk - 10)) / 5 + (((dmgmul * atkpwr[p[user].moveset[usermv]]) / 10) * (p[cpu].def - 10)) / 5;

            if (p[user].moveset[usermv] == 5)

                p[cpu].atk--;

            if (p[user].moveset[usermv] == 6)

                p[cpu].def--;

            if (p[cpu].hp <= 0)

            {
                printf("\n\n%s fainted\n\nYou win\n\n", p[cpu].name);

                break;
            }

            printf("\n\n%s used ", p[cpu].name);

            puts(moves[p[cpu].moveset[cpumv]]);

            atkppcpu[p[cpu].moveset[cpumv]]--;

            dmgmul = calcdmgmul(p[user].typ, atktyp[p[cpu].moveset[cpumv]]);

            p[user].hp = p[user].hp - (dmgmul * atkpwr[p[cpu].moveset[cpumv]]) / 10 - (((dmgmul * atkpwr[p[cpu].moveset[cpumv]]) / 10) * (p[cpu].atk - 10)) / 5 + (((dmgmul * atkpwr[p[cpu].moveset[cpumv]]) / 10) * (p[user].def - 10)) / 5;

            if (p[cpu].moveset[cpumv] == 5)

                p[user].atk--;

            if (p[cpu].moveset[cpumv] == 6)

                p[user].def--;

            printf("\n\n");
        }

        else

        {

            printf("\n\n%s used ", p[cpu].name);

            puts(moves[p[cpu].moveset[cpumv]]);

            atkppcpu[p[cpu].moveset[cpumv]]--;

            dmgmul = calcdmgmul(p[user].typ, atktyp[p[cpu].moveset[cpumv]]);
           p[user].hp = p[user].hp - (dmgmul*atkpwr[p[cpu].moveset[cpumv]])/10 - (((dmgmul*atkpuser].name);

           break;
        }

        printf("\n\n%s used ", p[user].name);

        puts(moves[p[user].moveset[usermv]]);

        atkppuser[p[user].moveset[usermv]]--;

        dmgmul = calcdmgmul(p[cpu].typ, atktyp[p[user].moveset[usermv]]);

        p[cpu].hp = p[cpu].hp - (dmgmul * atkpwr[p[user].moveset[usermv]]) / 10 - (((dmgmul * atkpwr[p[user].moveset[usermv]]) / 10) * (p[user].atk - 10)) / 5 + (((dmgmul * atkpwr[p[user].moveset[usermv]]) / 10) * (p[cpu].def - 10)) / 5;

        if (p[user].moveset[usermv] == 5)

            p[cpu].atk--;

        if (p[user].moveset[usermv] == 6)

            p[cpu].def--;

        printf("\n\n");
    }

    if (p[user].hp <= 0)

    {
        printf("%s fainted\nYou lose", p[user].name);

        break;
    }

    if (p[cpu].hp <= 0)

    {
        printf("%s fainted\nYou win", p[cpu].name);

        break;

    } /*printf("press enter to continue.......");

       fflush(stdin);

       gets(tempstr);

       */
}

return 0;
}

int chkspd(int userspd, int cpuspd)

{

    srand(time(NULL));

    if (userspd > cpuspd)

        return 1;

    if (cpuspd > userspd)

        return 2;
}

int calcdmgmul(int pktyp, int atktyp)

{

    switch (pktyp)

    {

    case 101:

        switch (atktyp)

        {

        case 101:

            return 1;

            break;

        case 71:

            return 3;

            break;

        case 103:

            return 2;

            break;

        case 102:

            return 2;

            break;

        case 119:

            return 2;

            break;

        case 110:

            return 2;

            break;
        }

        break;

    case 71:

        switch (atktyp)

        {

        case 101:

            return 1;

            break;

        case 71:

            return 2;

            break;

        case 103:

            return 3;

            break;

        case 102:

            return 1;

            break;

        case 119:

            return 3;

            break;

        case 110:

            return 2;

            break;
        }

        break;

    case 103:

        switch (atktyp)

        {

        case 101:

            return 2;

            break;

        case 71:

            return 2;

            break;

        case 103:

            return 1;

            break;

        case 102:

            return 3;

            break;

        case 119:

            return 2;

            break;

        case 110:

            return 2;

            break;
        }

        break;

    case 102:

        switch (atktyp)

        {

        case 101:

            return 2;

            break;

        case 71:

            return 3;

            break;

        case 103:

            return 1;

            break;

        case 102:

            return 1;

            break;

        case 119:

            return 3;

            break;

        case 110:

            return 2;

            break;
        }

        break;

    case 119:

        switch (atktyp)

        {

        case 101:

            return 3;

            break;

        case 71:

            return 2;

            break;

        case 103:

            return 3;

            break;

        case 102:

            return 1;

            break;

        case 119:

            return 1;

            break;

        case 110:

            return 2;

            break;
        }

        break;
    }
}
