#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#define encrypt 10
#define MAX 500
#define Checker "E:\\checker.dbf"  // Change the drive letter
#define Location "BDFMainDatabase.dbf"
#define RegInfo "E:\\Registration.dbf"  // Change the drive letter

typedef struct data{
    char pincode[7];
    char accname[50];
    int accno;
    int indept;
}LIST;

LIST list[MAX];
int last;

char pin[7];
char name[50];
int num;
int amount;

COORD coord = {0,0};

void gotoxy(int x, int y){
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void createBlock(int x,int y, int len, char *label){
    int i;
    gotoxy(x,y);
    for(i = x; i < len; i++)
        printf("_");
    for(i = y + 1; i < y + 4; i++){
        gotoxy(x - 1,i);
        printf("|");
        gotoxy(len,i);
        printf("|");
    }
    gotoxy(x,y + 3);
    for(i = x; i < len; i++)
        printf("_");
    gotoxy(x+1, y + 2);
    printf("%s", label);
}

void createtext(int x, int y, char* text){
    gotoxy(x,y);
    printf("%s",text);
}

void clear(int x, int y,int len){
    len+=x;
    for(int i = x;i<len;i++){
        gotoxy(i,y);
        printf(" ");
    }
}

int isFull(){
    return (last == MAX-1);
}

void createBox(int x,int y, int len, int width){
    int i;
    width += y;
    len += x;
    gotoxy(x-1,y);
        printf("%c",201);
    for(i = x; i < len; i++)
        printf("%c",205);
        printf("%c",187);
    for(i = y+1; i<width; i++){
        gotoxy(x - 1,i);
        printf("%c",186);
        gotoxy(len,i);
        printf("%c",186);
    }
    gotoxy(x-1,width);
    printf("%c",200);
    for(i = x; i < len; i++)
        printf("%c",205);
        printf("%c",188);
}

void header(int x, int y){
    createBox(x-4,y-2,39,10);
    gotoxy(x,y);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB   \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    gotoxy(x,y+1);
    printf("\xDB\xDB     \xDB\xDB  \xDB\xDB     \xDB\xDB   \xDB\xDB\xDB");
    gotoxy(x,y+2);
    printf("\xDB\xDB     \xDB\xDB  \xDB\xDB      \xDB\xDB  \xDB\xDB\xDB");
    gotoxy(x,y+3);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB   \xDB\xDB      \xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    gotoxy(x,y+4);
    printf("\xDB\xDB     \xDB\xDB  \xDB\xDB      \xDB\xDB  \xDB\xDB\xDB");
    gotoxy(x,y+5);
    printf("\xDB\xDB     \xDB\xDB  \xDB\xDB     \xDB\xDB   \xDB\xDB\xDB");
    gotoxy(x,y+6);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB   \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB");
    gotoxy(x+7,y+8);
    printf("BANKO DE FELIPINAS");
}

void makenull(){
    last = -1;
}

int locate(char dupname[50]){
    for(int i=0;i<=last;i++)
        if(strcmp(list[i].accname,dupname)==0)
            return(i);
    return (-1);
}

void acctnogen(){
    srand(time(NULL));
    num =1000+(rand()%10000);
    char number[4];
    itoa(num,number,10);
    for(int i = 0; i<last;i++)
        if (num==list[i].accno)
            num =1000+(rand()%10000);
    for (int j=0,x=55;j<4;j++,x+=2){
        gotoxy(x,7);
        printf(" %c",number[j]);
        clear(30,22,60);
        createtext(57,22,"- - -");
    }
}

void pincode(){
    int i,x,error=0;
    do{
        for (i=0,x=42;i<6;i++,x+=2){
            gotoxy(x,16);
            pin[i]=getch()+encrypt;
            error += isdigit(pin[i]-encrypt);
            putchar('*');
            }
        pin[i]='\0';
    if (error<6){
           clear(30,22,60);
           createtext(33,22,"Pincode must be numbers only!! (ENTER to try again...)");
           getch();
           clear(42,16,36);
           error=0;
           clear(30,22,60);
           createtext(57,22,"- - -");
        }
    }while(error<6);
         clear(30,22,60);
         createtext(31,22,"Note: Please remember your pincode!! (ENTER to continue...)");
         getch();
         clear(30,22,60);
         createtext(34,22,"Don't share it with anybody!! (ENTER to continue...)");
         getch();
         clear(30,22,60);
         createtext(57,22,"- - -");
}


void displayUi(){
    int i;
    createBox(30,1,60,3);
    createtext(44,3,"R E G I S T R A T I O N  F O R M");
    createBox(30,4,60,4);
    createtext(47,6,"A C C O U N T  N U M B E R");
    createtext(57,22,"- - -");
    createBlock(30, 8, 90, "ENTER NAME:");
    createBlock(30, 11, 90, "ENTER DEPOSIT: Php");
    createBlock(30, 14, 90, "ENTER PIN:");
    createBlock(30, 17, 90, "PLEASE CONFIRM PIN:");
    createBlock(30, 20, 90, " ");
    createtext(39,22,"PRESS ANY KEY TO GENERATE ACCOUNT NUMBER...");
}




void insert (char accountname[50], char pcode[7], int acctno, int amnt){
        if (locate(accountname)==-1){
        last++;
        strcpy(list[last].accname,accountname);
        strcpy(list[last].pincode,pcode);
        list[last].accno = acctno;
        list[last].indept = amnt;
        }
    }

void insertcard(){
    FILE *fp;
    do {
        system("cls");
        fp = fopen(Checker,"w");
        if (fp==NULL){
            header(49,4);
            createBox(42,13,45,4);
            createtext(48,15,"I N S E R T    F L A S H D R I V E");
            createtext(41,18,"[");
            createtext(87,18,"]");
            gotoxy(43,18);
            for(int i=0;i<21;i++){
                printf("%c ",219);
                Sleep(90);
            }
            printf("%c",219);
            gotoxy(43,18);
            for(int i=0;i<21;i++){
                printf("  ");
                Sleep(90);
            }
        }
        else{
            header(49,4);
            createBox(42,13,45,4);
            gotoxy(46,15);
            clear(46,15,25);
            createtext(46,15,"F L A S H D R I V E   D E T E C T E D");
            createtext(41,18,"[");
            createtext(87,18,"]");
            gotoxy(43,18);
            for(int i=0;i<43;i++){
                printf("%c",219);
            }
            createtext(51,20,"PRESS ANY KEY TO CONTINUE...");
            fclose(fp);
            remove(Checker);
            getch();
        }
    } while (fp==NULL);
    fclose(fp);
}

void scanRegistered(){
    FILE *reg;
    reg = fopen(RegInfo,"r+");
    if (reg!=NULL){
        system("COLOR 7C");
        system("cls");
        createBox(17,17,101,4);
        createtext(30,19,"FLASHDRIVE REGISTERED, RUN 'PROJECT TRANSACTION.C'. Press [ENTER] to exit...");
        getch();
        gotoxy(27,25);
        exit(1);
    }
}

void retrieve(){
    FILE *fp;
    char accountname[50],pcode[7];
    int no, amt;
    fp = fopen(Location,"r+");
    if (fp==NULL){
        system("cls");
        createBox(35,13,67,3);
        createtext(41,15,"FILE NOT FOUND. PRESS ENTER TO CREATE MAIN DATABASE FILE");
        fp = fopen(Location,"w+");
        getch();
    }
    else{
        while(!feof(fp)){
            fscanf(fp,"%d %[^\t]%d %s",&no,accountname,&amt,pcode);
            insert(accountname,pcode,no,amt);
        }
        if(isFull()){
            system("COLOR 7C");
            system("cls");
            createBox(17,17,101,3);
            createtext(41,19,"ERROR : BANK DATABASE IS FULL. PRESS ANY KEY TO EXIT...");
            getch();
            gotoxy(27,25);
            exit(1);
        }

    }
    fclose(fp);
}

void save(){
    FILE *save;
    FILE *fp;
    save = fopen(RegInfo,"w");
    fp = fopen(Location, "w+");
    fprintf(save,"%d\t%s\n",num,pin);
    for (int i=0;i<=last;i++)
        fprintf(fp,"%d\t%s\t%d\t%s\n",list[i].accno,list[i].accname,list[i].indept,list[i].pincode);
    fprintf(fp,"%d\t%s\t%d\t%s\n",num,name,amount,pin);
    fclose(save);
    fclose(fp);
}

void nameUI(int y){
    createBox(42,y,45,6);
    createtext(53,y+2,"S U B M I T T E D   B Y:");
    createtext(56,y+3,"WILLIAM CRIS HOD");
    createtext(59,y+4,"BSCS - N2A");
    gotoxy(0,27);
}

void saveUI(){
int counter;
    system("cls");
        header(49,4);
        createBox(42,13,45,4);
        createtext(55,15,"S A V I N G   D A T A");
        createtext(41,18,"[");
        createtext(87,18,"]");
        for (counter=0;counter<3;counter++){
            gotoxy(43,18);
            for(int i=0;i<22;i++){
                printf("%c ",219);
                Sleep(90);
            }
            gotoxy(43,18);
            for(int i=0;i<22;i++){
                printf("  ");
                Sleep(90);
            }
        }
        clear(48,15,40);
        createBox(33,13,63,4);
        for(int i=14;i<16;i++)
            clear(40,i,50);
        for(int i=43;i<86;i++){
            gotoxy(i,18);
            printf("%c",219);
        }
    }

int main(){
    char confirmpin[6];
    int number[4];
    int i,x;
    system("COLOR 1F");
    insertcard();
    scanRegistered();
    makenull();
    retrieve();
    while(1){
        system("cls");
        displayUi();
        getch();
        acctnogen();
        gotoxy(43,10);
        scanf(" %[^\n]s", name);
        do{
            gotoxy(50,13);
            scanf("%d", &amount);
            if (amount<500){
                createtext(35,22,"Minimum Balance should be 500+. please try again");
                getch();
                clear(50,13,25);
                clear(30,22,60);
                createtext(57,22,"- - -");
                }
        }while(amount<500);
        pincode();
            do {
                for (i=0,x=51;i<6;i++,x+=2){
                    gotoxy(x,19);
                    confirmpin[i]=getch()+encrypt;
                    putchar('*');
                }
                confirmpin[i]='\0';

                if (strcmp(pin,confirmpin)!=0){
                        createtext(45,22,"Incorrect Pin, please try again");
                        getch();
                        clear(30,22,60);
                        clear(50,19,34);
                }
            } while (strcmp(pin,confirmpin)!=0);
            if(locate(name)>=0){
                clear(30,22,60);
                createtext(57,22,"- - -");
                createtext(45,22,"Account Exist, Please Try again");
                getch();
            }
            else{
                FILE *check;
                saveUI();
                check = fopen(Checker,"w");
                if (check == NULL){
                    system("COLOR 4F");
                    clear(37,15,55);
                    createtext(42,15,"ERROR CREATING ACCOUNT, FLASHDRIVE NOT DETECTED");
                    fclose(check);
                    remove(Checker);
                    gotoxy(1,32);
                    break;
                }
                else{
                    save();
                    fclose(check);
                    remove(Checker);
                    nameUI(20);
                    clear(37,16,55);
                    createtext(37,15,"ACCOUNT SUCCESFULLY CREATED!! Press [ENTER] to continue");
                    getch();
                    clear(37,15,55);
                    createtext(38,15,"THANK YOU FOR TRUSTING BDF! Press [ENTER] to continue");
                    getch();
                    clear(37,15,55);
                    createtext(36,15,"Run Project Transaction.C now ... Press [ENTER] to exit...");
                    getch();
                    gotoxy(1,32);
                    break;
                }
            }
        }
    }

