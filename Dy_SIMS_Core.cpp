//Copyright (c) 2021 Qilu University of Technology Class of software Engineer(Software Development) 21-1 Duyu.
//The System of Students Information Manage.
//This program rely on 3 files: StudentsInfo.txt ConsoleSettings.config PasswordInfo.txt
#include<bits/stdc++.h>
#include<algorithm>
#include<windows.h>
#include<thread> //This is a muti-thread process.It need to be imported.
#define BIGNUM 10000
#define INITIAL_NUMBER 2021001
//Define copyright information.
#define COPYRIGHT "Copyright_(c)_2021_Qilu_University_of_Technology_Class_of_software_Engineer(Software Development)_21-1_Duyu."
#define VERSION "VERSION_1.0.1"
//Define rely file name.
#define STUINFO "StudentsInfo.txt" //Structure of Database:Name Sex Class Chinese Maths English
#define CONSET "ConsoleSettings.config"
#define PASS "PasswordInfo.txt"
using namespace std;
//Declare of StudentInfo
   typedef struct stu
	{
		char name[200];
   	    int num;
   	    bool sex; //0=man,1=woman
   	    int cla;
   	    double chinese,math,english;
   	    double total;
   } student;
   student glostu[BIGNUM];
   int glonum;
//Declare of Encrypt.
   void WriteEncWord(char* source_Oriword);
   bool GetUnencWord(char* destination);
   bool SetAdministratorPassword(void); //return 0:succeed.return 1:failed.
   bool Login(void);
//Declare of GUI and check environment.
   void SetColor(void);
   void GetColor(void);
   bool Check_Environment(int Arg_Count,char* Runtime_Path,char* Return_ErrInfo);
//Declare of Print Menu.
   void Print_Welcome(void);
   void Print_AddInfo(void);
   void Print_DeleteInfo(void);
   void Print_ExchangeInfo(void);
   void Print_FindInfo(void);
//Declare of business
   bool Welcome(int seletion);
   bool AddInfo(void);
   int  Getnum(FILE*);
   bool DeleteInfo(void);
   bool ExchangeInfo(void);
   void FindInfo(void); //According to name.
   void PrintAllInfo(void);
   void Exit_safe(int EXIT_CODE);
//Declare of other function
   void Warn_Handle(char*); //print the words and change console color.
   void Print_Copyright_And_Version(void); 
   void Muti_Thread_titleTime();
   int Readdata(void);
   void Writedata(void);
   void PRINT_COPYRIGHT(void);
void PRINT_COPYRIGHT()
{
	printf("__________________________________________________\n");
	printf("______________Copyright Information_______________\n\n");
	printf(COPYRIGHT);putchar('\n');
	printf(VERSION);
	printf("\n__________________________________________________\n");
	system("pause");
}
void Writedata()
{
	FILE *fp=fopen(STUINFO,"w");int rt=0;
	for(int k=0;k<=glonum-1;++k)
	{
		fflush(fp);
		if(glostu[k].num!=-1)
		{
		  fprintf(fp,"%d %s %d %d %.1lf %.1lf %.1lf %.1lf\n",glostu[k].num,glostu[k].name,glostu[k].sex,glostu[k].cla,glostu[k].chinese,glostu[k].math,glostu[k].english,glostu[k].total);
	      rt++;
		}
	}
	fclose(fp);
	glonum=rt;
}
int Readdata()
{
	FILE *fp=fopen(STUINFO,"r");int k=0;fflush(fp);
	while(fscanf(fp,"%d %s %d %d %lf %lf %lf %lf",&glostu[k].num,glostu[k].name,&glostu[k].sex,&glostu[k].cla,&glostu[k].chinese,&glostu[k].math,&glostu[k].english,&glostu[k].total)&&glostu[k].num!=0)
	{
		//fflush(fp);
	    ++k;
       //printf("+++++++++++%d  %d\n",glostu[k-1].num,k);
       //system("pause");
	}
	fclose(fp);
	glonum=k;
      //printf("========%d\n",glonum);
	return k;
}
void Muti_Thread_titleTime()
{
	while(1)
	system("title Student Information Management System - %time:~0,-3%");
}
void Print_Welcome()
{
	 //system("mode con cols=55 lines=32");
	 printf("***********************************************\n\n");
	 printf("  Welcome To Use Student Information System\n\n");
	 printf("***********************************************\n\n");
	 printf("_______________________________________________\n\n");
	 printf("   1.Add student's information.\n");
	 printf("   2.Delete student's information.\n");
	 printf("   3.Exchange student's information.\n");
	 printf("   4.Find student's information.\n");
	 printf("   5.Print all students' information.\n");
	 printf("   6.Setting Administrator Password.\n");
	 printf("   7.Setting Colors of console.\n");
	 printf("   8.Copyright Declare and Information.\n");
	 printf("   0.Exit System.\n");
	 printf("_______________________________________________\n\nPlease Choose a Function>");
}
void Print_AddInfo()
{
    printf("_____________Add Student Information___________\n");
    printf("Please Input Student Infomation:\n");
    printf("Sex Class Chinese Maths English\n>");
}
void Print_DeleteInfo()
{
	 printf("___________Delete Student Information__________\n");
	 printf("Please Input Student Number Which You Want To Delete\n>");
}
void Print_ExchangeInfo(void)
{
	 printf("__________Exchange Student Information_________\n");
	 printf("Please Input Student Number Which You Want To Exchange\n>");
}
void Print_FindInfo(void)
{
	 printf("___________Find Student Information_________\n");
	 printf("Please Input Student Number Which You Want To Find\n>");
}
void GetColor(void)
{
	FILE *p=fopen(CONSET,"r");
	if(!p)
	{
		printf("  !WARNING:COLOR SETTING FALIED!  \n");
		return;
	}
	char temp[3];fscanf(p,"%s",temp);
	fclose(p);
	char color_command[10]="COLOR ";
	strcat(color_command,temp);
	system(color_command);
}
void Warn_Handle(char* in)
{
	system("color 4A");
	printf("\n%s\n",in);
	system("echo PRESS ANY KEY TO CONTINUE.");
	system("pause>nul");
	GetColor();
}
bool Login() //0=succeed,1=failed.
{
	 system("mode con cols=90 lines=32");
	 system("Title Student Information Management System");
	 printf("***********************************************\n\n");
	 printf("  Welcome To Use Student Information System\n\n");
	 printf("***********************************************\n\n");
	 char InputPass[200];char RightPass[200];
	 fflush(stdin);
	 bool flag=GetUnencWord(RightPass);
	 if(flag)
	 {
	 	 return 0;
	 }
	 printf("Please Input the Password of Administrator\n>");
	 gets(InputPass);
	 if(strlen(InputPass)>=99)
	 {
	 	 char p[200]="\n !Error,Password is too long!\n";
	 	 Warn_Handle(p);
	 	 return 1;
	 }
	 if(strcmp(RightPass,InputPass))
	 {
	 	 char p[200]="\n !Error,Wrong Password!\n";
	 	 Warn_Handle(p);
	 	 return 1;
	 }
	 else
	 {
	 	 system("cls");
	 	 return 0;
	 }
}
bool SetAdministratorPassword() //return 0:succeed.return 1:failed.
{
	 char RightPass[100];char ori_InputPass[200];
	 printf("__________Set Administrator Password_________\n");
	 fflush(stdin);
	 bool flag=GetUnencWord(RightPass);
	 if(flag) goto SAP_LABEL1;
	 printf("Please Input Original Password\n>");
	 gets(ori_InputPass);
	 if(strlen(ori_InputPass)>=99)
	 {
	 	 char p[200]="\n !Error,Password is too long!\n";
	 	 Warn_Handle(p);
	 	 return 1;
	 }
	 if(strcmp(RightPass,ori_InputPass))
	 {
	 	 char p[200]="\n !Error,Wrong Password!\n";
	 	 Warn_Handle(p);
	 	 return 1;
	 }
	 else
	 {
SAP_LABEL1:
	 	 printf("Please Input New Password\nIf you want to cancel password, you can input NO_PASSWORD\n>");
	 	 char new_InputPass[200];
	 	 gets(new_InputPass);
	 	 if(strlen(new_InputPass)>99)
	 	 {
	 	 	 char p[200]="\n !Error,Password is too long!\n";
	 	 	 Warn_Handle(p);
	 	 	 return 1;
	 	 }
	 	 else
	 	 {
	 	 	 WriteEncWord(new_InputPass);
	 	 	 return 0;
	 	 }
	 }
}
void WriteEncWord(char* source_Oriword)
{
	 char new_key[200];
	 //Get Random Number
	 {
	   srand(time(0));
	   int key=(rand()%10);
	   itoa(key,new_key,10);
    }
	 char temp[200];
	 for(int a=0;a<=strlen(source_Oriword)-1;++a)
	 {
	 	 temp[a]=source_Oriword[a]^atoi(new_key);
	 }
	 FILE *fp=fopen(PASS,"w");
	 if(!strcmp(source_Oriword,"NO_PASSWORD"))
	 {
	 	 fprintf(fp,"-1");
	 	 fclose(fp);
		 return;
	 }
	 fprintf(fp,"%d\n",atoi(new_key));
	 for(int a=0;a<=strlen(source_Oriword)-1;++a)
	 {
	 	 fprintf(fp,"%c",temp[a]);
	 }
	 fclose(fp);
}
bool GetUnencWord(char* out) //return 0=common,return 1=no need password.
{
	 //File of Password_Storage has 2 lines - 1.Key 2.Encrypted Password. Enc & Unenc algorithm is key^encword.
	 //Key=-1 means do not need password to login.
	 FILE *fp=fopen(PASS,"r");
	 char encword[100];char encword_key[3];
	 fgets(encword_key,4,fp);encword_key[2]='\0';
    fgets(encword,BIGNUM,fp);
    int key=atoi(encword_key);
    if(key==-1) return 1;
    for(int a=0;a<=strlen(encword)-1;++a)
    {
    	 out[a]=encword[a]^key;
    }
    out[strlen(encword)]='\0';
    fclose(fp);
    return 0;
}
bool Welcome(int selection)
{
	 switch(selection)
	 {
	 	case 1:
	 	{
			 AddInfo();
	 	}
	 	break;
      case 2:
      {
      	     DeleteInfo();
      }
      break;
      case 3:
      {
        	 ExchangeInfo();
      }
      break; 
      case 4:
      {
      	     FindInfo();
      }
	  break;
      case 5:
		    PrintAllInfo();
			 break;
      case 6:
		    SetAdministratorPassword();
			 break;
      case 7:
      {
      	 SetColor();
      }
		    break;
	  case 8:PRINT_COPYRIGHT();break;
      case 0:
		Exit_safe(0);
		    break;
      default:
      {
      	 char a[100]="Sorry,your input is not available.\n";
      	 Warn_Handle(a);
      }
	 }
	 return 0;
}
void SetColor()
{
	 printf("______________Color Settings______________\n");
	 printf("Menu:\n");
	 printf("0=Black \n1=Blue \n2=Green \n3=Thin Green \n4=Red \n5=Purple \n6=Yellow \n7=White \n8=Grey \n9=Thin Blue \n");
     printf("A=Thin Green2 \nB=Thin Green3 \nC=Thin Red3 \nD=Thin Purple \nE=Thin Yellow \nF=Light White\n");
     char a,b;
     fflush(stdin);
     scanf("%c%c",&a,&b);
     a=toupper(a);b=toupper(b);
     if(!((a>='A' && a<='F') || (a>='0' && a<='9') && (b>='A' && b<='F') || (b>='0' && b<='9')))
     {
    	 char p[100]="Your command is not available.";
    	 Warn_Handle(p);
    	 return;
     }
     else
     {
    	 FILE *fp=fopen(CONSET,"w");
    	 if(!fp)
    	 {
    	 	 char p[100]="Failed to open color config file.";
    	     Warn_Handle(p);
    	     return;
    	 }
    	 fprintf(fp,"%c%c",a,b);
    	 fclose(fp);
     }
}
bool AddInfo()
{
	 bool flag=1;
	 FILE *sfp=fopen(STUINFO,"a+");
	 if(!sfp)
	 {
	 	 char er[200]=" !Warning:Failed to open database of students' information.";
	 	 Warn_Handle(er);
	 	 return 1;
	 }
	 while(flag)
	 {
	 	 student stutemp;
	 	 stutemp.num=Getnum(sfp);fseek(sfp,0L,SEEK_SET);
		 fflush(stdin);
	 	 printf("Please Input Student's Name\n>");
	 	 fflush(stdin);gets(stutemp.name);fflush(stdin);
	 	 Print_AddInfo();
	 	 fflush(stdin);
	 	 scanf("%d %d %lf %lf %lf",&stutemp.sex,&stutemp.cla,&stutemp.chinese,&stutemp.math,&stutemp.english);
	 	 stutemp.total=stutemp.chinese+stutemp.math+stutemp.english;
	 	 fprintf(sfp,"%d %s %d %d %.1lf %.1lf %.1lf %.1lf\n",stutemp.num,stutemp.name,stutemp.sex,stutemp.cla,stutemp.chinese,stutemp.math,stutemp.english,stutemp.total);
         fseek(sfp,0L,SEEK_SET);
         printf("|-------------------------------------------------------------------------|\n");
		 printf("|%-10s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|\n","NUMBER","NAME","SEX","CLASS","CHINESE","MATHE","ENGLISH","TOTAL"); 
		 printf("|----------+--------+--------+--------+--------+--------+--------+--------|\n");
    	 printf("|%-10d|%-8s|%-8d|%-8d|%-8.1lf|%-8.1lf|%-8.1lf|%-8.1lf|\n",stutemp.num,stutemp.name,stutemp.sex,stutemp.cla,stutemp.chinese,stutemp.math,stutemp.english,stutemp.total);
		 printf("|-------------------------------------------------------------------------|\n");
		 printf("_______________________\nDo you want to continue to add(0=No,1=Yes)\n>");
	     fflush(stdin);int r;
		 scanf("%d",&r);flag=r;
	 }
     fseek(sfp,0L,SEEK_SET);
	 fclose(sfp);
	 return 0;
}
void Exit_safe(int ex_code)
{
	 exit(ex_code);
}
int Getnum(FILE *fp)
{
	 fseek(fp,0L,SEEK_SET);
	 char tempnum[2000];int count=0;int ctmp[2000];
	 while(fgets(tempnum,BIGNUM,fp))
	 {
	 	 if(tempnum[0]==' ') continue;
	 	 ctmp[count]=atoi(tempnum);
	 	 ++count;
	 }
	 if(!count) return INITIAL_NUMBER;
	 sort(ctmp,ctmp+count);
//	 for(int i=0;i<=count-1;++i)
//	 {
//	 	 if(ctmp[i]!=i+1+INITIAL_NUMBER)
//	 	 {
//	 	 	 fseek(fp,0L,SEEK_SET);
//	 	 	 return i+1+INITIAL_NUMBER;
//	 	 }
//	 }
     int qwe=0;
     for(int q=INITIAL_NUMBER;q<=INITIAL_NUMBER-1+count;++q)
	 {
	 	if(ctmp[qwe]!=q) 
		{
		 	fseek(fp,0L,SEEK_END);
		 	return q;
		}
	 	++qwe;
	 }
	 fseek(fp,0L,SEEK_END);
	 return count+INITIAL_NUMBER;
}
bool DeleteInfo()
{
DELE_LABEL1:
	Print_DeleteInfo();
	Readdata();
	int num;fflush(stdin);
	scanf("%d",&num);bool flag=0;
	for(int a=0;a<=glonum-1;++a)
	{
		if(glostu[a].num==num)
		{
			printf("\n|-------------------------------------------------------------------------|\n");
		    printf("|%-10s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|\n","NUMBER","NAME","SEX","CLASS","CHINESE","MATHE","ENGLISH","TOTAL"); 
		    printf("|----------+--------+--------+--------+--------+--------+--------+--------|\n");
    	    printf("|%-10d|%-8s|%-8d|%-8d|%-8.1lf|%-8.1lf|%-8.1lf|%-8.1lf|\n",glostu[a].num,glostu[a].name,glostu[a].sex,glostu[a].cla,glostu[a].chinese,glostu[a].math,glostu[a].english,glostu[a].total);
		    printf("|-------------------------------------------------------------------------|\n");
		    printf("Do you want to delete it(0=No,1=Yes)\n>");fflush(stdin);
		    int w;scanf("%d",&w);
		    if(!w) goto DELE_LABEL1;
			glostu[a].num=-1;flag=1;
		}
	}
	if(!flag)
	{
		char op[100]=" !Warning,There are no student number which you input!";
		Warn_Handle(op);
		goto DELE_LABEL1;
	}
	Writedata();
	printf("________________________________________\nDo you want to continue to delete(0=No,1=Yes)\n>");
	int q;scanf("%d",&q);
	if(q) goto DELE_LABEL1;
}
void FindInfo()
{
	Readdata();
	printf("______________________________________________\nPlease input student name\n>");
	char stn[222];fflush(stdin);
	gets(stn);
	for(int a=0;a<=glonum-1;++a)
	{
		if(strstr(glostu[a].name,stn))
		{
			printf("\n|-------------------------------------------------------------------------|\n");
		    printf("|%-10s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|\n","NUMBER","NAME","SEX","CLASS","CHINESE","MATHE","ENGLISH","TOTAL"); 
		    printf("|----------+--------+--------+--------+--------+--------+--------+--------|\n");
    	    printf("|%-10d|%-8s|%-8d|%-8d|%-8.1lf|%-8.1lf|%-8.1lf|%-8.1lf|\n",glostu[a].num,glostu[a].name,glostu[a].sex,glostu[a].cla,glostu[a].chinese,glostu[a].math,glostu[a].english,glostu[a].total);
		    printf("|-------------------------------------------------------------------------|\n");
		}
	}
	system("echo PRESS ANY KEY TO CONTINUE && pause>nul");
}
void PrintAllInfo()
{
	Readdata();
	for(int a=0;a<=glonum-1;++a)
	{
			printf("\n|-------------------------------------------------------------------------|\n");
		    printf("|%-10s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|\n","NUMBER","NAME","SEX","CLASS","CHINESE","MATHE","ENGLISH","TOTAL"); 
		    printf("|----------+--------+--------+--------+--------+--------+--------+--------|\n");
    	    printf("|%-10d|%-8s|%-8d|%-8d|%-8.1lf|%-8.1lf|%-8.1lf|%-8.1lf|\n",glostu[a].num,glostu[a].name,glostu[a].sex,glostu[a].cla,glostu[a].chinese,glostu[a].math,glostu[a].english,glostu[a].total);
		    printf("|-------------------------------------------------------------------------|\n");
	}
	system("echo PRESS ANY KEY TO CONTINUE && pause>nul");
}
bool ExchangeInfo()
{
EXC_LABEL1:
	Readdata();
	Print_ExchangeInfo();
	int temp;int a;
	fflush(stdin);scanf("%d",&temp);
	for(a=0;a<=glonum-1;++a)
	{
		if(glostu[a].num==temp)
		{
			printf("\n|-------------------------------------------------------------------------|\n");
		    printf("|%-10s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|\n","NUMBER","NAME","SEX","CLASS","CHINESE","MATHE","ENGLISH","TOTAL"); 
		    printf("|----------+--------+--------+--------+--------+--------+--------+--------|\n");
    	    printf("|%-10d|%-8s|%-8d|%-8d|%-8.1lf|%-8.1lf|%-8.1lf|%-8.1lf|\n",glostu[a].num,glostu[a].name,glostu[a].sex,glostu[a].cla,glostu[a].chinese,glostu[a].math,glostu[a].english,glostu[a].total);
		    printf("|-------------------------------------------------------------------------|\n");
		    printf("Do you want to exchange this student information.(0=No,1=Yes)\n>");fflush(stdin);
		    int df;scanf("%d",&df);
		    if(!df) goto EXC_LABEL1;
		    fflush(stdin);
		    printf("Please Input Student's Name\n>");
	 	    fflush(stdin);gets(glostu[a].name);Print_AddInfo();
	 	    scanf("%d %d %lf %lf %lf",&glostu[a].sex,&glostu[a].cla,&glostu[a].chinese,&glostu[a].math,&glostu[a].english);
	 	    printf("\n|-------------------------------------------------------------------------|\n");
		    printf("|%-10s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|\n","NUMBER","NAME","SEX","CLASS","CHINESE","MATHE","ENGLISH","TOTAL"); 
		    printf("|----------+--------+--------+--------+--------+--------+--------+--------|\n");
    	    printf("|%-10d|%-8s|%-8d|%-8d|%-8.1lf|%-8.1lf|%-8.1lf|%-8.1lf|\n",glostu[a].num,glostu[a].name,glostu[a].sex,glostu[a].cla,glostu[a].chinese,glostu[a].math,glostu[a].english,glostu[a].total);
		    printf("|-------------------------------------------------------------------------|\n");
	 	    Writedata();break;
		}
	}
	if(a>glonum-1)
	{
		char swe[100]=" !Warning,there are no student which you input!";
		Warn_Handle(swe);goto EXC_LABEL1;
	}
	printf("Do you want to continue exchange.(0=No,1=Yes)\n>");fflush(stdin);
	int yp;scanf("%d",&yp);
	if(yp) goto EXC_LABEL1;
	
}
int main(int argc,char **argv)
{
    //There are 3 arguments,also it can receive no commandline argument.
    //Argument1:number of buisness.
    //Argument2:string of students' information.(items linked by '-')
    //Argument3:reserved paramenter.
    system("chcp 437>nul");
    GetColor();
    thread Muti_Th(Muti_Thread_titleTime);
    while(Login());
    glonum=Readdata();
    Print_Welcome();
    while(1)
    {
    	 system("cls");Print_Welcome();
    	 fflush(stdin);
    	 int selection;scanf("%d",&selection);
    	 Welcome(selection);
    }
    Muti_Th.join();
    return 0;
 }
//End of Source Code of Students Information Manage System.
//Copyright (c) 2021 Qilu University of Technology Class of software Engineer(Software Development) 21-1 Duyu.
