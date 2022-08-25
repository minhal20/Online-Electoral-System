#include <Stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <time.h>


void display();
void clrscr();
void admin_panel();
void admin_panelchoice(int );
void password(char *,int );					/*Input Masking of Password*/
void storevote(long int );
void store_userdata(long int ,char [],int);
void voter_panel();
void signin();
void signup();
void incorrect_formatid();					/*If "id" inputted in the wrong format,prompts Voter to either sign up again or exit*/

/*for Admin Access*/
#define adminid 12349876
#define adminpass   "22334455"


int main()
{
	display();
	clrscr();
 	system("COLOR 75");
 	
	int choice;
	char pass[8];
	long int id;
	
	printf("      ONLINE ELECTORAL SYSTEM\n");
	printf("\t1.Login as Admin\n");
	printf("\t2.Login as Voter\n");
	printf("\nEnter your choice : ");
	scanf("%d",&choice);							                    
	
	/*Logging in as Admin or Voter*/
	if (choice==1){
		
		printf("Enter Admin ID: ");
		scanf("%d",&id);
		printf("Enter password:");
		fflush(stdin);
		gets(pass);
		
		if(id==adminid){
			if(strcmp(pass,adminpass)==0){
				printf("Logged in successfully!\n");
				clrscr();
				admin_panel();
			}
			else
				printf("\nIncorrect pw");
		}
		
		else
			printf("Access denied!!");
	}
	
	else if (choice==2){
		clrscr();
		voter_panel();
	}
	else
		printf("Incorrect option selected");
	
	return 0;
}


/*clearing the screen*/
void clrscr(){
    system("@cls||clear");
}

/*Admin Panel will be loaded on the console*/
void admin_panel(){
	int choice1;
	
	printf("\t\t\tTHIS IS ADMIN PANEL\n");
	printf("\nSelect one of the options\n\n");
	printf("1.Display all Data");
	printf("\n2.Display Voters' Data");
	printf("\n3.Voters of a certain candidate");
	printf("\n4.Display Winning Candidate\n");
	scanf("%d",&choice1);
	
	if((choice1==1)||(choice1==2)||(choice1==3)||(choice1==4))
	{
		clrscr();
		admin_panelchoice(choice1);
	}
	else
		printf("\nIncorrect Choice!!");
}

/*THE Choices in Admin Panel*/
void admin_panelchoice(int choice){
	
	FILE *fp;
	struct voter{
		long int id;
		int code;		
	};
	struct voter Voter[200];
	int i=0,count=0,j,Code,max=0,k;
	int candidate[5][2]={{1200,0},{2222,0},{1222,0},{9000,0},{8999,0}};
	
	fp=fopen("Votes.txt","r");
	if (fp==NULL){
		printf("Cannot open the target file");
		exit(1);
	}
	
	while(fscanf(fp,"%d\t%d",&Voter[i].id,&Voter[i].code)!=EOF) {					/*Reading and storing the id of voter and code of the candidate*/
		 i++;
		 count++;
	}
	fclose(fp);

	/*Calculating Votes for every candidate*/
	for(i=0;i<count;i++){
			
		if (Voter[i].code==1200)
			candidate[0][1]+=1;
		else if (Voter[i].code==1222)
			candidate[2][1]+=1;
		else if (Voter[i].code==2222)
			candidate[1][1]+=1;
		else if (Voter[i].code==9000)
			candidate[3][1]+=1;
		else if (Voter[i].code==8999)
			candidate[4][1]+=1;
			
	}
	
	
	/*Displaying data according to Admin's Choice*/
	switch(choice){
		case 1:
		{
		/*Displaying votes of all Voters*/
			printf("*******VOTING DATA****************************************************************\n\n");
			for(i=0;i<count;i++){
				printf("ID: %d\t",Voter[i].id);
				printf("CODE: %d\n",Voter[i].code);
			}
			break;
		}
		case 2:
		{
		/*	Displaying Candidates data*/
			printf("\n********************Displaying the Candidates voting Status***********************\n\n");
			printf("\n\t\tCode    \t\tVotes\n");
			for (i=0;i<5;i++){
				for(j=0;j<2;j++){
					printf("\t\t%d    ",candidate[i][j]);
				}
				printf("\n");
			}
			break;
		}
		case 3:
		{
		/*Voters of a certain candidate*/
			printf("(1222)- Mark John");
			printf("\n(1200)-Johny Bravo");
			printf("\n(8999)-Mickey Mouse");
			printf("\n(9000)-Morris Feliks");
			printf("\n(2222)-Adam Blake\n");
			
			printf("Enter the code of the Candidate whose list of voters you want :");
			scanf("%d",&Code);
			printf("\n");
			if ((Code==1200)||(Code==1222)||(Code==2222)||(Code==9000)||(Code==8999)){
				for(i=0;i<count;i++){
					if (Voter[i].code==Code)
						printf("%d\n",Voter[i].id);
				}
			}
			else
				printf("Incorrect Code Entered!");
			break;
		}
		case 4:
		{
		/*Print the winning candidate*/
			for(i=0;i<5;i++){
				if(candidate[i][1]>max){
					max=candidate[i][1];
					k=candidate[i][0];				      	/*Winning Candidate*/
				}
			}
			printf("The winning Candidate is : %d",k);
			break;
		}
		default :
		{
			printf("Incorrect choice!!");	
			break;
		}
		
	}	
		
}


/*Voter Panel*/
void voter_panel(){
	int choice2;
	
	printf("\t\tLOGGED IN AS VERIFIED VOTER !!\n\n(NOTE:you can vote only once ..Choose wisely)\n");
	printf("\nEnter '1' to SIGN IN\nEnter '2' to SIGN UP\n");
	scanf("%d",&choice2);
	if (choice2==1){
		clrscr();
		signin();
	}
	else if (choice2==2){
		signup();
	}
	else
		printf("\nIncorrect option Selected!");
		
}


/*When Voter wants to sign in */
void signin(){

	FILE *fp,*FP2;
	struct voter{
		char password[10];
		long int id;
	};
	struct voter Voter[200];
	int i=0,count=0,n=0,found,voted;
	long int id;
	char pw[10];
	long int ID;
	int code;
	printf("\t\tWelcome to SIGN-IN PAGE\t\t\n\n\n");
	printf("Enter ID: ");
	scanf("%d",&id);
	
	printf("Enter password : ");
	fflush(stdin);
	
	password(&pw[0],10);											/*Input masking of password*/

	fp=fopen("userdata.txt","r");									/*To load the user database from the file "userdata.txt" into memory */
	if (fp==NULL){
		printf("Cannot open the target file");
		exit(1);
	}
	while(fscanf(fp,"%d\t%s",&Voter[i].id,&Voter[i].password)!=EOF) {
		 i++;
		 count++;
	}
	fclose(fp);
	for(i=0;i<count;i++){											/*To verify the sign in of user*/
		if(Voter[i].id==id){
			printf("\nID FOUND\n");
			if (strcmp(Voter[i].password,pw)==0){
				printf("\nSIGN IN SUCCESSFUL!!");
				FP2=fopen("Votes.txt","r");							/*To check if Voter has already voted from the files "Votes.txt" */
				
				if (FP2==NULL){
					printf("Cannot open the target file");
					exit(2);
				}
				
				while(fscanf(FP2,"%d\t%d",&ID,&code)!=EOF) {
					
					if (ID==Voter[i].id){
						printf("\nYou have already Voted!!\n");
						printf("\nThe person you voted for is : %d",code);
						voted=1;
						break;
					}
					else;
						voted=0;
				}
				fclose(FP2);
			
				if (voted==0){										/*If the user has not voted yet ,ask for vote and store the details*/
					
					storevote(Voter[i].id);
				}
				found=0;
				break;
			}
		}
		else 
			found=1;			
	}
	if (found==1)
		printf("ID OR PW WRONG");
}


/*When Voter selects to Sign up*/
void signup(){
	
	struct voter{
		char password[10];
		long int id;	
	};
	struct voter Voter;
	int i=1,count=0,VoteCode,confirmation;
	char code[4],answer,pass[10];	
	
	
	int x=10,y=0;
	
	
	clrscr();
	printf("\t\tWelcome to SIGN UP PAGE\t\t\n\n\n");
	printf("Enter ID(8 digits only)(100000000):");
	scanf("%d",&Voter.id);
	
	if (((double)Voter.id/10000000!=(double)0)&&((double)Voter.id/10000000<(double)10)){
		if((double)Voter.id<=(double)99999999){
			printf("Enter the 4 digit verification code :");
			fflush(stdin);
			gets(code);
			
			if((strcmp(code,"c111")==0)||(strcmp(code,"C111")==0)){
				
				printf("Enter the password(max 10 digits) : ");
				fflush(stdin);
				gets(Voter.password);
				
				printf("Re-Enter your password: ");
				fflush(stdin);
				gets(pass);
				
				
				if (strcmp(pass,Voter.password)==0){
					
					store_userdata(Voter.id,Voter.password,10);				/*Stores user's data into the file*/
					printf("Do you want to vote right now(Y/N)? ");
					answer=getch();
					
					if((answer=='y')||(answer=='Y')){
						storevote(Voter.id);								/*Store votes if user wants to vote while signing up*/
					}	
					else if ((answer=='n')||(answer=='N'))
						exit(3);
					else 
						printf("\nError:Sorry cannot update the contents!");
				}
				
			}
			else
				printf("\nIncorrect Code!!");
		}
		
		else
		{
			printf("ID entered in incorrect format!");
			incorrect_formatid();								/*Prompt to sign up again or end the program*/
		}
	}
	else if(((double)Voter.id/10000000>10)) {
		printf("ID entered in incorrect format!");
		incorrect_formatid();									/*Prompt to sign up again or end the program*/						
	}
}



void incorrect_formatid(){
	
	char answer;
	
	printf("\nDo you want to try again(Y/N)? ");
	answer=getch();
	if((answer=='y')||(answer=='Y')){
		signup();						         /*If user wants to sign up again */
	}
	else if ((answer=='n')||(answer=='N'))
		exit(4);
	else {
		printf("\nError:Sorry cannot update the contents!");
		exit(4);
	}
}



void store_userdata(long int id,char pass[],int n){
	FILE *fp;
	int i=2;
	
	fp=fopen("userdata.txt","a");
	if (fp==NULL){
		printf("Cannot open the target file");
		exit(1);
	}
	
	while(i>0){
		fflush(stdin);
		fprintf(fp,"%d\t%s\n",id,pass);			/*writing into the file "Userdata.txt" */
		break;
	}
	
	printf("\nData updated!\n");
	fclose(fp);
}


/*function for input masking of paragraph with character '*'  */
void password(char *pw,int count){
	int k=0;
	char c;
	
	do{
		c=getch();
		if (c!='\r'){
			*(pw+k)=c;
			printf("*");
			k++;	
		}
		else if (c==13){
			*(pw+k)='\0';
			break;
		}
			
	}while(k<(count+1));
	
}


void storevote(long int id){
	int i=2;
	printf("(Note:You can only vote once !)\n");
	FILE *FP3;
	int code,choice;
	
	FP3=fopen("Votes.txt","a");
	if (FP3==NULL){
		printf("Cannot open the target file");
		exit(3);
	}
	
	do{
		printf("\nEnter the candidate you want to vote for (1222/8999/9000/1200/2222) :\n");
		printf("(1222)- Mark John");
		printf("\n(1200)-Johny Bravo");
		printf("\n(8999)-Mickey Mouse");
		printf("\n(9000)-Morris Feliks");
		printf("\n(2222)-Adam Blake\n");
		scanf("%d",&code);
		
		if (code==1222||code==1200||code==8999||code==9000||code==2222){
			printf("\nEnter '1' to confirm\nEnter '2' to Vote again\n");
			scanf("%d",&choice);	
			i=2;
			
		}
		else{
			choice=2;
			i=0;
			printf("\nChoose again!!!");
		}
	}while((choice!=1)&&(choice==2));
	
	while(i>0){
		fprintf(FP3,"%d\t%d\n",id,code);						/*Writing the contents into the file*/
		break;
	}
	fclose(FP3);
}


/*Color definitions for console background*/

#define BLUE    "\x1b[34m"
#define CYAN    "\x1b[36m"

///////////////////////////////////////////////////////////////////////////////////////////////
void display()
{	
	
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	system("COLOR 7F");
	printf("\a\a");
	printf("\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t");
	printf(CYAN"\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2"BLUE);
	printf(CYAN"\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2"BLUE);
	printf(CYAN"\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf(CYAN"\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE"\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE"\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE"\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE"\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE"\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE"\n\t\t\t\t\xB3\xB3                	''  W E L C O M E  ''                  \t\xB3\xB3");
	printf(BLUE"\n\t\t\t\t\xB3\xB3                      	                               \t\xB3\xB3");
	printf(BLUE"\n\t\t\t\t\xB3\xB3                 	    '' T O ''                       \t\xB3\xB3");
	printf(BLUE"\n\t\t\t\t\xB3\xB3                  	                                  \t\xB3\xB3");
	printf(BLUE"\n\t\t\t\t\xB3\xB3                 	'' O N L I N E ''     	        \t\xB3\xB3");
	printf(BLUE"\n\t\t\t\t\xB3\xB3                      	                             \t\xB3\xB3");
	printf(BLUE"\n\t\t\t\t\xB3\xB3                     ''E L E C T O R A L''               \t\xB3\xB3");
	printf(BLUE"\n\t\t\t\t\xB3\xB3                  	                                  \t\xB3\xB3");
	printf(BLUE"\n\t\t\t\t\xB3\xB3                	''  S Y S T E M ''                     \t\xB3\xB3");
	printf(BLUE"\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE"\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE"\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE"\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE"\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(CYAN"\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf(CYAN"\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf(CYAN"\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf(CYAN"\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2"BLUE);

	sleep(1);
	system("cls");
		
	printf("\n\n\n");
	printf("**********************************************************ONLINE ELECTORAL SYSTEM FOR AREA XYZ*********************************************************************");
	
	sleep(3);
	system("cls");
}
