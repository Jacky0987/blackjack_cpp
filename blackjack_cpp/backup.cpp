#include <time.h>
#include <stdio.h>
void wait(int milli)
{
clock_t start;
start=clock();
while( ( clock()-start ) < milli )
;
}
//wait.h end
//utility.h begin
//Isaac Shaffer    
//Utility Libray
// void Pause(),int GetInt(int L,int H),void signature(), int random(long hi, long lo)
#include<iostream.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
//=========================================================
void pause()
//displays a message and waits for the user to hit a key
{
        cout<<"Press Any Key To Continue"<<endl;
        getch();
}
//=========================================================
int GetInt(int L=0,int H=100)
{
        int ent;
        cout<<"Please Enter A Number Between "<<L<<" and "<<H<<endl;
        cin>>ent;
        while((ent<L)||(ent>H))
        {
                cout<<"Error"<<endl;
                cout<<"Value must be between "<<L<< " and "<<H<<endl;
                cin>>ent;
        }
        return(ent);
}
//==========================================================
void sign()
//Displays ISAAC SHAFFER
{
        cout<<"This Program Was Written By Isaac Shaffer"<<endl;
}
//=============================================================
int random(long hi,long lo)
//This Program Finds A Random Number Between Hi and Low
{
        int ran;
        srand((unsigned)time(NULL));
        ran=rand()%(hi-(lo-1))+lo;
        return(ran);
}
//utility.h end
//ISAAC SHAFFER
//3-2-2000
//BLACKJACK GAME WITH FUNCTIONS
//THIS PROGRAM IS MENT TO BE A SIMPLE BLACK JACK GAME 
//since i can't use gotoxy i used the slash t to space my program
//notes
//cpu is used to refer to the coumputer
//librays
#include<iostream.h>
#include<stdlib.h>
#include "utility.h"
#include  "wait.h"
//fuctions
void replay(char &ans);     //allows replay of game
void hit(int &total);       //take another card
void deal(int &player,int &cpu,int &playerturns,int &cputurns); //deals hand
void BET(int &bet,int &money);  //takes bet
void print(int wins,int lose,int draw,int money); //prints final score
void rules(); //shows rules
void results(int player,int cpu,int bet,int &money,int &draw,int &win,int &lose); //finds winner
int main()
{
    int player=0,cpu=0,win=0,lose=0,draw=0,playerturns=0,cputurns=0,money=0,bet;
    char ans;
    system("cls"); //执行系统命令 cls
    rules();
    cout<<"\t\t\tWOULD YOU LIKE TO PLAY :";
    cin>>ans;
    if((ans == 'y')||(ans=='Y')) //checks to see they want to play
    {
        cout<<"\t\t\tI WILL LET YOU START WITH $100"<<endl; //starts u with money
        money=100;
        cout<<"\t\t\t";
        pause();
    }
    else
    {
        return(0);
    }
    do{
        system("cls");
        if(money<0) //sees if your broke
        {
            cout<<"Your broke"<<endl; //sees if your broke
            return(0);
        }
        BET(bet,money); //calls bet fuction
         deal(player,cpu,playerturns,cputurns); //Deals teh cards
    do{    
            cout<<"\t\t\tWould You Like To Hit or Stay :"; //ask user if the want a hit
            cin>>ans;
            if((ans=='h')||(ans=='H'))
            {
                playerturns++; //adds one to players total cards
                if(playerturns>5) //sees if player can take a card
                {
                    cout<<"\t\t\tYou Can't Have more than 5 cards";
               
                }
            
            }
            if((playerturns<6)&&(ans=='h')) //sees if the coumputer can take a card
            {
               cout<<endl;
            hit(player);  //calls hit function
            }
        }while((ans=='h')||(ans=='H'));  //Takes value for hit or stay
    for(;(cpu<16)&&(cputurns<6);cputurns++)   //Tells the cpu wither to take a card or not
    {
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
//---------------------------------------------------------------------------------------
void rules()
//This Function Displays the rules for Black Jack
{
cout<<"\t\t WELCOME TO ISAAC SHAFFER'S BLACK JACK GAME"<<endl;
    cout<<"\t\t\t HERE ARE SOME SIMPLE RULES"<<endl;
    cout<<"\t\t\t1:You Can only have a max of 5 cards."<<endl;
    cout<<"\t\t\t2:If you bust you automatically lose."<<endl;
    cout<<"\t\t\t3:If you win you win double what you bet."<<endl;
    cout<<"\t\t\t4:The Dealer stops at or after 16."<<endl;
    cout<<"\t\t\t\t";
    pause();
}
//----------------------------------------------------------------------------------------
void BET(int &bet,int &money)
//This Function finds out how much money they wish to bet;
{
    system("cls");
    cout<<"\t\t\tYOU HAVE :$"<<money<<endl;
    cout<<"\t\t\tHow Much Do You Wish To Bet: ";
    cin>>bet;
       if(bet<0)
        {
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
    cout<<"\n\t\t\tDEALING HAND"<<endl;
wait(350);
    playercard2=random(13,1);
    wait(150);
    cpucard1=random(13,1);
    
    wait(350);
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
--------------------------------------------------------
作者：程浩
链接：https://wenku.baidu.com/view/cd58d383ec3a87c24028c459.html
来源：百度文库
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
