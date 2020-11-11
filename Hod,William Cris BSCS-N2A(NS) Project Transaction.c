#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#define encrypt 10
#define MAX 500
#define timer 10
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

void makenull(){
    last = -1;
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

void createtext(int x, int y, char* text){
    gotoxy(x,y);
    printf("%s",text);
}


int locate_accnumber(int accnum){
    for(int i=0;i<=last;i++)
        if(list[i].accno==accnum)
            return(i);
    return (-1);
}

int locate_pinnum(char pin[7]){
    for(int i=0;i<=last;i++)
        if(strcmp(list[i].pincode,pin)==0)
            return(i);
    return (-1);
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

void clear(int x, int y,int len){
    len+=x;
    for(int i = x;i<len;i++){
        gotoxy(i,y);
        printf(" ");
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
            for(int i=0;i<22;i++){
                printf("%c ",219);
            }
            createtext(51,20,"PRESS ANY KEY TO CONTINUE...");
            fclose(fp);
            remove(Checker);
            getch();
        }
    } while (fp==NULL);
    fclose(fp);
    system("cls");
}

void loginUI(){
    gotoxy(60-strlen(list[locate_accnumber(num)].accname),15);
    printf("W E L C O M E, %s [%d] !!",list[locate_accnumber(num)].accname,num);
    header(49,4);
    createBox(32,17,65,-4);
    createBox(42,18,45,6);
}

void nameUI(int y){
    createBox(42,y,45,6);
    createtext(53,y+2,"S U B M I T T E D   B Y:");
    createtext(56,y+3,"WILLIAM CRIS HOD");
    createtext(59,y+4,"BSCS - N2A");
    gotoxy(0,27);
}


void pincode(){
    int i,x,counter=0,time=timer,error=0;
    char confrmpin[6];
        do{
            createtext(52,20,"E N T E R   P I N C O D E");
            for (i=0,x=60;i<6;i++,x+=2){
                gotoxy(x,22);
                confrmpin[i]=getch()+encrypt;
                putchar('*');
                }
            confrmpin[i]='\0';
            if(strcmp(pin,confrmpin)!=0){
                counter++;
                if(counter==3){
                    error++;
                    system("COLOR 4F");
                    clear(52,25,26);
                    createtext(35,25,"E R R O R : M A X I M U M   A T T E M P T S  R E A C H E D");
                    gotoxy(56,26);
                    printf("A T T E M P T S: %d  ",counter);
                    gotoxy(0,30);
                    while(time!=0){
                        gotoxy(51,26);
                        printf("T R Y   A G A I N   I N : %d     ",time);
                        time--;
                        sleep(1);
                    }
                system("COLOR 1F");
                clear(33,25,97);
                clear(33,26,97);
                clear(51,22,27);
                counter = 0;
                time = timer*error;
                }
                else{
                    clear(52,25,26);
                    createtext(33,25,"W R O N G   P I N C O D E . T R Y  A G A I N (space to continue)...");
                    gotoxy(56,26);
                    printf("A T T E M P T S: %d  ",counter);
                    getch();
                    clear(33,25,97);
                    clear(33,26,97);
                    clear(51,22,27);
                }
            }
        }while(strcmp(pin,confrmpin)!=0);
}

void menuUI(){
    system("cls");
    FILE *check;
    check = fopen(Checker,"w");
     if (check == NULL)
          insertcard();

    createBox(35,2,64,4);
    createtext(37,4,"W E L C O M E    T O     B A N K O   D E   F E L I P I N A S");

    createBox(35,7,64,5);
    createtext(41,9,"A c c o u n t  N a m e");
    createtext(35+(16-(strlen(list[locate_accnumber(num)].accname)/2)),10,list[locate_accnumber(num)].accname);
    createtext(70,9,"A c c o u n t  N u m b e r");
    gotoxy(81,10);
    printf("%d",num);

    createBox(35,13,31,5);
    createtext(47,15,"WITHDRAW");
    createtext(48,16,"[ 1 ]");

    createBox(68,13,31,5);
    createtext(80,15,"DEPOSIT");
    createtext(81,16,"[ 2 ]");

    createBox(35,19,31,5);
    createtext(43,21,"BALANCE INQUIRY");
    createtext(48,22,"[ 3 ]");

    createBox(68,19,31,5);
    createtext(77,21,"FUND TRANSFER");
    createtext(81,22,"[ 4 ]");

    createBox(35,25,31,5);
    createtext(45,27,"CHANGE PIN");
    createtext(48,28,"[ 5 ]");

    createBox(68,25,31,5);
    createtext(81,27,"EXIT");
    createtext(81,28,"[ 0 ]");

    createBox(35,31,64,5);
    createtext(43,33,"ENTER THE CODE THAT CORRESPONDS TO YOUR CHOICE");
    createtext(59,34,"CODE >>");
}

void withdraw(){
    system("cls");
    int withdraw_amt,i,x,counter=0,time =timer;
    char accnm[4],wpin[6];

    itoa(num,accnm,10);
    createBox(39,1,56,4);
    createtext(52,3,"W I T H D R A W A L    S L I P");

    createBox(39,1,56,32);

    createBox(68,6,25,4);
    createtext(42,8,"A C C O U N T   N A M E");
    createtext(69+(12-(strlen(list[locate_accnumber(num)].accname)/2)),8,list[locate_accnumber(num)].accname);

    createBox(68,11,25,4);
    createtext(40,13,"A C C O U N T  N U M B E R");
    createtext(79,13,accnm);

    createBox(68,16,25,4);
    createtext(48,18,"A M O U N T");
    createtext(72,18,"P H P ");

    createBox(68,21,25,4);
    createtext(45,23,"E N T E R   P I N");

    if (list[locate_accnumber(num)].indept == 0){
            createBox(41,26,52,5);
            createtext(59,28,"N O  B A L A N C E");
            createtext(48,29,"[ PRESS ANY KEY TO GO BACK TO MENU... ]");
            getch();
            for(int a=0;a<5;a++)
                clear(40,26+a,54);
        }
    else{
    do {
        createtext(59,28,"ENTER [0] TO CANCEL");
        gotoxy(79,18);
        scanf("%d",&withdraw_amt);
        if(withdraw_amt==0){
            clear(58,28,25);
            createBox(41,26,52,5);
            createtext(50,28,"O P E R A T I O N  C A N C E L E D");
            createtext(48,29,"[ PRESS ANY KEY TO GO BACK TO MENU... ]");
            getch();
            for(int a=0;a<5;a++)
                clear(40,26+a,54);
            break;
        }
        else if (withdraw_amt>list[locate_accnumber(num)].indept){
            clear(58,28,25);
            createBox(41,26,52,5);
            createtext(47,28,"I N S U F F I C I E N T    B A L A N C E");
            createtext(51,29,"[ PRESS ANY KEY TO TRY AGAIN... ]");
            getch();
            for(int a=0;a<6;a++)
                clear(40,26+a,54);
            clear(78,18,10);
        }
        else if (withdraw_amt<0){
            clear(58,28,25);
            createBox(41,26,52,5);
            createtext(51,28,"A M O U N T   M U S T   B E  > 0");
            createtext(51,29,"[ PRESS ANY KEY TO TRY AGAIN... ]");
            getch();
            for(int a=0;a<6;a++)
                clear(40,26+a,54);
            clear(78,18,10);
        }
        else {
            FILE *check;
            check = fopen(Checker,"w");
            do{
                clear(58,28,25);
                for (i=0,x=75;i<6;i++,x+=2){
                      gotoxy(x,23);
                      wpin[i]=getch()+encrypt;
                      putchar('*');
                }
                wpin[i]='\0';
                if(strcmp(pin,wpin)!=0){
                    counter++;
                    if(counter == 3){
                        system("COLOR 4F");
                        createBox(41,26,52,5);
                        createtext(55,28,"W R O N G  P I N C O D E");
                        createtext(51,29,"PRESS ANY KEY TO TRY AGAIN IN ");

                        while(time!=0){
                            gotoxy(81,29);
                            printf("%d  ",time);
                            time--;
                            sleep(1);
                        }
                        system("COLOR 1F");
                        clear(42,29,51);
                        createtext(51,29,"[ PRESS ANY KEY TO TRY AGAIN... ]");
                        getch();
                        for(int a=0;a<6;a++)
                            clear(40,26+a,54);
                        clear(74,23,14);
                        counter = 0;
                        time = timer;
                    }
                    else{
                    createBox(41,26,52,5);
                    createtext(55,28,"W R O N G  P I N C O D E");
                    createtext(51,29,"[ PRESS ANY KEY TO TRY AGAIN... ]");
                    getch();
                    for(int a=0;a<6;a++)
                        clear(40,26+a,54);
                    clear(74,23,14);
                    }
                }
                else if (check == NULL){
                    insertcard();
                    break;
                }
                else{
                    fclose(check);
                    remove(Checker);
                    createBox(41,26,52,5);
                    createtext(49,28,"W I T H R A W   S U C C E S S F U L !!");
                    createtext(48,29,"[ PRESS ANY KEY TO GO BACK TO MENU... ]");
                    list[locate_accnumber(num)].indept-=withdraw_amt;
                    getch();
                    break;
                }
              }while(strcmp(pin,wpin)!=0);
            }
        }while (withdraw_amt>list[locate_accnumber(num)].indept || withdraw_amt<0);
    }
}


void deposit(){

    system("cls");
    int deposit_amt,i,x,counter=0,time =timer;
    char accnm[4],wpin[7];
    itoa(num,accnm,10);
    createBox(39,1,56,4);
    createtext(56,3,"D E P O S I T    S L I P");

    createBox(39,1,56,32);

    createBox(68,6,25,4);
    createtext(42,8,"A C C O U N T   N A M E");
    createtext(69+(12-(strlen(list[locate_accnumber(num)].accname)/2)),8,list[locate_accnumber(num)].accname);

    createBox(68,11,25,4);
    createtext(40,13,"A C C O U N T  N U M B E R");
    createtext(79,13,accnm);

    createBox(68,16,25,4);
    createtext(48,18,"A M O U N T");
    createtext(72,18,"P H P ");

    createBox(68,21,25,4);
    createtext(45,23,"E N T E R   P I N");

    do {
        createtext(59,28,"ENTER [0] TO CANCEL");
        gotoxy(79,18);
        scanf("%d",&deposit_amt);
        if(deposit_amt==0){
            clear(58,28,25);
            createBox(41,26,52,5);
            createtext(50,28,"O P E R A T I O N  C A N C E L E D");
            createtext(48,29,"[ PRESS ANY KEY TO GO BACK TO MENU... ]");
            getch();
            for(int a=0;a<6;a++)
                clear(40,26+a,54);
            break;
        }
        else if (deposit_amt<0){
            clear(58,28,25);
            createBox(41,26,52,5);
            createtext(51,28,"A M O U N T   M U S T   B E  > 0");
            createtext(51,29,"[ PRESS ANY KEY TO TRY AGAIN... ]");
            getch();
            for(int a=0;a<5;a++)
                clear(40,26+a,54);
            clear(78,18,10);
        }
        else{
             FILE *check;
            check = fopen(Checker,"w");
        do{
            clear(56,28,25);
            for (i=0,x=75;i<6;i++,x+=2){
                  gotoxy(x,23);
                  wpin[i]=getch()+encrypt;
                  putchar('*');
            }
            wpin[i]='\0';
            if(strcmp(pin,wpin)!=0){
               counter++;
                    if(counter == 3){
                        system("COLOR 4F");
                        createBox(41,26,52,5);
                        createtext(55,28,"W R O N G  P I N C O D E");
                        createtext(51,29,"PRESS ANY KEY TO TRY AGAIN IN ");

                        while(time!=0){
                            gotoxy(81,29);
                            printf("%d  ",time);
                            time--;
                            sleep(1);
                        }
                        system("COLOR 1F");
                        clear(42,29,51);
                        createtext(51,29,"[ PRESS ANY KEY TO TRY AGAIN... ]");
                        getch();
                        for(int a=0;a<6;a++)
                            clear(40,26+a,54);
                        clear(74,23,14);
                        counter = 0;
                        time = timer;
                    }
                    else{
                    createBox(41,26,52,5);
                    createtext(55,28,"W R O N G  P I N C O D E");
                    createtext(51,29,"[ PRESS ANY KEY TO TRY AGAIN... ]");
                    getch();
                    for(int a=0;a<6;a++)
                        clear(40,26+a,54);
                    clear(74,23,14);
                    }
                }
            else if (check == NULL){
                    insertcard();
                    break;
            }
            else{
                fclose(check);
                remove(Checker);
                createBox(41,26,52,5);
                gotoxy(48,28);
                printf("PHP %d WAS DEPOSITED TO YOUR ACCOUNT",deposit_amt);
                createtext(48,29,"[ PRESS ANY KEY TO GO BACK TO MENU... ]");
                list[locate_accnumber(num)].indept+=deposit_amt;
                getch();
                break;
            }
          }while(strcmp(pin,wpin)!=0);
        }
    }while (deposit_amt<0);
}

void balanceinquiry(){
    FILE *check;
    check = fopen(Checker,"w");
    system("cls");
    if (check == NULL)
        insertcard();
    createBox(39,1,56,4);
    createtext(53,3,"B A L A N C E   I N Q U I R Y");
    createBox(39,1,56,29);
    header(51,8);
    createtext(43,19,"Y O U R   R E M A I N I N G   B A L A N C E  I S");
    createBox(42,20,50,4);
    gotoxy(62,22);
    printf("PHP %d",list[locate_accnumber(num)].indept);
    createtext(53,27,"PRESS ANY KEY TO CONTINUE...");
    getch();
}

void fundtransfer(){

    int amount_transfer,numdest,i,x,time=timer,counter=0;
    char pintransfer[7];
    system("cls");
    createBox(38,1,57,4);
    createtext(54,3,"F U N D   T R A N S F E R");
    createBox(23,6,46,4);
    gotoxy(24,8);
    printf("ACCOUNT NAME >> %s", list[locate_accnumber(num)].accname);
    createBox(71,6,39,4);
    gotoxy(72,8);
    printf("ACCOUNT NUMBER >> %d", num);
    createBox(38,11,57,4);
    createtext(39,13,"ENTER AMOUNT TO BE TRANSFERED >> PHP ");

    createtext(45,17,"R E C I E V E R   O F   T H E    F U N D S");
    createBox(23,19,46,4);
    createBox(71,19,39,4);
    createBox(38,24,57,5);
    createtext(24,21,"ACCOUNT NAME >> ");
    createtext(72,21,"ACCOUNT NUMBER >> ");

    do{
        createtext(51,26,"ENTER [0] TO CANCEL OPERATION");
        gotoxy(76,13);
        scanf("%d",&amount_transfer);
        if (amount_transfer>list[locate_accnumber(num)].indept){
            clear(51,26,40);
            createtext(51,26,"ERROR: INSUFFICIENT BALANCE");
            createtext(48,27,"[ PRESS ANY KEY TO TRY AGAIN... ]");
            getch();
            clear(76,13,15);
            clear(38,26,50);
            clear(48,27,40);
        }
        else if (amount_transfer == 0)
        {
            createtext(48,26,"O P E R A T I O N   C A N C E L E D");
            createtext(46,27,"[ PRESS ANY KEY TO GO BACK TO MENU... ]");
            getch();
            break;
            clear(51,26,30);
        }
        else if (amount_transfer<0){
            clear(51,26,40);
            createtext(51,26,"ERROR: AMOUNT SHOULD BE > 0");
            createtext(48,27,"[ PRESS ANY KEY TO TRY AGAIN... ]");
            getch();
            clear(76,13,15);
            clear(38,26,50);
            clear(48,27,40);
        }
    else{

    gotoxy(90,21);
    scanf("%d", &numdest);
    if (locate_accnumber(numdest)<0)
    {
        createtext(40,26,"ERROR: ACCOUNT WITH ENTERED ACCOUNT NUMBER NOT FOUND");
        createtext(46,27,"[ PRESS ANY KEY TO GO BACK TO MENU... ]");
        getch();
    }
    else {
        createtext(40,21,list[locate_accnumber(numdest)].accname);
        gotoxy(47,26);
        printf("YOU WILL TRANSFER PHP %d TO %s",amount_transfer,list[locate_accnumber(numdest)].accname);
        createtext(51,27,"[ PRESS ANY KEY TO CONTINUE... ]");
        getch();
        clear(47,26,50);
        clear(47,27,50);
        clear(37,29,60);
        createBox(38,24,57,4);
        createtext(40,26,"E N T E R  P I N C O D E  >> ");
        FILE *check;
        check = fopen(Checker,"w");
        do{
            for (i=0,x=70;i<6;i++,x+=2){
                      gotoxy(x,26);
                      pintransfer[i]=getch()+encrypt;
                      putchar('*');
                }
                pintransfer[i]='\0';
                if(strcmp(pin,pintransfer)!=0){
                    counter++;
                    if(counter == 3){
                        system("COLOR 4F");
                        createtext(55,25,"W R O N G  P I N C O D E");
                        createtext(49,26,"PRESS ANY KEY TO TRY AGAIN IN ");

                        while(time!=0){
                            gotoxy(81,26);
                            printf("%d  ",time);
                            time--;
                            sleep(1);
                        }
                        system("COLOR 1F");
                        clear(42,26,51);
                        createtext(49,26,"[ PRESS ANY KEY TO TRY AGAIN... ]");
                        getch();
                        clear(55,25,40);
                        clear(51,26,40);
                        clear(70,22,14);
                        counter = 0;
                        time = timer;
                    }
                    else{
                    createtext(53,29,"W R O N G  P I N C O D E");
                    createtext(49,30,"[ PRESS ANY KEY TO TRY AGAIN... ]");
                    getch();
                    clear(53,29,40);
                    clear(49,30,40);
                    clear(70,26,14);
                    }
                }
                 else if (check == NULL){
                    insertcard();
                    break;
                }
                else{
                fclose(check);
                remove(Checker);
                gotoxy(48,29);
                printf("PHP %d WAS TRANSFERED TO %s",amount_transfer,list[locate_accnumber(numdest)].accname);
                createtext(48,30,"[ PRESS ANY KEY TO GO BACK TO MENU... ]");
                list[locate_accnumber(numdest)].indept+=amount_transfer;
                list[locate_accnumber(num)].indept-=amount_transfer;
                getch();
                break;
                }
          }while(strcmp(pin,pintransfer)!=0);
        }
        break;
      }
    }while(amount_transfer>list[locate_accnumber(num)].indept || amount_transfer<0);
}

void changepin(){
    char oldPin[7];
    char newPin[7];
    int error = 0;
    char confirmNew[7];
    int i,x ;
    system("cls");
    createBox(38,1,57,4);
    createtext(54,3,"C H A N G E   P I N");
    createBox(38,6,57,4);
    createtext(39,8,"E N T E R  O L D   P I N : ");
    createBox(38,11,57,4);
    createtext(39,13,"E N T E R  N E W  P I N : ");
    createBox(38,16,57,4);
    createtext(39,18,"C O N F I R M  N E W   P I N : ");
    createBox(38,21,57,5);
    do{
    for (i=0,x=66;i<6;i++,x+=2){
        gotoxy(x,8);
        oldPin[i]=getch()+encrypt;
        putchar('*');
    }
    oldPin[i]='\0';
        if (strcmp(oldPin,pin)!=0)
        {
            createtext(53,23,"W R O N G   P I N C O D E");
            createtext(51,24,"[ PRESS ANY KEY TO TRY AGAIN ]");
            getch();
            clear(39,23,50);
            clear(39,24,50);
            clear(66,8,15);
        }
    }while (strcmp(oldPin,pin)!=0);

    do{
        do{
            for (i=0,x=66;i<6;i++,x+=2){
                gotoxy(x,13);
                newPin[i]=getch()+encrypt;
                error +=isdigit(newPin[i]-encrypt);
                putchar('*');
            }
            newPin[i]='\0';
                if (error <6){
                    createtext(48,23,"PINCODE MUST CONTAIN NUMBERS ONLY !!");
                    createtext(51,24,"[ PRESS ANY KEY TO TRY AGAIN ]");
                    error=0;
                    getch();
                    clear(39,23,50);
                    clear(39,24,50);
                    clear(66,13,15);
            }
        }while(error<6);
        for (i=0,x=70;i<6;i++,x+=2){
            gotoxy(x,18);
            confirmNew[i]=getch()+encrypt;
            putchar('*');
        }
        confirmNew[i]='\0';
        FILE *check;
        check = fopen(Checker,"w");
        if(strcmp(newPin,confirmNew)!=0)
        {
            createtext(45,23,"P I N C O D E   D O E S   N O T   M A T C H");
            createtext(51,24,"[ PRESS ANY KEY TO TRY AGAIN ]");
            getch();
            clear(39,23,50);
            clear(39,24,50);
            clear(70,18,15);
            clear(66,13,15);
        }
         else if (check == NULL){
                    insertcard();
                    break;
            }
        else{
            fclose(check);
            remove(Checker);
            createtext(40,23,"P I N C O D E   C H A N G E   S U C C E S S F U L L Y");
            createtext(48,24,"[ PRESS ANY KEY TO GO BACK TO MENU ]");
            getch();
            strcpy(pin,newPin);
            strcpy(list[locate_accnumber(num)].pincode,newPin);
            break;

        }
    }while (strcmp(newPin,confirmNew)!=0);

}

void insert (char accountname[50], char pcode[7], int acctno, int amnt){
        last++;
        strcpy(list[last].accname,accountname);
        strcpy(list[last].pincode,pcode);
        list[last].accno = acctno;
        list[last].indept = amnt;
    }

void retrieve(){
    FILE *fp;
    char accountname[50],pcode[7];
    int no,amt;
    fp = fopen(Location,"r");
    if (fp==NULL){
        system("cls");
        createBox(42,13,45,3);
        gotoxy(41,15);
        printf("FILE NOT FOUND. PRESS ENTER TO CREATE MAIN DATABASE FILE");
        fp = fopen(Location,"w+");
        getch();
    }
    else{
        while(!feof(fp)){
            fscanf(fp,"%d %[^\t]%d %[^\n]",&no,accountname,&amt,pcode);
            insert(accountname,pcode,no,amt);
        }
    }
    fclose(fp);
}
void saveUI(){
    FILE *check;
    int counter;
        system("cls");

            header(49,4);
            createBox(42,13,45,4);
            createtext(55,15,"S A V I N G   D A T A");
            createtext(41,18,"[");
            createtext(87,18,"]");
            for (counter=0;counter<2;counter++){
               gotoxy(43,18);
                for(int i=0;i<21;i++){
                printf("%c ",219);
                Sleep(90);
                }
                printf("%c",219);
                gotoxy(43,18);
                for(int i=0;i<22;i++){
                    printf("  ");
                    Sleep(90);
                }
            }
            check = fopen(Checker,"w");
            if (check == NULL){
                createBox(33,13,63,3);
                for(int i=14;i<16;i++)
                    clear(40,i,50);
                system("COLOR 4F");
                clear(37,15,55);
                for(int i=43;i<86;i++){
                    gotoxy(i,18);
                    printf("%c",219);
                }
                createtext(42,15,"ERROR CREATING ACCOUNT, FLASHDRIVE NOT DETECTED");
                fclose(check);
                remove(Checker);
                gotoxy(1,32);
            }
            else{
            fclose(check);
            remove(Checker);
            clear(48,15,40);
            createBox(33,13,63,4);
            for(int i=14;i<17;i++)
                clear(40,i,50);
            for(int i=43;i<86;i++){
                gotoxy(i,18);
                printf("%c",219);
            }

            createtext(40,15,"T H A N K   Y O U   F O R   T R U S T I N G  BDF !!");
            gotoxy(0,25);
            nameUI(20);
    }
}

void scanRegistered(){
    FILE *reg;
    reg = fopen(RegInfo,"r+");
    if (reg==NULL){
        system("COLOR 7C");
        system("cls");
        createBox(17,17,101,4);
        gotoxy(24,19);
        printf("FLASHDRIVE NOT REGISTERED, RUN 'PROJECT REGISTRATION.C' FIRST. Press [ENTER] to exit...");
        getch();
        gotoxy(27,25);
        exit(1);
    }
    else{
        while(!feof(reg)){
            fscanf(reg,"%d %s",&num,pin);
        }
        strcpy(name,list[locate_accnumber(num)].accname);
        amount = list[locate_accnumber(num)].indept;
    }
    fclose(reg);
}

void save(){
    FILE *fp;
    FILE *save;
    fp= fopen(Location,"w+");
    save = fopen(RegInfo,"w+");
    for (int i=0;i<last;i++)
        fprintf(fp,"%d\t%s\t%d\t%s\n",list[i].accno,list[i].accname,list[i].indept,list[i].pincode);
    fprintf(save,"%d\t%s",num,pin);
    fclose(fp);
}

int main(){
    int choice;
    system("COLOR 1F");
    insertcard();
    scanRegistered();
    system("cls");
    makenull();
    retrieve();
    loginUI();
    pincode();
    while(1){
        menuUI();
        gotoxy(67,34);
        scanf("%d",&choice);
        switch(choice){
            case 1: withdraw(); break;
            case 2: deposit(); break;
            case 3: balanceinquiry(); break;
            case 4: fundtransfer(); break;
            case 5: changepin(); break;
            case 0: saveUI(); save(); exit(1); break;
            default:
                clear(43,33,55);
                createtext(54,33,"I N V A L I D   C H O I C E");
                getch();
                clear(42,34,40);
            break;
        }
    }
}
