#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;

class Init_map
{
public:
	void gener_Init_map(int cities);
};

inline void Init_map::gener_Init_map(int cities)
{
	ofstream fout("C:\\Users\\25361\\Desktop\\zz.txt");
	
	srand((unsigned)time(NULL));
	vector<vector<int> > map(cities, vector<int>(2));

	for (int i = 0; i < cities; i++)
	{
		map[i][0] = i;
		map[i][1] = i;
	}
	for (int i = cities - 1; i >= 0; i--)
	{
		int num = rand() % (i + 1);
		if (num != i)
		{
			swap(map[num][0], map[i][0]);
		}
	}

	for (int i = cities - 1; i >= 0; i--)
	{
		int num = rand() % (i + 1);
		if (num != i)
		{
			swap(map[num][1], map[i][1]);
		}
	}

	for (int i=0; i < cities; i++)
	{
		fout << i << " " << map[i][0] << " " << map[i][1] << endl;
	}
}
