#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dos.h>
#include <dir.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

int level_save , no_save = 0 , komaki = 1 , word_counter , level_choose , level_number = 0 , word_count , false_char = 0 , correct_char = 0 , k_switch = 0 , correct = 0 , tedad_level;
char word_user , level_num_global[20] ,  name_file[30];
float zaman1 = 0, zaman2 = 0 , zaman_kol , emtiaz_marhale = 0;
double emtiaz_kol , marhale_emtiaz , word_emtiaz , all_words_emtiaz;

void set_color (int color)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

struct info
{
    char user_name[20];
    double emtiaz;
    char shomare_lvl[20];
    int level;
};
struct info users;

struct node
{
    char word[100];
    struct node* next;
    struct node* pervious;
};
struct node* first;
struct node* starter;

void game()
{
    FILE *lvl;
    word_counter = 0;
    char get[50] , help_level[20];
    starter = (struct node*)malloc(sizeof(struct node));
    if(starter == NULL)
    {
        printf("We have an Error!");
        return -1;
    }
    first = starter;
    starter -> pervious = NULL;
    lvl = fopen(level_num_global , "r");
    if(lvl == NULL)
    {
        printf("cannot open the file");
        return -1;
    }
    fscanf(lvl , "%s" , get);
    while(1)
    {
        if(feof(lvl))
            break;
        struct node* helper;
        word_counter++;
        int i =0;
        while(i <= strlen(get))
        {
            starter->word[i] = get[i];
            i++;
        }
        starter -> next = (struct node*)malloc(sizeof(struct node));
        if((starter -> next) == NULL)
        {
            printf("We have an Error!");
            return -1;
        }
        helper = starter->next;
        helper -> pervious = starter;
        starter = helper;
        fscanf(lvl , "%s" , get);
    }
    word_count = word_counter;
    time_t t = time(NULL);
    srand(t);
    while(word_counter != 0)
    {
        int random = rand() % word_counter;
        starter = first;
        int i = 0;
        for(i = 0 ; i < random ; i++)
        {
            struct node* current;
            current = starter -> next;
            starter = current;
        }
        printf("%s\n" , (*starter).word);
        struct node *tmp1;
        struct node *tmp2;
        if((*starter).pervious == NULL)
        {
            tmp1 = (*starter).next;
            first = tmp1;
            (*first).pervious = NULL;
        }
        else
        {
            tmp2 = (*starter).pervious;
            tmp1 = (*starter).next;
            (*tmp2).next = tmp1;
            (*tmp1).pervious = tmp2;
        }
        word_counter--;
        clock_t start = clock();
        for(k_switch = 0 ; k_switch < strlen((*starter).word) ; k_switch++)
        {
            check_word();
            correct = 0;
        }
        clock_t finish = clock();
        zaman1 = (((float)(finish - start)) / CLOCKS_PER_SEC);
        zaman_kol = zaman1 - zaman2;

        word_emtiaz = ((3 * strlen((*starter).word)) - false_char) / zaman_kol;
        all_words_emtiaz += word_emtiaz;
        marhale_emtiaz = all_words_emtiaz / word_count;
        word_emtiaz = 0;
        zaman2 = 0;
        false_char = 0;
        correct_char = 0;

    }
    emtiaz_kol += marhale_emtiaz;
    level_save = level_choose;
    level_number++;
    set_color(5);
    system("cls");
    if(komaki == 0)
        return;
    level_save = level_choose;
    printf("NICE YOU HAVE FINISHED THIS LVL! ^.^\n");
    printf("your score in this lvl: %lf\n" , marhale_emtiaz);
    set_color(9);
    printf("Do you wanna play next lvl?\n");
    printf("[1] YES\n");
    printf("[2] Save & quit\n");
    printf("[3] Quit without save\n");
    char answer2 = getch();
    while(answer2 != '1' && answer2 != '2' && answer2 != '3')
    {
        set_color(4);
        printf("Wrong input please try again!:\n");
        answer2 = getch();
    }
    if(answer2 == '1')
    {
        char str1[20] , str2[30] = "level-x.txt" , str3[30] = "level-xx.txt";
        level_choose++;
        if(level_choose < 10)
        {
            sprintf(str1 , "%d" , level_choose);
            str2[6] = str1[0];
            strcpy(level_num_global , str2);

        }
        else
        {
            sprintf(str1 , "%d" , level_choose);
            str3[6] = str1[0];
            str3[7] = str1[1];
            strcpy(level_num_global , str3);
        }
        printf("%s" , level_num_global);
    }
    if(answer2 == '2')
    {
        save();
        level_choose = level_counter() + 1;
    }
    if(answer2 == '3')
    {
        level_choose = level_counter() + 1;
    }
    system("cls");
}

/*void delete_node(struct node ** avali , int random)
{
    if(*avali == NULL)
    {
        printf("sorry there is a problem");
        return;
    }
    if(random ==1)
    {
        struct node * tmp;
        tmp = *avali;
        *avali = (*avali) -> next;
        free(tmp);
    }
    else
    {
        struct node *tmp1;
        struct node *tmp2;
        int j = 2;
        tmp1 = *avali;
        for(j = 2 ; j < random ; j++)
            tmp1 = tmp1 -> next;

        tmp2struct info users; = tmp1 -> next;
        tmp1 -> next = tmp1 -> next -> next;
        free(tmp2);
    }
}*/

void check_word()
{
    while(correct == 0)
    {
        level_save = level_choose;
        set_color(10);
        word_user = getch();
        if(word_user == 81)
        {
            system("cls");
            set_color(11);
            printf("You wanna leave me! :-(\n");
            printf("Do you wanna save your Game?\n");
            printf("[1] YES\n");
            printf("[2] NO\n");
            char answer;
            answer = getch();
            set_color(10);
            level_save = level_choose;
            while(answer != '1' && answer != '2')
            {
                printf("Wrong input try again!\n");
                answer = getch();
            }
            if(answer == '1')
            {
                save();
                level_choose = level_counter() + 1;
                k_switch = strlen((*starter).word);
                word_counter = 0;
                komaki = 0;
                return;
            }
            else
            {
                level_choose = level_counter() + 1;
                k_switch = strlen((*starter).word);
                word_counter = 0;
                komaki = 0;
                return;
            }
        }
        if(word_user == (*starter).word[k_switch])
        {
            (*starter).word[k_switch] = ((int)((*starter).word[k_switch])) - 32;
            correct = 1;
            correct_char++;
        }
        else
        {
            if(word_user == 'P')
            {
                set_color(4);
                clock_t pause = clock();
                printf("GAME IS PAUSED\n");
                printf("press R to resume the game\n");
                char resume;
                resume = getch();
                while(resume != 'R')
                    resume = getch();
                if(resume = 'R')
                {
                    clock_t resume = clock();
                    zaman2 = ((float)(resume - pause)) / CLOCKS_PER_SEC;
                }
                set_color(10);
            }
            else
            {
                if(word_user == '`')
                {
                    set_color(4);
                    printf("Your score until now %lf" , marhale_emtiaz);
                    set_color(10);
                    getch();
                }
                else
                {
                    Beep(2000 , 200);
                    false_char++;
                }
            }

        }
        system("cls");
        printf("%s\n", (*starter).word);
        set_color(7);
    }
}

void open_level(char x , FILE * lvl)
{
    FILE * file;
    char name[20] = "level-1.txt" ;
    name[6] = x;
    file = fopen(name , "r");
    if(file == NULL)
    {
        printf("Cannot open the file");
        return;
    }
}

int level_counter()
{
    FILE * level;
    int i = 0 , j = 1;
    char str1[20] , str2[30] = "level-x.txt" , str3[30] = "level-xx.txt";
        while(level != NULL)
        {
            if(j < 10)
            {
                sprintf(str1 , "%d" , j);
                str2[6] = str1[0];
                level = fopen(str2 , "r");
                j++;

            }
            else
            {
                sprintf(str1 , "%d" , j);
                str3[6] = str1[0];
                str3[7] = str1[1];
                level = fopen(str3 , "r");
                j++;
            }
        }
        tedad_level = j - 2;
        return tedad_level;
}

void get_name_show_menu()
{
    FILE *information;
    char answer1 , str2[30] = "level-x.txt" , str3[30] = "level-xx.txt" , str1[30] ;
    set_color(10);
    scanf("%s" , users.user_name);
    strcpy(name_file , users.user_name);
    strcat(name_file , ".txt");
    information = fopen(name_file , "r");
    if(information == NULL)
    {
        information = fopen(name_file , "w");
        fprintf(information , "%s " , users.user_name);
        no_save = 1;

    }
    else
    {
        information = fopen(name_file , "r+");
    }
    system("cls");
    set_color(4);
    printf("Hi %s are u ready to play? ^.^ \n" , users.user_name);
    printf("[1] Play a new game\n");
    printf("[2] Resume an old game\n");
    answer1 = getch();
    while(answer1 != '1' && answer1 !='2')
    {
        printf("Please Enter the correct number!\n");
        answer1 = getch();
    }
    system("cls");
    if(answer1 == '1')
    {
        emtiaz_kol = users.emtiaz = 0;
        fprintf(information , "%s " , users.user_name);
        fprintf(information , "%lf " , users.emtiaz);
        set_color(11);
        printf("OK , let's start\n");
        printf("Please Enter the level (now , I have at most %d levels):\n" , level_counter());
        scanf("%d" , &level_choose);
        while(level_counter() < level_choose || level_choose == 0)
        {
            set_color(4);
            printf("You write a wrong lvl!!\n");
            set_color(11);
            printf("Please Enter the level again:\n");
            scanf("%d" , &level_choose);
        }
        if(level_choose < 10)
        {
            sprintf(str1 , "%d" , level_choose);
            str2[6] = str1[0];
            strcpy(level_num_global , str2);
        }
        else
        {
            sprintf(str1 , "%d" , level_choose);
            str3[6] = str1[0];
            str3[7] = str1[1];
            strcpy(level_num_global , str3);
        }
        strcpy(users.shomare_lvl , level_num_global);
        fprintf(information , "%s" , users.shomare_lvl);
    }
    if(answer1 == '2')
    {
        if(no_save == 1)
        {
            printf("You dont have any save game!\n");
            printf("tab any key to start a new game\n");
            getch();
            emtiaz_kol = users.emtiaz = 0;
            fprintf(information , "%s " , users.user_name);
            fprintf(information , "%lf " , users.emtiaz);
            system("cls");
            set_color(11);
            printf("OK , let's start\n");
            printf("Please Enter the level (now , I have at most %d levels):\n" , level_counter());
            scanf("%d" , &level_choose);
            while(level_counter() < level_choose)
            {
                set_color(4);
                printf("You write a wrong lvl!!\n");
                set_color(11);
                printf("Please Enter the level again:\n");
                scanf("%d" , &level_choose);
            }
            if(level_choose < 10)
            {
                sprintf(str1 , "%d" , level_choose);
                str2[6] = str1[0];
                strcpy(level_num_global , str2);
            }
            else
            {
                sprintf(str1 , "%d" , level_choose);
                str3[6] = str1[0];
                str3[7] = str1[1];
                strcpy(level_num_global , str3);
            }
            strcpy(users.shomare_lvl , level_num_global);
            fprintf(information , "%s" , users.shomare_lvl);
        }
        else
        {
            fscanf(information , "%s " , users.user_name);
            fscanf(information , "%lf " , &users.emtiaz);
            fscanf(information , "%s " , users.shomare_lvl);
            fscanf(information , "%d " , &users.level);
            strcpy(level_num_global , users.shomare_lvl);
            level_choose = users.level;
            printf("You were in level %d:\n" , level_choose);
            printf("Press any key to start!\n");
            getch();
        }
    }
    system("cls");
    fclose(information);
}

void save()
{
    FILE * information;
    printf("%lf" , emtiaz_kol);
    information = fopen(name_file , "w");
    if(information == NULL)
    {
        printf("Cannot open the file\n");
        return -1;
    }
    users.level = level_save;
    users.emtiaz = emtiaz_kol;
    strcpy(users.shomare_lvl , level_num_global);
    fprintf(information , "%s " , users.user_name );
    fprintf(information , "%lf " , users.emtiaz);
    fprintf(information , "%s " , users.shomare_lvl);
    fprintf(information , "%d " , users.level);
    fclose(information);
}

int main()
{
    system("color 31");
    //set_color(5);
    printf("Welcome to my words Game! :-) \n");
    printf("Please Enter your name below:\n");
    get_name_show_menu();
    while(level_choose <= level_counter())
    {
        game();
        set_color(4);
    }
    system("cls");
    printf("Its finished\n");
    set_color(15);
    printf("Hope to see u soon :-)");
    set_color(16);

    return 0;
}
