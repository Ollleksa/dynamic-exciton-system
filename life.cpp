#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

using namespace std;

const int Dim = 100;

class life
{
	private:
	        int cells[Dim+2][Dim+2];			//bigger on two, because I want to initialisate some border conditions
	        int temp[Dim+2][Dim+2];
	        int iter;
		int type;					//type of life system (closed, open, etc)
	public:
	        life()                                		//empty field;
	        {
			for(int x = 0; x < Dim+2; x++)
            		for(int y = 0; y < Dim+2; y++)
            		{
                		cells[x][y] = 0;
                		temp[x][y] = 0;
            		}
            		iter = 0;
			type = 0;				//by default it closed system
        	}
//------------------------------------------
        	void doc_show();                     		//write system into file in ASCII format
//------------------------------------------
        	void generation(int s);             		//generate system
		void random_gen();
		void block_gen();
		void blinker_gen();
		void glider_gen();
		void glider_cannon();
//------------------------------------------
		void change_type(int t);        	
		void moving();                      		//evolve by one step
		void check();					//check if set is empty or stable
};

void life::doc_show()
{
	ofstream myfile;
	char filename[256];
	sprintf(filename,"life/data%d.dat",iter);
	myfile.open(filename);
	for(int x = 1; x < Dim+1; x++)
	{
		for(int y = 1; y < Dim+1; y++)
                {
	                myfile << cells[x][y] << "\t";
                }
                myfile << "\n";
	}
        myfile.close();
}

void life::generation(int s)             //generate system
{
        switch(s)
	{
		case(1):
		{
			random_gen();
			break;
		}
		case(2):
		{
			block_gen();
			break;
		}
		case(3):
		{
			blinker_gen();
			break;
		}
		case(4):
		{
			glider_gen();
			break;
		}
		case(5):
		{
			glider_cannon();
		}
	}	
}

void life::random_gen()
{
	for(int x = 1; x < Dim+1; x++)
        for(int y = 1; y < Dim+1; y++)
        {
        	cells[x][y] = rand()%2;
        }
}

void life::block_gen()
{
	cells[1][1] = 1;
	cells[2][1] = 1;
	cells[1][2] = 1;
	cells[2][2] = 1;
	cells[1][3] = 1;
}

void life::blinker_gen()
{
	cells[2][1] = 1;
	cells[2][2] = 1;
	cells[2][3] = 1;
}

void life::glider_gen()
{
	cells[1][1] = 1;
	cells[3][1] = 1;
	cells[2][2] = 1;
	cells[3][2] = 1;
	cells[2][3] = 1;
}

void life::glider_cannon()
{
	cells[25][1] = 1;
	cells[23][2] = 1;
	cells[25][2] = 1;

	cells[13][3] = 1;
	cells[14][3] = 1;
	cells[21][3] = 1;
	cells[22][3] = 1;
	cells[35][3] = 1;
	cells[36][3] = 1;

	cells[12][4] = 1;
	cells[16][4] = 1;
	cells[21][4] = 1;
	cells[22][4] = 1;
	cells[35][4] = 1;
	cells[36][4] = 1;

	cells[1][5] = 1;
	cells[2][5] = 1;
	cells[11][5] = 1;
	cells[17][5] = 1;
	cells[21][5] = 1;
	cells[22][5] = 1;

	cells[1][6] = 1;
	cells[2][6] = 1;
	cells[11][6] = 1;
	cells[15][6] = 1;
	cells[17][6] = 1;
	cells[18][6] = 1;
	cells[23][6] = 1;
	cells[25][6] = 1;
	
	cells[11][7] = 1;
	cells[17][7] = 1;
	cells[25][7] = 1;

	cells[12][8] = 1;
	cells[16][8] = 1;
	cells[13][9] = 1;
	cells[14][9] = 1;
}

void life::change_type(int t)
{
	type = t;
}

void life::moving()                      //evolve by one step
{
	for(int x = 1; x < Dim+1; x++)
        for(int y = 1; y < Dim+1; y++)
        {
        	temp[x][y] = cells[x][y];
        }

	if(type = 1)
	{
		cells[0][0] = cells[Dim][Dim];
		cells[0][Dim+1] = cells[Dim][1];
		cells[Dim+1][0] = cells[1][Dim];
		cells[Dim+1][Dim+1] = cells[1][1];
		for(int k = 1; k < Dim+1; k++)
		{
			cells[0][k] = cells[Dim][k];
			cells[Dim+1][k] = cells[1][k];
			cells[k][0] = cells[k][Dim];
			cells[k][Dim+1] = cells[k][1];
		}
	}

        for(int x = 1; x < Dim+1; x++)
        for(int y = 1; y < Dim+1; y++)
        {
		int Sum = cells[x-1][y-1]+cells[x][y-1]+cells[x+1][y-1]
				 +cells[x-1][y]+cells[x+1][y]
				 +cells[x-1][y+1]+cells[x][y+1]+cells[x+1][y+1];
        	if(cells[x][y] == 0)
                {	
	                if(Sum == 3)
                    	{                     
                        temp[x][y] = 1;
                    	}
                }
		else
		{
			if(Sum == 2 || Sum == 3)
			{
			temp[x][y] = 1;
			}
			else
			{
			temp[x][y] = 0;
			}
		}
	}
	
	check();

        for(int x = 1; x < Dim+1; x++)
        for(int y = 1; y < Dim+1; y++)
        {
        	cells[x][y] = temp[x][y];
        }

	iter++;
}

void life::check()
{
	int z_count = 0;
	bool stable = true;
	for(int x = 1; x < Dim+1; x++)
        for(int y = 1; y < Dim+1; y++)
        {
        	z_count += temp[x][y];
		if(cells[x][y] != temp[x][y])
		{stable = false;}
        }
	if(z_count == 0)
	{
		cout << "Set is empty. System just died." << endl;
		doc_show();
		exit(0);
	}

	if(stable == true)
	{
		cout << "Stable situation" << endl;
		doc_show();
		exit(0);
	}
}

int main()
{
	life run;
	int type;
	int sys;
	cout << "Maybe open system? Type 1 for Yes, 0 for No" << endl;
	cin >> sys;
	run.change_type(sys);
	cout << "Possible systems: random (type 1), block (2), blinker (3), glider(4), glider cannon(5)" << endl;
	cin >> type;

	srand (time(NULL));
	run.generation(type);
	
	for(int k = 0; k<600; k++)
	{
	        run.moving();
		run.doc_show();
	}

    	cout << "Hello world!" << endl;
    	return 0;
}
