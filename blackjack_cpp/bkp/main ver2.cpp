//SuperJacky6 @ ByteDance Tiktok Algorithm Dep.
//Under GPT-v3 License Redesigned and refined.

//Contact : adding2003@gmail.com

#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <conio.h>
#include <time.h>

using namespace std;


//游戏内容设定函数声明
void replay(char &ans);     //allows replay of game
void setting(int chips);	//jump into settings menu.
//游戏主要内容操作函数设定
void hit(int &total, int &flag_legal, int &playerturns);      //take another card
int cpu_hit(int &total, int &cputurns);
void deal(int &player, int &cpu, int &playerturns, int &cputurns); //deals hand
void BET(int &bet, int &money); //takes bet
//游戏判断与打印函数设定
int judging21(int a);
void print(int wins, int lose, int draw, int money); //prints final score
void results(int player, int cpu, int bet, int &money, int &draw, int &win, int &lose); //finds winner
//游戏数学与计算机机制函数声明
int random(long hi, long lo); //random function using time stamp.
void wait(int milli);
void pause();


/*
未完成任务列表：

1.H键超级管理员设定。（菜单分类化与模块化调用(或许程序拆分？)）
	菜单问题选择拆分程序。
	游戏内容问题仿照cpu_hit与hit函数分别设定。
2.大于10的点数改为0.5判断。
	全程序关于player和cpu的浮点属性修改。
3.要牌后的赔率multiplier的设定。
	暂未实现，需要更新筹码溢出的判断与加减方式。
4.模拟图形化Graphic User Interface的实现。
5.规则阐述与作者声明函数的实现。
	void function game_rules();
	void function game_author();
6.相同数字手牌的Split操作与函数实现。（非必须）


已完成任务列表:

1.主程序的实现、改写与主程序封装。
2.13张扑克牌大于10的判定为10（若需要改成0.5则有浮点数要求）
3.CPU方永远不会爆庄。(2.3.3-3)
4.筹码的数量判断设定与报错。
5.中文本地化21点程序内容。

已知BUG列表：

1.程序内对于非法操作的判定仍是使用玩家手数，flag_legal未彻底使用。
2.手牌有极大可能相同。
	原因：random函数在传入时间戳的时候同时执行则获得同样数字。
	部分解决方案：更改13/10，用sleep延迟时间戳传入。
3.筹码溢出问题。
	已部分解决。
4.输入内容的检索问题。
5.CPU在已经超数的情况下会继续获取牌的bug
	已解决，函数改int增加返回与多层判定。
*/


int main() {

	//Initialize variants
	int player = 0, cpu = 0, win = 0, lose = 0, draw = 0, playerturns = 0, cputurns = 0, money = 0, bet;
	int flag_legal = 1, flag = 0;
	char ans;

	//system("cls");
	cout << "BLACKJACK GAME" << endl;
	cout << "是否开始游戏？(Y/n)";

	cin >> ans;

	if ((ans == 'y') || (ans == 'Y')) { //Checks to see if they want to play...
		system("cls");
		cout << "您初始拥有的筹码为 $ " << money << endl; //starts u with money
		money = 1000;
	} else {
		return (0);
	}


	do {
		system("cls");
		if (money <= 0) {
			cout << "您破产了！" << endl;
			return (0);
			break;
		}
		BET(bet, money); //calls bet fuction
		deal(player, cpu, playerturns, cputurns); //Deals the cards

		do {
			cout << "您是否要继续拿牌？(H/s)"; //ask user if the want a hit
			cin >> ans;
			if ((ans == 'h') || (ans == 'H')) {
				playerturns++; //adds one to players total cards
				if (playerturns > 5) { //sees if player can take a card
					cout << "操作非法！" << endl;;
				}
			}
			if ((playerturns < 6) && (ans == 'h' ) ) {
				//sees if the coumputer can take a card
				hit(player, flag_legal, playerturns);
			}
		} while ((ans == 'h') || (ans == 'H')); //Takes value for hit or stay


		//Tells the cpu wither to take a card or not
		for (; (cpu < 16) && (cputurns < 6); cputurns++) {
			cout << endl;
			cout << "CPU正在进行思考" << endl;
			wait(600);
			cpu_hit(cpu, cputurns);
			//calls hit function
		}
		cout << endl;
		cout << "CPU的总数:" << cpu << endl; //displays dealers total and then yours
		cout << "您的总数:" << player << endl;
		cout << endl;
		results(player, cpu, bet, money, draw, win, lose); //send data to function to tell if you won our not
		replay(ans);
	} while ((ans == 'y') || (ans == 'Y'));

	print(win, lose, draw, money);
	return (0);
}

/* void setting(int chips) {
	money = chips;
	cout << "New chips setting applied. New chips" << chips << endl;
}*/

int random(long hi, long lo) {
	time_t t;
	int ran;
	srand((unsigned) time(&t));
	ran = rand() % (hi - (lo - 1)) + lo;
	return (ran);
}


void BET(int &bet, int &money)

//This Function finds out how much money they wish to bet;
{
	cout << "您拥有筹码 $" << money << endl;
	cout << "您想下注多少 $ ？ ";
	cin >> bet;

	if (money - bet < 0) {
		cout << "您所输入的数字超过了您所拥有的筹码，请重试" << endl;
		BET(bet, money);
		//使用重复调用解决筹码溢出问题
	} else {
		money = money - bet;
	}
}


void deal(int &player, int &cpu, int &playerturns, int &cputurns) {
	int playercard1, playercard2, cpucard1, cpucard2;
	cout << "轻触回车键开始发牌！" << endl;
	pause();

	playerturns = 2;
	cputurns = 2;

	playercard1 = random(13, 1);
	wait(250);
	playercard2 = random(13, 1);
	wait(150);
	cpucard1 = random(13, 1);
	wait(350);
	cpucard2 = random(13, 1);
	//实现伪随机数的random函数保证单次调用的差异性
	if (playercard1 >= 10) {
		playercard1 = 10;
	}

	if (playercard2 >= 10) {
		playercard2 = 10;
	}

	if (cpucard1 >= 10) {
		cpucard1 = 10;
	}

	if (cpucard2 >= 10) {
		cpucard2 = 10;
	}

	player = playercard1 + playercard2;
	cpu = cpucard1 + cpucard2;
	cout << "您的牌总和为" << player << endl;
	cout << "[" << playercard1 << "]";
	cout << "[" << playercard2 << "]";
	cout << endl;
	cout << "CPU的其中一张牌为:" << cpucard1 << endl;
	cout << "详细牌点为：" << endl;
	cout << "[*]" << "[" << cpucard1 << "]" << endl;
}

int cpu_hit(int &total, int &cputurns) {
	int card;
	card = random(13, 1);

	if (card >= 10) {
		card = 10;
	}
	//修复了CPU在已经超数的情况下会继续获取牌的bug。
	if ( total + card > 21 ) {
		// Stop hitting cards and undo the event.
		cout << "CPU选择不获取新牌，总点数为" << total << endl;
		return 0;
	} else {
		total = total + card;
		cout << "CPU选择获取新牌" << endl;
		cout << "此时CPU的新牌点总数为 " << total << endl;
		return 1;
	}

}

int judging21(int a) {
	if (a > 21) {
		return 0;
	} else {
		return 1;
	}
}

void hit(int &total, int &flag_legal, int &playerturns) {
	int card;
	card = random(13, 1);

	if (card >= 10) {
		card = 10;
	}
	if (judging21( card + total )) {
		total = card + total;
		cout << "新获得的牌点数为" << card << endl;
		cout << "此时您的牌点总数为 " << total << endl;
		cout << endl;
		flag_legal = 1;
	} else {
		total = card + total;
		cout << "新获得的牌点数为" << card << endl;
		cout << "此时您的牌点总数为 " << total << endl;
		cout << "您的牌已经超过21点，请输入 s 结束该轮比赛。" << endl;
		cout << endl;

		flag_legal = 0;
		playerturns = 10;
	}

}

void results(int player, int cpu, int bet, int &money, int &draw, int &win, int &lose)

//this function finds who wins
{

	if (cpu == player) {
		cout << "您和CPU打平了！" << endl;
		draw++;
		money = money + bet;
	}

	if (player > 21) {
		cout << "您的牌超过了21!" << endl;
		lose++;

	} else {

		if (cpu < player) {
			cout << "您赢了！";
			money = money + (bet * 2);
			win++;
		}
	}

	if (cpu > 21) {
		cout << "CPU的牌点数超过了21！" << endl;

		if (player < 21) {
			cout << "您赢了！";
			win++;
			money = money + (bet * 2);
		}

	} else {

		if (cpu > player) {
			cout << "很遗憾，您输了这一回合！" << endl;
			lose++;
		}
	}
}

void replay(char &ans) {
	cout << "您是否还想继续进行？(Y/n)";
	cin >> ans;
}

void print(int wins, int lose, int draw, int money) {
//	char name;
	cout << "胜场 :" << wins << endl;
	cout << "败场 :" << lose << endl;
	cout << "平局场次 :" << draw << endl;
	cout << "筹码总数 :" << money << endl;

//	cout << "请输入您的id";
//	cin >> name;
	cout << "您的战绩为" << wins << "-" << draw << "-" << lose << " " << "总筹码为:" << money << endl;
}

void wait(int milli) {
	clock_t start;
	start = clock();
	while ( ( clock() - start ) < milli );
}

void pause() {
	cout << "Press Any Key To Continue" << endl;
	getch();
}