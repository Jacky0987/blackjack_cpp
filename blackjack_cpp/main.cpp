//SuperJacky6 @ ByteDance Tiktok Algorithm Department
//Under GNU-v3 License Redesigned and refined.

//Contact : adding2003@gmail.com

#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <conio.h>
#include <time.h>
#include <string>

using namespace std;


//��Ϸ�����趨��������
void replay(char &ans);     //allows replay of game
void setting(int chips, int &money);	//jump into settings menu.
//��Ϸ��Ҫ���ݲ��������趨
void hit(int &total, int &flag_legal, int &playerturns);      //take another card
int cpu_hit(int &total, int &cputurns);
void deal(int& player, int& cpu, int& playerturns, int& cputurns, float &player_score, float & cpu_score); //deals hand
void admin_deal(int &player, int &cpu, int &playerturns, int &cputurns, float& player_score, float& cpu_score); //deals hand for admin mode
void BET(int &bet, int &money); //takes bet
//��Ϸ�ж����ӡ�����趨
int judging21(int a);
void print(int wins, int lose, int draw, int money , int default_money); //prints final score
void results(int player, int cpu, int bet, int &money, int &draw, int &win, int &lose); //finds winner
//��Ϸ��ѧ���������ƺ�������
int random(long hi, long lo); //random function using time stamp.
void wait(int milli);
void pause();
void game_rules();
void game_author();

/*
δ��������б�

1.Ҫ�ƺ������multiplier���趨��
	��δʵ�֣���Ҫ���³���������ж���Ӽ���ʽ��

����������б�:

1.�������ʵ�֡���д���������װ��
2.13���˿��ƴ���10���ж�Ϊ10������Ҫ�ĳ�0.5���и�����Ҫ��
3.CPU����Զ���ᱬׯ��(2.3.3-3)
4.����������ж��趨�뱨��
5.���ı��ػ�21��������ݡ�
6.H����������Ա�趨��
	�˵�����ѡ���ֳ�������ɡ�
	��Ϸ�����������cpu_hit��hit�����ֱ��趨������ɡ�
7.�����������������������ʵ�֡�
8.����10�ĵ�����Ϊ0.5�жϡ�
	ȫ�������player��cpu�ĸ��������޸ġ�


��֪BUG�б�

1.�����ڶ��ڷǷ��������ж�����ʹ�����������flag_legalδ����ʹ�á�
2.�����м��������ͬ��
	ԭ��random�����ڴ���ʱ�����ʱ��ͬʱִ������ͬ�����֡�
	���ֽ������������13/10����sleep�ӳ�ʱ������롣
3.����������⡣
	�Ѳ��ֽ����
4.�������ݵļ������⡣
5.CPU���Ѿ�����������»������ȡ�Ƶ�bug
	�ѽ����������int���ӷ��������ж���
*/


int main() {

	//Initializing...
	int player = 0, cpu = 0, win = 0, lose = 0, draw = 0, playerturns = 0, cputurns = 0, money = 100 ,default_money = 100, bet;
	float player_score = 0, cpu_score = 0;
	int flag_legal = 1, flag = 0, admin_mode = 0;

	char ans;

	string password = "1";
	string input_pwd = "";

	int choice;

		do {
			// ��ʾ�˵�ѡ��
			system("cls");
			std::cout << "��ӭ����21����Ϸ��" << std::endl;
			std::cout << "1. ��ʼ��Ϸ" << std::endl;
			std::cout << "2. ��Ϸ����" << std::endl;
			std::cout << "3. ��Ϸ����" << std::endl;
			std::cout << "4. �˳�" << std::endl;
			std::cout << "����������ѡ��: ";
			std::cin >> choice;


			// �����û�ѡ��
			switch (choice) {
			case 1:
				system("cls");
				ans = 'y';
				cout << "��ӭ����21����Ϸ��" << endl;
				if ((ans == 'y') || (ans == 'Y')) {
					cout << "����ʼӵ�еĳ���Ϊ $ " << money << endl;
				}
				else {
					return 0;
				}

				do {
					system("cls");
					if (money <= 0) {
						cout << "���Ʋ��ˣ�" << endl;
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
						cout << "���Ƿ�Ҫ�������ƣ�(H�Լ�����s��ֹͣ)";
						cin >> ans;
						if ((ans == 'h') || (ans == 'H')) {
							playerturns++;
							if (playerturns > 5) {
								cout << "�����Ƿ���" << endl;;
							}
						}
						if ((playerturns < 6) && (ans == 'h')) {
							hit(player, flag_legal, playerturns);
						}
					} while ((ans == 'h') || (ans == 'H'));

					for (; (cpu < 16) && (cputurns < 6); cputurns++) {
						cout << endl;
						cout << "CPU���ڽ���˼��" << endl;
						wait(600);
						cpu_hit(cpu, cputurns);
					}
					cout << endl;
					cout << "CPU������:" << cpu << endl;
					cout << "��������:" << player << endl;
					cout << endl;
					results(player, cpu, bet, money, draw, win, lose);
					replay(ans);
				} while ((ans == 'y') || (ans == 'Y'));

				print(win, lose, draw, money, default_money);
				return (0);
				break;

			case 2:
				std::cout << "��Ϸ����" << std::endl;
				game_rules();
				break;
			
			case 3:
				std::cout << "��Ϸ����" << std::endl;
				cout << "���������룺";
				cin >> input_pwd;

				if (input_pwd == password) {
					cout << "���ѻ��Ȩ�ޣ��������ò˵���" << endl;
					admin_mode = 1;
					int choice3, def_money;
					do {
						std::cout << "1. ��ʼ��������" << std::endl;
						std::cout << "2. ��Ϸ����" << std::endl;
						std::cout << "3. �ص����˵�" << std::endl;
						std::cout << "����������ѡ��: ";
						std::cin >> choice3;

						switch (choice3) {
						case 1:
							cout << "�������ʼ������Ŀ��";
							cin >> def_money;
							cout << "�����õĳ�ʼ����Ϊ $" << def_money << endl;
							setting(def_money, money);
							default_money = def_money;
							break;

						case 2:
							std::cout << "��Ϸ����" << std::endl;
							game_author();
							break;

						case 3:
							break;

						default:
							std::cout << "��Ч��ѡ���������Чѡ�" << std::endl;
							break;
						}

					} while (choice != 3);
				}
				else {
					cout << "Password is incorrect. Access denied." << endl;
				}
				
			
				break;

			case 4:
				std::cout << "�˳���Ϸ���ټ���" << std::endl;
				break;

			default:
				std::cout << "��Ч��ѡ���������Чѡ�" << std::endl;
				break;
			}

		} while (choice != 4);


	
}

void game_rules() {
	cout << "1. �����СΪ1-13��11-13����Ϊ0.5�֡�" << endl;
	cout << "2. �����С��ͬ���ƣ���Ϊͬһ���ơ�" << endl;
	cout << "3. ��Ϸ��ʼʱ����һ��յ������ƣ����ֱ��ƣ������Ƶ��ܵ�������21�㣩�����������" << endl;
	cout << "4. Ŀ����ʹ�����еĿ����ܵ��������ܽӽ� 21 �㣬�������� 21 �㡣" << endl;
	cout << "5. ��ҿ���ѡ��Hit������ȡ������ƣ��Ծ����ܽӽ�21�㡣" << endl;
	cout << "6. ��һ�����ѡ��Stand�������ٳ�ȡ������ƣ��������ֵ�ׯ�ұ��֡�" << endl;
	cout << "7. �����Һ�ׯ�ҵĵ�����ͬ�������ƽ�֡�" << endl;		
	pause();
}

void game_author() {
	cout << "���ߣ�SuperJacky6" << endl;
	cout << "��ϵ��ʽ��Adding2003@gmail.com" << endl;
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
	cout << "��ӵ�г��� $" << money << endl;
	cout << "������ע���� $ �� ";
	cin >> bet;

	if (money - bet < 0) {
		cout << "������������ֳ���������ӵ�еĳ��룬������" << endl;
		BET(bet, money);
		//ʹ���ظ����ý�������������
	} else {
		money = money - bet;
	}
}

void admin_deal(int& player, int& cpu, int& playerturns, int& cputurns, float& player_score, float& cpu_score) {
	float playercard1, playercard2, cpucard1, cpucard2;
	cout << "�ᴥ�س�����ʼ���ƣ�" << endl;
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
	//ʵ��α�������random������֤���ε��õĲ�����
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
	cout << "�������ܺ�Ϊ" << player << endl;
	cout << "[" << playercard1 << "]";
	cout << "[" << playercard2 << "]";
	cout << endl;
	cout << "CPU����Ϊ:" << endl;
	cout << "[" << cpucard1 << "]";
	cout << "[" << cpucard2 << "]" << endl;
	cout << "CPU�����ܺ�Ϊ" << cpu << endl;
}

void deal(int &player, int &cpu, int &playerturns, int &cputurns, float& player_score, float& cpu_score) {
	float playercard1, playercard2, cpucard1, cpucard2;
	cout << "�ᴥ�س�����ʼ���ƣ�" << endl;
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
	//ʵ��α�������random������֤���ε��õĲ�����
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
	cout << "�������ܺ�Ϊ" << player << endl;
	cout << "[" << playercard1 << "]";
	cout << "[" << playercard2 << "]";
	cout << endl;
	cout << "CPU������һ����Ϊ:" << cpucard1 << endl;
	cout << "��ϸ�Ƶ�Ϊ��" << endl;
	cout << "[*]" << "[" << cpucard1 << "]" << endl;
}

int cpu_hit(int &total, int &cputurns) {
	float card;
	card = random(13, 1);

	if (card >= 10) {
		card = 0.5;
	}
	//�޸���CPU���Ѿ�����������»������ȡ�Ƶ�bug��
	if ( total + card > 21 ) {
		cout << "CPUѡ�񲻻�ȡ���ƣ��ܵ���Ϊ" << total << endl;
		return 0;
	} else {
		total = total + card;
		cout << "CPUѡ���ȡ����" << endl;
		cout << "��ʱCPU�����Ƶ�����Ϊ " << total << endl;
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
		cout << "�»�õ��Ƶ���Ϊ" << card << endl;
		cout << "��ʱ�����Ƶ�����Ϊ " << total << endl;
		cout << endl;
		flag_legal = 1;
	} else {
		total = card + total;
		cout << "�»�õ��Ƶ���Ϊ" << card << endl;
		cout << "��ʱ�����Ƶ�����Ϊ " << total << endl;
		cout << "�������Ѿ�����21�㣬������ s �������ֱ�����" << endl;
		cout << endl;

		flag_legal = 0;
		playerturns = 10;
	}

}

void results(int player, int cpu, int bet, int &money, int &draw, int &win, int &lose) {

	if (cpu == player) {
		cout << "����CPU��ƽ�ˣ�" << endl;
		draw++;
		money = money + bet;
	}

	if (player > 21) {
		cout << "�����Ƴ�����21!" << endl;
		lose++;

	} else {

		if (cpu < player) {
			cout << "��Ӯ�ˣ�";
			money = money + (bet * 2);
			win++;
		}
	}

	if (cpu > 21) {
		cout << "CPU���Ƶ���������21��" << endl;

		if (player < 21) {
			cout << "��Ӯ�ˣ�";
			win++;
			money = money + (bet * 2);
		}

	} else {

		if (cpu > player) {
			cout << "���ź�����������һ�غϣ�" << endl;
			lose++;
		}
	}
}

void replay(char &ans) {
	cout << "���Ƿ���������У�(Y/n)";
	cin >> ans;
}

void print(int wins, int lose, int draw, int money, int default_money) {
	string name;
	cout << "ʤ�� :" << wins << endl;
	cout << "�ܳ� :" << lose << endl;
	cout << "ƽ�ֳ��� :" << draw << endl;
	cout << "�������� :" << money << endl;

	cout << "����������id";
	cin >> name;
	cout << name << " ��ս��Ϊ" << wins << "-" << draw << "-" << lose << " " << "�ܳ���Ϊ:" << money << endl;
	cout << "����ڳ�ʼ������Ŀ������������Ϊ $	" << money - default_money << endl;
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