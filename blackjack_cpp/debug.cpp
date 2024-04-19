#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

void replay(char &ans);     //allows replay of game
void hit(int &total);       //take another card
void deal(int &player,int &cpu,int &playerturns,int &cputurns); //deals hand
void BET(int &bet,int &money);  //takes bet
void print(int wins,int lose,int draw,int money); //prints final score
void results(int player,int cpu,int bet,int &money,int &draw,int &win,int &lose); //finds winner
int random(long hi,long lo);


/// @brief 
/// @return 
int main()
{

    //Initialize variants
    int player=0, cpu=0, win=0, lose=0, draw=0, playerturns=0, cputurns=0, money=0, bet;
	char ans;

	//system("cls");
	cout << "WOULD YOU LIKE TO PLAY :";
	cin >> ans;

    
    if((ans == 'y')||(ans=='Y')) //Checks to see if they want to play...
	{
		cout << "\t\t\tI WILL LET YOU START WITH $100" <<endl; //starts u with money
		money = 100;
		cout << "\t\t\t";
	}
	else
	{
		return(0);
	}


	do{
		system("cls");
		if(money < 0)
		{
	    	cout<<"You're broke"<<endl; 
			return(0);
		}
        BET(bet,money); //calls bet fuction
     	deal(player,cpu,playerturns,cputurns); //Deals teh cards

	    do{	
        	cout << "Would You Like To Hit or Stay :"; //ask user if the want a hit
	    	cin >> ans;
        	if((ans=='h')||(ans=='H'))
			{
				playerturns++; //adds one to players total cards
				if(playerturns>5) //sees if player can take a card
				{
		    		cout << "You Can't Have more than 5 cards";
			   
				}
			
			}
		    if((playerturns < 6)&&(ans == 'h')) //sees if the coumputer can take a card
			{
	            cout << endl;
			    hit(player);  
			}
		    }while((ans=='h')||(ans=='H'));  //Takes value for hit or stay


        //Tells the cpu wither to take a card or not
	    for(;(cpu<16)&&(cputurns<6);cputurns++){
		    cout<<endl;
		    cout<<"\t\t\tThe Dealer Takes A Card"<<endl;
		    hit(cpu); //calls hit function
	        }

	    cout<<endl;
	    cout<<endl;
	    cout<<"\t\t\tThe Dealer Has A Total:"<<cpu<<endl; //displays dealers total and then yours
	    cout<<"\t\t\tYou Have A Total Of:"<<player<<endl;
        cout<<endl;
	    results(player,cpu,bet,money,draw,win,lose); //send data to function to tell if you won our not
	    replay(ans);
	    }while((ans=='y')||(ans=='Y'));

    
	print(win,lose,draw,money);
	cout<<endl;
	cout<<"\t\t\t\t";
	return(0);
}

int random(long hi,long lo)
//This Program Finds A Random Number Between Hi and Low
{
        int ran;
        srand((unsigned)time(NULL));
        ran=rand()%(hi-(lo-1))+lo;
        return(ran);
}


void BET(int &bet,int &money)
//This Function finds out how much money they wish to bet;
{
	system("cls");
	cout<<"\t\t\tYOU HAVE :$"<<money<<endl;
	cout<<"\t\t\tHow Much Do You Wish To Bet: ";
	cin >> bet;
    if(bet<0){
        bet=bet*-1;
    }
	money=money-bet;
}

//----------------------------------------------------------------------------------------
void deal(int &player,int &cpu,int &playerturns,int &cputurns)
//This Function Deals The hands
{
	int playercard1,playercard2,cpucard1,cpucard2;
	playerturns=2;
	cputurns=2;
	playercard1=random(13,1);
	cout<<"DEALING HAND"<<endl;
	playercard2=random(13,1);
    cpucard1=random(13,1);
	
	cpucard2=random(13,1);
	if(playercard1>=10)
	{
		playercard1=10;
	}
	if(playercard2>=10)
	{
		playercard2=10;
	}
	if(cpucard1>=10)
	{
		cpucard1=10;
	}
	if(cpucard2>=10)
	{
		cpucard2=10;
	}
player=playercard1+playercard2;
cpu=cpucard1+cpucard2;
cout<<"\t\t\tYOU HAVE a total of :"<<player<<endl;
cout<<"["<<playercard1<<"]";
cout<<"["<<playercard2<<"]";
cout<<endl;
cout<<"\t\t\tThe DEALER HAS A "<<cpucard1<<" SHOWING"<<endl;
cout<<endl;
cout<<"[*] "<<" ["<<cpucard1<<"]";
}    

//----------------------------------------------------------------------------------------
void hit(int &total)
//This fuction is to deal a card and add it to the total
{
	int card;
	card=random(13,1);
	if(card>=10)
	{
		card=10;
	}
	total=total+card;
	cout<<"\t\t\tThe card is a :"<<card<<endl;
    cout<<"\t\t\tTotal is :"<<total<<endl;
}
//-----------------------------------------------------------------
void results(int player,int cpu,int bet,int &money,int &draw,int &win,int &lose)
//this function finds who wins 
{
if(cpu==player)
	{
	cout<<"\t\t\tIT WAS A DRAW HOUSE WINS"<<endl;
		draw++;    
	}
	if(player>21)
	{
	cout<<"\t\t\tYou Bust"<<endl;
		lose++;
	}
	else
	{
	    if(cpu<player)
		{
			cout<<"\n\t\t\tYOU WIN";
		    money=money+(bet*2);
        	win++;	
		}
	}
	if(cpu>21)
	{
		cout<<"\t\t\tDealer Bust"<<endl;
		
		if(player<21)
		{
			cout<<"\n\t\t\tYOU WIN";
			win++;
			money=money+(bet*2);
		}
	}
	else
	{
    	if(cpu>player)
		{
			cout<<"\t\t\tYOU LOSE"<<endl;
    		lose++;
		}
	}
}
//-----------------------------------------------------------------
void replay(char &ans)
{
	cout<<"\n\t\t\tWould You Like To Play This Game Again :";
	cin>>ans;
}
//-----------------------------------------------------------------
void print(int wins,int lose,int draw,int money)
{
	cout<<"\t\t\t\tWINS :"<<wins<<endl;
	cout<<"\t\t\t\tLOSE :"<<lose<<endl;
	cout<<"\t\t\t\tDRAWS :"<<draw<<endl;
	cout<<"\t\t\t\tMONEY :"<<money<<endl;
}