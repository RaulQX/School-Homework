#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct phone
{
    char repair_type[30];
    char imei[15];
    int price;
    int investment;
    int profit;
    unsigned int blacklisted : 1;

} phone;

enum {exitto, look_alls, look_specific_imei, look_black, add_entry, delete_entry, mark_unmarkk, tot_prof, tot_influx};

void print_menu()
{
    printf("What would you like to do?\n");

    printf("0 - Exit\n");
    printf("1 - Look up all entries\n");
    printf("2 - Look up all entries of one specific IMEI\n");
    printf("3 - Look up all blacklisted phones\n");
    printf("4 - Add an entry\n");
    printf("5 - Delete an entry\n");
    printf("6 - Mark/Unmark an entry as blacklisted\n");
    printf("7 - See total profit\n");
    printf("8 - See total influx\n");

}

int menu ()
{
    int key=1;

    print_menu();
    scanf("%d", &key);

    return key;
}

void print_phone(phone x, int n)
{
    char str_format_helper[35];
    int len;

    memset(str_format_helper,0,35);

    sprintf(str_format_helper, "%d", n);
    len=strlen(str_format_helper);

    for (int i = len; i<4; i++)
        str_format_helper[i]=' ';

    printf("|%s", str_format_helper);


    memset(str_format_helper,0,35);

    sprintf(str_format_helper, "%s", x.repair_type);
    len=strlen(str_format_helper);

    for (int i = len; i<31; i++)
        str_format_helper[i]=' ';
    printf("|%s", str_format_helper);



    memset(str_format_helper,0,35);

    sprintf(str_format_helper, "%s", x.imei);
    len=strlen(str_format_helper);

    for (int i = len; i<16; i++)
        str_format_helper[i]=' ';
    printf("|%s", str_format_helper);



    memset(str_format_helper,0,35);

    sprintf(str_format_helper, "%d", x.price);
    len=strlen(str_format_helper);

    for (int i = len; i<11; i++)
        str_format_helper[i]=' ';
    printf("|%s", str_format_helper);



    memset(str_format_helper,0,35);

    sprintf(str_format_helper, "%d", x.investment);
    len=strlen(str_format_helper);

    for (int i = len; i<14; i++)
        str_format_helper[i]=' ';
    printf("|%s", str_format_helper);



    memset(str_format_helper,0,35);

    sprintf(str_format_helper, "%d", x.profit);
    len=strlen(str_format_helper);

    for (int i = len; i<11; i++)
        str_format_helper[i]=' ';

    printf("|%s", str_format_helper);

    if (x.blacklisted == 1)
        printf("|Yes\n");
    else
        printf("|No\n");

    //printf("________________________________________________________________________________________________\n");
}

void print_header ()
{
    printf("|i   |Repair type                    |IMEI            |Price      |Investment    |Profit     |BL\n");
    //printf("________________________________________________________________________________________________\n");
}

int look_all(FILE *fp)
{
    phone curr;
    int i=0;

    print_header();

    while (!feof(fp))
    {
        fread(&curr, sizeof(phone), 1, fp);
        if (!feof(fp))
            print_phone(curr, i++);
    }

    fseek(fp,0,SEEK_SET);

    return i-1;
}

void all_imei(char* imei, FILE *fp)
{
    phone curr;
    int i=0;

    print_header();
    
    while (!feof(fp))
    {
        fread(&curr, sizeof(phone),1,fp);
        if (!feof(fp))
            if (strcmp(curr.imei, imei)==0)
                print_phone(curr, i++);
    }
}


void all_blacklst(FILE *fp)
{
    phone curr;
    int i=0;

    print_header();

    while (!feof(fp))
    {
        fread(&curr, sizeof(phone),1,fp);
        if (!feof(fp))
            if (curr.blacklisted)
                print_phone(curr, i++);
    }
}


void add_entr(FILE *fp)
{
    phone new_entry;

    printf("Please introduce the repair type:\n");
    getchar();
    fgets(new_entry.repair_type,30,stdin);

    int len = strlen(new_entry.repair_type);
    new_entry.repair_type[len-1] = 0;

    printf("Please introduce the imei\n");
    scanf("%30s", new_entry.imei);

    printf("Please introduce the price\n");
    scanf("%d", &new_entry.price);

    printf("Please introduce the investment\n");
    scanf("%d", &new_entry.investment);

    new_entry.profit = new_entry.price - new_entry.investment;

    new_entry.blacklisted=0; //One wouldn't repair/change a phone that's known to be blacklisted.

    fseek(fp, 0, SEEK_END); //Write at the end of the file
    fwrite(&new_entry, sizeof(phone), 1, fp);

}


void delete_entr(FILE *fp, char *name)
{
    int position_to_delete;

    int n = look_all(fp);
    printf("What position would you like to delete?\n");
    scanf("%d", &position_to_delete);

    phone curr;

    FILE *tmp = fopen ("tmp.bdb", "wb");
    if (!tmp)
    {
        printf("Couldn't open additional file\n");
        exit(2);
    }

    if (position_to_delete <= n)
        for (int i = 0; i <= n; i++)
        {
            fread(&curr, sizeof(phone), 1, fp);
            if (i != position_to_delete)
                fwrite(&curr, sizeof(phone), 1, tmp);
        }
    else
        printf("Not enough entries\n");

    fclose(fp);
    fclose(tmp);

    remove(name);
    rename("tmp.bdb", name);
}

void mark_unmark(FILE *fp, char *imei_searched)
{
    phone old;

    int found = 0;
    long position;

    while (!feof(fp))
    {
        position = ftell(fp);

        fread(&old, sizeof(phone),1,fp);

        if (!feof(fp))
            if (strcmp(old.imei, imei_searched) == 0)
            {
                found = 1;
                if (old.blacklisted == 1)
                    old.blacklisted = 0;
                else
                    old.blacklisted = 1;

                fseek(fp, position, SEEK_SET);
                fwrite(&old, sizeof(phone),1,fp);
            }
    }

    if (!found)
        printf("Couldn't find a phone with that IMEI\n");
}

void total_profit(FILE *fp)
{
    phone temp;

    int sum = 0;

    while (!feof(fp))
    {
        fread(&temp, sizeof(phone), 1, fp);
        if (!feof(fp))
            sum+=temp.profit;
    }

    printf("Total profit: %d\n", sum);
}

void total_influx(FILE *fp)
{
    phone temp;

    int sum = 0;

    while (!feof(fp))
    {
        fread(&temp, sizeof(phone), 1, fp);
        if (!feof(fp))
            sum+=temp.price;
    }

    printf("Total influx: %d\n", sum);
}

int main(int argc, char**argv)
{
    int new_dtb=0;
    char new_dtb_name[100];

    if (argc < 2)
    {
        printf("Would you like to create a new database?\n");
        printf("1 - yes\n2 - no\n");

        scanf("%d", &new_dtb);
        if (new_dtb == 1)
        {
            printf("What would you like it to be called?\n");
            scanf("%100s", new_dtb_name);
        }
        else
        {
            printf("Then please introduce the name of the database as command line argument\n");
            exit(1);
        }
    }

    FILE *fp = NULL;

    if (new_dtb == 1)
        fp = fopen (new_dtb_name, "wb+");
    else
        fp = fopen (argv[1], "rb+");

    int current_menu;
    char imei_searched[15];
    int check_again;

    do
    {
        current_menu = menu();

        fseek(fp, 0, SEEK_SET);

        switch (current_menu)
        {
        case look_alls:
            look_all(fp);
            break;

        case look_specific_imei:

            printf("Please insert the IMEI you are looking for:\n");
            scanf("%15s", imei_searched);
            all_imei(imei_searched, fp);

            break;

        case look_black:
            all_blacklst(fp);
            break;

        case add_entry:
            add_entr(fp);
            break;

        case delete_entry:
            delete_entr(fp, argv[1]);
            fp = fopen(argv[1], "rb+");
            break;

        case mark_unmarkk:

            printf("Would you like to see all the phones?\n");
            printf("1 - yes\n2 - no\n");
            scanf("%d", &check_again);

            if (check_again==1)
                look_all(fp);

            printf("What IMEI would you like to blacklist/whitelist?\n");
            scanf("%15s", imei_searched);

            mark_unmark(fp,imei_searched);
            break;

        case tot_prof:
            total_profit(fp);
            break;

        case tot_influx:
            total_influx(fp);
            break;

        default:
            break;
        }

    }while(current_menu);

    fclose(fp);

    return 0;
}
