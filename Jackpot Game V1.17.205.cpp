#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <string>

using namespace std;

int life_remain,secret_number,maxrand,temp_life,text_temp;
int x,mins=2147483647,maxs=0;
int level,ispre=0,debug=0;                        								//Version
string pre="1.0",ver="1.17.205";                  								//Version
string preview="...";                             								// Preview Detail
char choice;
char highcontinue;

int init();
void start();
void again();
void quit();
int test(int num);


int main(){
    system("@echo off");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    system("title Jackpot Game V1.17.205");                 //Version
    cout << "**              Jackpot Game           **\n";
    if(!ispre){
    	cout << "*        \033[3mVersion "<<ver<<"-stable";
		cout<<"\033[0m";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		cout<<"        *\n";
	}
    else{
    	cout << "*    Version "<<ver<<" pre-"<<pre<<"    *\n";
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
    	cout<<"Preview details: "<<preview<<endl;
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
		cout<<"Preview program is unstable, so please use it carefully."<<endl;
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
    cout << "The goal of this game is to guess a number.\n";
    cout << "Jackpot will tell you if the number is (too) big or (too)\n";
    cout << "small compared to the secret number to find.\n";

    if(init()==0)
        start();
    return 0;
}

int init(){
	highcontinue='n';
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << "Set defficluty mode\n1: 0~100\n2: 0~200\n3: 0~300\nect.\n";
    cout << "or press -1 to quit\n>>";
    cin>>level;
    if(!test(level)) {
        cout<<"Something went wrong...\nNow exiting...";
        Sleep(1500);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		exit(0);
	}
    else if(level==-1){
    quit();
    return 1;
    }
    else if(level>=20000&&level<=2000000){
    	cout<<"The level is too high!\nCountinue?";
    	cin>>highcontinue;
    	if(!(highcontinue=='y'||highcontinue=='Y')){
    		cout<<"Input again then. :)\n";
    		Sleep(1500);
    		system("cls");
    		init();
		}
	}
	else if(level >200000){
		cout<<"Too high!";
		Sleep(1500);
		system("cls");
		exit(0);
	}
    maxrand=level*100;
    mins=maxrand;
    if(level<=100)
        life_remain=10;
    else
        life_remain=15;
    temp_life=life_remain;
    srand((unsigned)time(NULL));
    secret_number = rand() % maxrand;
    system("cls");
    return 0;
}

void start(){
	if(debug)
		secret_number=50;                  												  //Just for test.
    while(life_remain>=1){
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        cout<<"Type a number between "<<maxs<<" and "<<mins<<" ."<<"\nLifes remaining:";
        if(life_remain>=7)
    		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
		else if(life_remain>=3)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
		else
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
		cout<<life_remain;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		cout<<"\n>>";
        cin>>x;
        if(!test(x)){
        	cout<<"Warn:Input error, now exiting...";
   			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    		Sleep(1500);
        	exit(0);
        }
        
        if(x >= mins){
        	cout<<"Did you type a number more or equal than "<<mins<<"?"<<endl<<"You can try to input a number less than "<<mins<<",refreshing...";
        	Sleep(1500);
			system("cls");
			continue;
		}
		else if(x <= maxs){
        	cout<<"Did you type a number less or equal than "<<maxs<<"?"<<endl<<"You can try to input a number more than "<<maxs<<",refreshing...";
        	Sleep(1500);
			system("cls");
			continue;
		}
        
        if(x <= maxrand){
            if(x>secret_number){
            	if(x-secret_number>=250) 
                	cout<<x<<" is too bigger than the secret number";
                else
                	cout<<x<<" is bigger than the secret number";
                if(x<mins){
                    mins=x;
                }
                if(life_remain!=1)
                    cout<<",try again.";
                else
                	cout<<". You don't have any more life left :)";
             Sleep(3000);
            }
            else if(x<secret_number){
            	if(x-secret_number<=-250)
                	cout<<x<<" is too smaller than the secret number";
                else
                	cout<<x<<" is smaller than the secret number";
                if(x>maxs){
                    maxs=x;
                }
                if(life_remain!=1)
                    cout<<",try again.";
                else
                	cout<<". You don't have any more life left :)";
             Sleep(3000);
            }
            else{
    			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);
                cout<<"Congratulation!\nYou win!\nThe secret number is "<<secret_number<<" !";
                cout<<"\n\033[5m\033[7mYou spent "<<temp_life-life_remain<<" times to guess the secret number!";
                if(temp_life-life_remain<=3){
                	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                	cout<<"\nWait, You just spent 3 or less time(s) to find out the secret number?"<<endl;
					cout<<"\033[5m\033[7mYou are so lucky!";
				}
                Sleep(6000);
                again();
                return ;
            }
            life_remain--;
            system("cls");
        }
    }
    if(life_remain==0){
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
        cout<<"Oh!\nYou lose!\nThe secret number is "<<secret_number<<" !";
        again();
    }
}

void again(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
    cout<<"\n-----------------------------------------";
    cout<<"\nDo you want to play it again?(Y/N)\n>>";
    cin>>choice;
    if(choice=='Y'||choice=='y'){
        system("cls");
        maxs=0;
        main();
    }
    else if(choice=='N'||choice=='n'){
        quit();
    }
    else{
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
        cout<<"Input wrong...\nTry it again.";
        Sleep(1500);
        system("cls");
        again();
    }
}

void quit(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
    cout<<"\n\nThank you playing this \"boring\" game.";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
    cout<<"\nMade by Chidc.";
    Sleep(1500);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    Sleep(1500);
    exit(0);
    return ;
}

int test(int num){
    if((num<=0||num>2147483647)&&num!=-1){
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
    	system("cls");
        return 0;
    }
    return 1;
}
