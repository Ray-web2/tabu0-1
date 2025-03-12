#include <iostream>
using namespace std;

const int TABU_SIZE = 10;     // tabulist最大長度
const int MAX_ITER = 1000;    //iteration 1000

void Tweak(int array[], int capacity, int profits[], int weights[],int n)
{
	for (int k=0; k < n; k++)//做n次
	{
		int random = rand() % n;
		int orig = array[random];//將變換前的值暫存
		array[random] = 1 - array[random];//1-0=1,1-1=0(0變1,1變0)

		int total_weight = 0;
		for (int i = 0; i < n; i++)//加總重量
		{
			total_weight = total_weight + array[i] * weights[i];
		}
		if (total_weight <= capacity)//在可負重範圍
			return;
		else//超重的話捨棄
			array[random] = orig;
	}
}
int total_profit(int array[], int capacity, int profits[], int weights[], int n)
{
	int total_profit = 0;
	for (int i = 0; i < n; i++)//加總價值
	{
		total_profit = total_profit + array[i] * profits[i];
	}
	return total_profit;
}

void addTabu(int tabu[TABU_SIZE][5000],int array[],int tabucount,int n)//將一組結果存到tabulist
{
	for (int i = 0; i < n; i++)
	{
		tabu[(tabucount + 1) % TABU_SIZE][i] = array[i];
	}
}

int inTabu(int tabu[TABU_SIZE][5000],int array[],int n)//檢查該組結果是否在tabulist中
{
	int flag = 1;
	for (int i = 0; i < TABU_SIZE; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (tabu[i][j] != array[j])//一個字不一樣就把旗子設成0
				flag = 0;
		}
	}
	if (flag == 1)//在tabulist中的話 旗子為1
		return true;
	else
		return false;
}

int main() {
	int tabucount=0;//紀錄tabulist要存入位置，取代第九行的remove oldest
	int n, capacity;
	cin >> n >> capacity;//讀入數量和重量

	int weights[5000], profits[5000];

	for (int i = 0; i < n; i++) {//讀入參數
		cin >> weights[i] >> profits[i];
	}

	int S[5000]={};//初始化
	int Best[5000]={};//初始化
	int tabu[TABU_SIZE][5000] = {};//初始化tabu list

	addTabu(tabu, S, tabucount,n);
	tabucount++;


	for (int iter = 0; iter < MAX_ITER; iter++)
	{
		int R[5000];//原本的最佳解
		for (int i = 0; i < 5000; i++)//佔存原本的最佳解
		{
			R[i] = S[i];
		}
		Tweak(R,capacity,profits,weights,n);
		//觀察目前最佳解
		int bestProfit = total_profit(Best, capacity, profits, weights, n);
		cout << "max profit:" << bestProfit << "\n";
		cout << "solution:";
		for (int i = 0; i < n; i++)
			cout << Best[i];
		cout << "\n";
		//
		for (int i = 0; i < n-1; i++)
		{
			int W[5000];
			for (int i = 0; i < 5000; i++)//佔存原本的最佳解
			{
				W[i] = S[i];
			}
			Tweak(W, capacity, profits, weights, n);//12行

			if ((!inTabu(tabu, W,n)) || (total_profit(W, capacity, profits, weights,n) > total_profit(R, capacity, profits, weights,n)))// 13行 
			{
				for (int i = 0; i < 5000; i++)//更新最佳解
				{
					R[i] = W[i];//14行
				}
			}
			if (!inTabu(tabu, R, n))//15到17
			{
				for (int i = 0; i < 5000; i++)//更新最佳解
				{
					S[i] = R[i];
				}
				addTabu(tabu, R, tabucount, n);//17行
				tabucount++;//紀錄tabulist要存入位置，取代第九行的remove oldest
			}
			if ((total_profit(S, capacity, profits, weights, n) > total_profit(Best, capacity, profits, weights, n)))//18到19
			{
				for (int i = 0; i < 5000; i++)//更新最佳解
				{
					Best[i] = S[i];
				}
			}
		}
	}
	//輸出
	int bestProfit = total_profit(Best, capacity, profits, weights,n);
	cout << "max profit:" << bestProfit << "\n";
	cout << "solution:";
	for(int i = 0; i < n; i++)
		cout << Best[i];
	cout << "\n";

	system("pause");//exe暫停
	return 0;
}
