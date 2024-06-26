#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <conio.h>
#include <time.h>
#include <string>

using namespace std;

//游戏内容设定函数声明
void replay(char &ans);     
void setting(int chips, int &money);	
//游戏主要内容操作函数设定
void hit(float &total, int &flag_legal, int &playerturns);    
int cpu_hit(float &total, int& cputurns);
void deal(float &player, float& cpu, int& playerturns, int& cputurns, float& player_score, float& cpu_score); 
void admin_deal(float &player, float& cpu, int& playerturns, int& cputurns, float& player_score, float& cpu_score);
void BET(int &bet, int &money); //takes bet
//游戏判断与打印函数设定
int judging21(int a);
void print(int wins, int lose, int draw, int money , int default_money);
void results(float player, float cpu, int bet, int &money, int &draw, int &win, int &lose);
//游戏数学与计算机机制函数声明
int random(long hi, long lo);
void wait(int milli);
void pause();
void game_rules();
void game_author();
//全局变量声明
int win = 0, lose = 0, draw = 0, playerturns = 0, cputurns = 0, money = 100, default_money = 100, bet;
float player = 0, cpu = 0;
float player_score = 0, cpu_score = 0;
int flag_legal = 1, flag = 0, admin_mode = 0;
string password = "1";
string input_pwd = "";

int main() {

	char ans;
	int choice;

		do {
			// 显示菜单选项
			system("cls");
			std::cout << "欢迎来到21点游戏！" << std::endl;
			std::cout << "1. 开始游戏" << std::endl;
			std::cout << "2. 游戏规则" << std::endl;
			std::cout << "3. 游戏设置" << std::endl;
			std::cout << "4. 退出" << std::endl;
			std::cout << "请输入您的选择: ";
			std::cin >> choice;


			// 处理用户选择
			switch (choice) {
			case 1:
				system("cls");
				ans = 'y';
				cout << "欢迎来到21点游戏！" << endl;
				if ((ans == 'y') || (ans == 'Y')) {
					cout << "您初始拥有的筹码为 $ " << money << endl;
				}
				else {
					return 0;
				}

				do {
					system("cls");
					if (money <= 0) {
						cout << "您破产了！" << endl;
						return (0);
						break;
					}
					BET(bet, money);

					if (admin_mode == 0) {
						deal(player, cpu, playerturns, cputurns, player_score, cpu_score);
					} else {
						admin_deal(player, cpu, playerturns, cputurns, player_score, cpu_score);
					}

					do {
						cout << "您是否要继续拿牌？(H以继续，s则停止)";
						cin >> ans;
						if ((ans == 'h') || (ans == 'H')) {
							playerturns++;
							if (playerturns > 5) {
								cout << "操作非法！" << endl;;
							}
						}
						if ((playerturns < 6) && (ans == 'h')) {
							hit(player, flag_legal, playerturns);
						}
					} while ((ans == 'h') || (ans == 'H'));

					for (; (cpu < 16) && (cputurns < 6); cputurns++) {
						cout << endl;
						cout << "CPU正在进行思考" << endl;
						wait(600);
						cpu_hit(cpu, cputurns);
					}
					cout << endl;
					cout << "CPU的总数:" << cpu << endl;
					cout << "您的总数:" << player << endl;
					cout << endl;
					results(player, cpu, bet, money, draw, win, lose);
					replay(ans);
				} while ((ans == 'y') || (ans == 'Y'));

				print(win, lose, draw, money, default_money);
				return (0);
				break;

			case 2:
				std::cout << "游戏介绍" << std::endl;
				game_rules();
				break;
			
			case 3:
				std::cout << "游戏设置" << std::endl;
				cout << "请输入密码：";
				cin >> input_pwd;

				if (input_pwd == password) {
					cout << "您已获得权限，进入设置菜单。" << endl;
					admin_mode = 1;
					int choice3, def_money;
					do {
						std::cout << "1. 初始筹码设置" << std::endl;
						std::cout << "2. 游戏作者" << std::endl;
						std::cout << "3. 回到主菜单" << std::endl;
						std::cout << "请输入您的选择: ";
						std::cin >> choice3;

						switch (choice3) {
						case 1:
							cout << "请输入初始筹码数目：";
							cin >> def_money;
							cout << "您设置的初始筹码为 $" << def_money << endl;
							setting(def_money, money);
							default_money = def_money;
							break;

						case 2:
							std::cout << "游戏作者" << std::endl;
							game_author();
							break;

						case 3:
							break;

						default:
							std::cout << "无效的选择！请键入有效选项。" << std::endl;
							break;
						}

					} while (choice != 3);
				}
				else {
					cout << "Password is incorrect. Access denied." << endl;
				}
				
			
				break;

			case 4:
				std::cout << "退出游戏。再见！" << std::endl;
				break;

			default:
				std::cout << "无效的选择！请键入有效选项。" << std::endl;
				break;
			}

		} while (choice != 4);


	
}

void game_rules() {
	cout << "1. 牌面大小为1-13，11-13被视为0.5分。" << endl;
	cout << "2. 牌面大小相同的牌，视为同一张牌。" << endl;
	cout << "3. 游戏开始时，玩家会收到两张牌，出现爆牌（手中牌的总点数超过21点）即输掉比赛。" << endl;
	cout << "4. 目标是使您手中的卡牌总点数尽可能接近 21 点，但不超过 21 点。" << endl;
	cout << "5. 玩家可以选择“Hit”来抽取额外的牌，以尽可能接近21点。" << endl;
	cout << "6. 玩家还可以选择“Stand”（不再抽取额外的牌），并将轮到庄家表现。" << endl;
	cout << "7. 如果玩家和庄家的点数相同，则比赛平局。" << endl;		
	pause();
}

void game_author() {
	cout << "作者：SuperJacky6" << endl;
	cout << "联系方式：Adding2003@gmail.com" << endl;
}

 void setting(int chips,int &money) {
	money = chips;
	cout << "New chips setting applied. New chips" << chips << endl;
}

int random(long hi, long lo) {
	time_t t;
	int ran;
	srand((unsigned) time(&t));
	ran = rand() % (hi - (lo - 1)) + lo;
	return (ran);
}

void BET(int &bet, int &money) {
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

void admin_deal(float& player, float& cpu, int& playerturns, int& cputurns, float& player_score, float& cpu_score) {
	float playercard1, playercard2, cpucard1, cpucard2;
	cout << "轻触回车键开始发牌！" << endl;
	pause();

	playerturns = 2;
	cputurns = 2;

	playercard1 = random(13, 1);
	wait(1250);

	playercard2 = random(13, 1);
	wait(1250);

	cpucard1 = random(13, 1);
	wait(1250);

	cpucard2 = random(13, 1);
	//实现伪随机数的random函数保证单次调用的差异性
	if (playercard1 > 10) {
		    playercard1 = 0.5;
	}
	if (playercard2 > 10) {
        playercard2 = 0.5;
    }
    if (cpucard1 > 10) {
        cpucard1 = 0.5;
    }
    if (cpucard2 > 10) {
        cpucard2 = 0.5;
    }

	player = playercard1 + playercard2;
	cpu = cpucard1 + cpucard2;
	cout << "您的牌总和为" << player << endl;
	cout << "[" << playercard1 << "]";
	cout << "[" << playercard2 << "]";
	cout << endl;
	cout << "CPU的牌为:" << endl;
	cout << "[" << cpucard1 << "]";
	cout << "[" << cpucard2 << "]" << endl;
	cout << "CPU的牌总和为" << cpu << endl;
}

void deal(float &player, float &cpu, int &playerturns, int &cputurns, float& player_score, float& cpu_score) {
	float playercard1, playercard2, cpucard1, cpucard2;
	cout << "轻触回车键开始发牌！" << endl;
	pause();

	playerturns = 2;
	cputurns = 2;

	playercard1 = random(13, 1);
	wait(1250);

	playercard2 = random(13, 1);
	wait(1250);

	cpucard1 = random(13, 1);
	wait(1250);

	cpucard2 = random(13, 1);
	//实现伪随机数的random函数保证单次调用的差异性
	if (playercard1 > 10) {
		playercard1 = 0.5;
	}
	if (playercard2 > 10) {
		playercard2 = 0.5;
	}
	if (cpucard1 > 10) {
		cpucard1 = 0.5;
	}
	if (cpucard2 > 10) {
		cpucard2 = 0.5;
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

int cpu_hit(float &total, int &cputurns) {
	float card;
	card = random(13, 1);

	if (card >= 10) {
		card = 0.5;
	}
	//修复了CPU在已经超数的情况下会继续获取牌的bug。
	if ( total + card > 21 ) {
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

void hit(float &total, int &flag_legal, int &playerturns) {
	int card;
	card = random(13, 1);

	if (playerturns > 2) {
		int additionalBet;
		cout << "您已经追加要牌 " << (playerturns - 2) << " 次，是否要追加下注？(输入追加的金额或 0 表示不追加): ";
		cin >> additionalBet;

		if (additionalBet > 0 && additionalBet <= money) {
			bet += additionalBet;
			money -= additionalBet;
		}
		else if (additionalBet > money) {
			cout << "追加下注金额超过您的筹码，请重新输入。" << endl;
		}
	}

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

void results(float player, float cpu, int bet, int& money, int& draw, int& win, int& lose) {

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

void print(int wins, int lose, int draw, int money, int default_money) {
	string name;
	cout << "胜场 :" << wins << endl;
	cout << "败场 :" << lose << endl;
	cout << "平局场次 :" << draw << endl;
	cout << "筹码总数 :" << money << endl;

	cout << "请输入您的id";
	cin >> name;
	cout << name << " 的战绩为" << wins << "-" << draw << "-" << lose << " " << "总筹码为:" << money << endl;
	cout << "相比于初始筹码数目，您的正负差为 $	" << money - default_money << endl;
}

void wait(int milli) {
	clock_t start;
	start = clock();
	while ( ( clock() - start ) < milli );
}

void pause() {
	cout << "Press Any Key To Continue" << endl;
	_getch();
}