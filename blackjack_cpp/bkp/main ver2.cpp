//SuperJacky6 @ ByteDance Tiktok Algorithm Dep.
//Under GPT-v3 License Redesigned and refined.

//Contact : adding2003@gmail.com

#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <conio.h>
#include <time.h>

using namespace std;


//��Ϸ�����趨��������
void replay(char &ans);     //allows replay of game
void setting(int chips);	//jump into settings menu.
//��Ϸ��Ҫ���ݲ��������趨
void hit(int &total, int &flag_legal, int &playerturns);      //take another card
int cpu_hit(int &total, int &cputurns);
void deal(int &player, int &cpu, int &playerturns, int &cputurns); //deals hand
void BET(int &bet, int &money); //takes bet
//��Ϸ�ж����ӡ�����趨
int judging21(int a);
void print(int wins, int lose, int draw, int money); //prints final score
void results(int player, int cpu, int bet, int &money, int &draw, int &win, int &lose); //finds winner
//��Ϸ��ѧ���������ƺ�������
int random(long hi, long lo); //random function using time stamp.
void wait(int milli);
void pause();


/*
δ��������б�

1.H����������Ա�趨�����˵����໯��ģ�黯����(��������֣�)��
	�˵�����ѡ���ֳ���
	��Ϸ�����������cpu_hit��hit�����ֱ��趨��
2.����10�ĵ�����Ϊ0.5�жϡ�
	ȫ�������player��cpu�ĸ��������޸ġ�
3.Ҫ�ƺ������multiplier���趨��
	��δʵ�֣���Ҫ���³���������ж���Ӽ���ʽ��
4.ģ��ͼ�λ�Graphic User Interface��ʵ�֡�
5.�����������������������ʵ�֡�
	void function game_rules();
	void function game_author();
6.��ͬ�������Ƶ�Split�����뺯��ʵ�֡����Ǳ��룩


����������б�:

1.�������ʵ�֡���д���������װ��
2.13���˿��ƴ���10���ж�Ϊ10������Ҫ�ĳ�0.5���и�����Ҫ��
3.CPU����Զ���ᱬׯ��(2.3.3-3)
4.����������ж��趨�뱨��
5.���ı��ػ�21��������ݡ�

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

	//Initialize variants
	int player = 0, cpu = 0, win = 0, lose = 0, draw = 0, playerturns = 0, cputurns = 0, money = 0, bet;
	int flag_legal = 1, flag = 0;
	char ans;

	//system("cls");
	cout << "BLACKJACK GAME" << endl;
	cout << "�Ƿ�ʼ��Ϸ��(Y/n)";

	cin >> ans;

	if ((ans == 'y') || (ans == 'Y')) { //Checks to see if they want to play...
		system("cls");
		cout << "����ʼӵ�еĳ���Ϊ $ " << money << endl; //starts u with money
		money = 1000;
	} else {
		return (0);
	}


	do {
		system("cls");
		if (money <= 0) {
			cout << "���Ʋ��ˣ�" << endl;
			return (0);
			break;
		}
		BET(bet, money); //calls bet fuction
		deal(player, cpu, playerturns, cputurns); //Deals the cards

		do {
			cout << "���Ƿ�Ҫ�������ƣ�(H/s)"; //ask user if the want a hit
			cin >> ans;
			if ((ans == 'h') || (ans == 'H')) {
				playerturns++; //adds one to players total cards
				if (playerturns > 5) { //sees if player can take a card
					cout << "�����Ƿ���" << endl;;
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
			cout << "CPU���ڽ���˼��" << endl;
			wait(600);
			cpu_hit(cpu, cputurns);
			//calls hit function
		}
		cout << endl;
		cout << "CPU������:" << cpu << endl; //displays dealers total and then yours
		cout << "��������:" << player << endl;
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


void deal(int &player, int &cpu, int &playerturns, int &cputurns) {
	int playercard1, playercard2, cpucard1, cpucard2;
	cout << "�ᴥ�س�����ʼ���ƣ�" << endl;
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
	//ʵ��α�������random������֤���ε��õĲ�����
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
	cout << "�������ܺ�Ϊ" << player << endl;
	cout << "[" << playercard1 << "]";
	cout << "[" << playercard2 << "]";
	cout << endl;
	cout << "CPU������һ����Ϊ:" << cpucard1 << endl;
	cout << "��ϸ�Ƶ�Ϊ��" << endl;
	cout << "[*]" << "[" << cpucard1 << "]" << endl;
}

int cpu_hit(int &total, int &cputurns) {
	int card;
	card = random(13, 1);

	if (card >= 10) {
		card = 10;
	}
	//�޸���CPU���Ѿ�����������»������ȡ�Ƶ�bug��
	if ( total + card > 21 ) {
		// Stop hitting cards and undo the event.
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

void results(int player, int cpu, int bet, int &money, int &draw, int &win, int &lose)

//this function finds who wins
{

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

void print(int wins, int lose, int draw, int money) {
//	char name;
	cout << "ʤ�� :" << wins << endl;
	cout << "�ܳ� :" << lose << endl;
	cout << "ƽ�ֳ��� :" << draw << endl;
	cout << "�������� :" << money << endl;

//	cout << "����������id";
//	cin >> name;
	cout << "����ս��Ϊ" << wins << "-" << draw << "-" << lose << " " << "�ܳ���Ϊ:" << money << endl;
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