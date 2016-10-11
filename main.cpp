#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string.h>

using namespace std;

const int Dim = 10;

class QW
{
    private:
        int EHP[Dim][Dim];
        int temp[Dim][Dim];
        int iter;
    public:
        QW()                                //generate empty 2D quantum well, with no excitons
        {
            for(int x = 0; x < Dim; x++)
            for(int y = 0; y < Dim; y++)
            {
                EHP[x][y] = 0;
                temp[x][y] = 0;
            }
            iter = 0;
        }
//------------------------------------------
        void doc_show()                     //write system into file in ASCII format
        {
            ofstream myfile;
            char filename[256];
            sprintf(filename,"data%d.txt",iter);
            myfile.open(filename);
            for(int x = 0; x < Dim; x++)
            {
                for(int y = 0; y < Dim; y++)
                {
                    myfile << EHP[x][y] << "\t";
                }
                myfile << "\n";
            }
            myfile.close();
        }

//------------------------------------------
        void doc_MP()                     //write system into file for MetaPost usage
        {
            ofstream myfile;
            char filename[256];
            sprintf(filename,"data%d.dat",iter);
            myfile.open(filename);
            for(int x = 0; x < Dim; x++)
            {
                for(int y = 0; y < Dim; y++)
                {
                    myfile << x << "\t" << y << "\t" << EHP[x][y] << endl;
                }
            }
            myfile.close();
        }
//------------------------------------------
        void generation()                   //randomly generate excitons in system
        {
            for(int x = 0; x < Dim; x++)
            for(int y = 0; y < Dim; y++)
            {
                int k = rand()%10;
                if(k == 0)
                {
                    EHP[x][y] += 1;
                }
            }

            iter++;
        }
 //-----------------------------------------
        void recombination()                //decreasing of EHP because of recombination
        {
            for(int x = 0; x < Dim; x++)
            for(int y = 0; y < Dim; y++)
            {
                int k = 0;
                for(int i = 0; i<EHP[x][y];i++)
                {
                    int l;
                    if(EHP[x][y] >= 10)
                    {
                        l = rand()%30;
                    }
                    else
                    {
                        l = rand()%50;
                    }

                    if(l == 1)
                    {
                        k++;
                    }
                }
                EHP[x][y] -= k;
            }
        }
//------------------------------------------
        void moving()                       //moving of exitons (exiton is in the move)
        {
            for(int x = 0; x < Dim; x++)
            for(int y = 0; y < Dim; y++)
            {
                temp[x][y] = EHP[x][y];
            }

            for(int x = 0; x < Dim; x++)
            for(int y = 0; y < Dim; y++)
            {
                for(int i = 0; i<EHP[x][y]; i++)
                {
                    int k;
                    if(EHP[x][y]>=10)           //this need to be updated because we need to consider moving of EHP in EHL for
                    {                           //necessity of constant density
                        k = rand()%8;
                    }
                    else
                    {
                        k = rand()%4;
                    }

                    switch( k )
                    {
                        case 0:
                            if(EHP[x-1][y] < 10)
                            {
                                temp[x][y] -= 1;
                                if(x != 0){temp[x-1][y] += 1;}
                            }
                        case 1:
                            if(EHP[x][y+1] < 10)
                            {
                                temp[x][y] -= 1;
                                if(y != Dim){temp[x][y+1] += 1;}
                            }
                        case 2:
                            if(EHP[x+1][y] < 10)
                            {
                                temp[x][y] -= 1;
                                if(x != Dim){temp[x+1][y] += 1;}
                            }
                        case 3:
                            if(EHP[x][y-1] < 10)
                            {
                                temp[x][y] -= 1;
                                if(y != 0){temp[x][y-1] += 1;}
                            }
                    }
                }
            }

            for(int x = 0; x < Dim; x++)
            for(int y = 0; y < Dim; y++)
            {
                EHP[x][y] = temp[x][y];
            }
        }
};

int main()
{
    QW run;

    srand (time(NULL));

    for(int l = 0; l<100; l++)
    {
        run.generation();
        run.recombination();
    }

    run.doc_show();
    run.doc_MP();

    cout << "Hello world!" << endl;
    return 0;
}
