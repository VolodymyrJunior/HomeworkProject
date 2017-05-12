#include<iostream>
#include<iomanip>
#include<fstream>

using namespace std;

void game(ifstream &);
void draw( int**, int,int,int);

int main()
{
	int T;
	ifstream fin("input.txt");
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		game(fin);
	}
	fin.close();
	//system("pause");
}

void game( ifstream &fin)
{
	int n;
	cin >> n;
	int n1 = n - 1;
	int **iMatrix = new int*[n];
	for (int i = 0; i < n; i++)
		iMatrix[i] = new int[n];

	for (int i = 0,u,v; i < n1; i++)
	{
		cin >> u >> v;
		iMatrix[--u][--v] = 1;
		iMatrix[v][u] = 1;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (iMatrix[i][j] != 1)
				iMatrix[i][j] = 0;
		}
	}
	///////////////////////////////////////////////////////////////algoritm Uorshala
	int **Mlenght = new int*[n];
	for (int i = 0; i < n; i++)
		Mlenght[i] = new int[n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			Mlenght[i][j] = iMatrix[i][j];//копіювання елемента матриці
			Mlenght[i][i] = 0;//обнулення значень по діагоналі
			if (Mlenght[i][j] == 0)
			{
				Mlenght[i][j] = 999;//присвоєння безкінечності
			}
		}
	}
	for (int k = 0; k < n; ++k)//кількість раз використання матриці
	{
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{

				if (i != j)//якщо елемент не лежить на діагоналі

				{
					Mlenght[i][j] = Mlenght[i][j] < Mlenght[i][k] + Mlenght[k][j] ? Mlenght[i][j] : Mlenght[i][k] + Mlenght[k][j];
					//визначення мінімального часу між двома станціями
				}
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (Mlenght[i][j] == 999)//шлях не існує
			{
				Mlenght[i][j] = 0;//доїхати не можливо до станція
			}
			//cout << setw(3) << Mlenght[i][j] << " ";
		}
		//cout << endl;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////game on tree
	int start=-1, altStart;
	bool error_pair = false;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (Mlenght[i][j] != 0 && Mlenght[i][j] % 2 == 0)
			{

				if (!error_pair)
				{
					start = i;
					error_pair = true;
					break;
				}
				
			}
		}
		if (error_pair)
			break;
	}
	
	
	bool br = false;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (Mlenght[i][j] != 0)
			{
				if (!br)
				{
					altStart = i;
					br = true;
					break;
				}
			}
		}
		if (br)
			break;
	}
	
	//cout << altStart + 1 << endl;;
	if (start==-1)
		start = altStart;
	//cout << start + 1 << endl;
	
	draw(Mlenght,n,start,0);







	for (int i = 0; i < n; i++)
	{
		delete[] iMatrix[i];
		delete[] Mlenght[i];
	}
}
void draw( int** lenght, int n,int start,int win)
{
	//bool change = false;
	int *visit = new int[n];
	for (int i = 0; i < n; i++)
	{
		visit[i] = -1;
		//cout << visit[i] << " ";
	}
	//cout << endl;
	//int next;
	int altStart;
	int winner;
	//char win//;
	visit[start] = 0;
	if (win == 0)
	{
		win = 1;
	}
	else
	{
		win = 0;
	}
//	cout << win << endl;
	do
	{
		bool new1 = false;
		bool new2 = false;
		if (win == 0)
		{
			
			for (int i = 0; i < n; i++)
			{
				//cout << "start" << start << endl;
				if (lenght[start][i] != 0 && visit[i] == -1)
				{
				//	cout << "-1-";
					if (lenght[start][i] % 2 == 0)
					{
						start = i;
						//cout << "start" << start+1 << endl;
						visit[i] = 0;
						//draw(lenght, visit, n, start, win);
						
						new1 = true;
						break;
					}
					else
					{
						if (!new2)
						{
							altStart = i;
							visit[i] = 0;
							new2 = true;
						}
					}
				}
			}
			if (!new1 && new2)
			{
				start = altStart;
				//draw(lenght, visit, n, start, win);
				//cout << "start" << start+1 << endl;
			}
			if (!new1 && !new2)
			{
				winner = 1;
				break;
			}
		}
		else
		{
			for (int i = 0; i < n; i++)
			{
				if (lenght[start][i] != 0 && visit[i] == -1)
				{
					//cout << "_++_" << endl;
					if (lenght[start][i] % 2 != 0)
					{
						start = i;
						//cout << "start" << start+1 << endl;
						visit[i] = 0;
						new1 = true;
						break;
					}
					else
					{
						if (!new2)
						{
							altStart = i;
							visit[i] = 0;
							new2 = true;
						}
					}
				}
			}
			if (!new1 && new2)
			{
				start = altStart;
				//cout << "start" << start+1 << endl;
			}
			if (!new1 && !new2)
			{
				winner = 0;
				break;
			}
		}
		if (win == 0)
			win = 1;
		else
			win = 0;
		//cout << "+" << winner[0] << endl;
	} while (1);
	//cout <<"+" <<winner[0] << endl;
	winner == 1 ? cout << "Bob" << endl : cout << "Alice" << endl;


	delete[] visit;
	//for (int i = 0; i < n; i++)
	//{
	//	if (win == 'A')
	//	{
	//		if (visit[i] == '-1'&& lenght[start][i] != 0)
	//		{
	//			if (!new1) next = i;
	//			if (lenght[start][i] % 2 == 0)
	//			{
	//				//draw(lenght, visit, n, start, win);
	//				start = i;
	//				change = true;
	//			}
	//			if (lenght[start][i] != 0 && visit[i] == '-1')
	//			{

	//			}
	//		}
	//	}
	//	else
	//	{
	//		if (lenght[start][i] != 0 && lenght[start][i] % 2 != 0 && visit[i] == '-1')
	//		{
	//			draw(lenght, visit, n, start, win);
	//		}
	//	}
	//}
	//for (int i = 0; i < n; i++)
	//{
	//	if (lenght[start][i] != 0 && lenght[start][i] % 2 == 0 && visit[i] == '-1')
	//	{
	//		
	//		start = i;
	//		change = true;
	//		draw(lenght, visit, n, start, win);
	//	}
	//}
	//if (!change)
	//{
	//	for (int i = 0; i < n; i++)
	//	{
	//		if (lenght[start][i] != 0 && visit[i] == '-1')
	//		{
	//			start = i;
	//			draw(lenght, visit, n, start, win);
	//		}
	//	}
	//}
}