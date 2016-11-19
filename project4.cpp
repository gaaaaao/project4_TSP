#include <iostream>  
#include <string.h>  
#include <fstream>  
#include <iterator> 
#include <limits.h>  
#include <math.h>  
#include <stdlib.h> 
#include <time.h>
#include "project4_init.cpp"

using namespace std;

class TSP
{
public:
	void adaptor();
private:
	static const int cities = 10;
	const double SPEED = 0.98;
	const int INIT_temperature = 1000;
	const int L = 100 * cities;
	struct city { int index/*city index*/; int x; int y;/*city coordinate*/ } map[cities];
	struct solution
	{ 
		double length; 
		int path[cities]; 
		bool operator < (const struct solution &another) const
		{
			return length < another.length;
		}
	};
	solution bestone;
	double length_table[cities][cities];

	void init_dis();
	void SA_TSP();
	void calcu_length(solution &p);
	void print_answer(solution &p);
	void GENER_NEW_PATH(solution &p);
	bool accept(solution &current, solution &p, double accept_prob);
	void random_shuffle(solution &p);
};

inline void TSP::adaptor()
{
	Init_map im;
	im.gener_Init_map(cities);

	init_dis();
	SA_TSP();
	calcu_length(bestone);
	print_answer(bestone);

	//solution temp;
	//for (int i = 0; i < cities; i++)
	//{
	//	temp.path[i] = i;
	//}
	//GENER_NEW_PATH(temp);
	//init_dis();
	//calcu_length(temp);

}

inline void TSP::init_dis()
{
	ifstream in("C:\\Users\\25361\\Desktop\\zz.txt");
	for (int i = 0; i < cities; i++)
	{
		in >> map[i].index >> map[i].x >> map[i].y;
	}

	for (int i = 0; i < cities; i++)
	{
		for (int j = i+1; j < cities; j++)
		{
			length_table[i][j] = length_table[j][i] = sqrt
			(
				(map[i].x - map[j].x)*(map[i].x - map[j].x) +
				(map[i].y - map[j].y)*(map[i].y - map[j].y)
			);
		}
	}
}

inline void TSP::SA_TSP()
{
	srand((unsigned)time(NULL));
	double spe = SPEED;
	double tem = INIT_temperature;
	const double MIN_tem = 0.001;

	solution temp;
	random_shuffle(temp);
	calcu_length(temp);
	memcpy(&bestone, &temp, sizeof(temp));

	while (tem > MIN_tem)
	{
		for (int i = 0; i < L; i++)
		{
			GENER_NEW_PATH(temp);
			if (accept(bestone, temp, tem))
			{
				memcpy(&bestone, &temp, sizeof(temp));
			}
			else
			{
				memcpy(&temp, &bestone, sizeof(temp));
			}
		}
		tem *= spe;
	}
	return;
}

inline void TSP::calcu_length(solution & p)
{
	int i = 1;
	p.length = 0;
	for (i; i < cities; i++)
	{
		p.length += length_table[p.path[i-1]][p.path[i]];
	}
	p.length += length_table[p.path[i-1]][p.path[0]];
}

inline void TSP::print_answer(solution & p)
{
	cout << "the best length: " << p.length;
	cout << "path: ";
	for (int i = 0; i < cities; i++)
	{
		cout << p.path[i] << " ";
	}
	cout << endl;
}

inline void TSP::GENER_NEW_PATH(solution & p)
{
	int i = rand() % cities;
	int j = rand() % cities;
	if (i > j)
	{
		int t = i;
		i = j;
		j = t;
	}
	else if (i == j)
		return;	
	
	int choose = rand() % 3;
	if (choose == 0)
	{
		int temp = p.path[i];
		p.path[i] = p.path[j];
		p.path[j] = temp;
	}
	else if (choose == 1)
	{
		int temp = 0;
		while (i < j)
		{
			temp = p.path[i];
			p.path[i] = p.path[j];
			p.path[j] = temp;
			i++;
			j--;
		}
	}
	else
	{
		if (j + 1 == cities)
			return;

		int temp = p.path[j];
		for (j; j>=i; j--)
		{
			p.path[j] = p.path[j - 1];
		}
		p.path[i] = temp;
	}
	calcu_length(p);
}

inline	bool TSP::accept(solution & current, solution & p, double accept_prob)
{
	if (current.length > p.length)
		return true;
	else
	{
		if ((int)(exp((current.length - p.length) / accept_prob) * 100) > (rand() % 101))
			return true;
	}
	return false;
}

inline void TSP::random_shuffle(solution & p)
{
	for (int i = 0; i < cities; i++)
	{
		p.path[i] = i;
	}

	for (int i = cities - 1; i >= 0; i--)
	{
		int num = rand() % (i+1);
		if (num != i)
		{
			swap(p.path[num], p.path[i]);
		}
	}
}


