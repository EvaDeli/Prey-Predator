//PS courework prototype
// 14/10/2013
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstring>

using namespace std;


int main(){
        float r = 0.08f; //hare birth rate
        float a = 0.04f; //predation rate
        float b = 0.02f; //birth rate puma per hare eaten
        float m = 0.06f; //puma mortality rate
        float k = 0.02f; //hare diffusion rate
        float l = 0.02f; //puma diffusion rate
        float delta_t = 0.4f; //time step;

        const int grid_x = 2;
        const int grid_y = 2;

        int grid[grid_y+2][grid_x+2];
        //tropos desmeumhs monosdiastatos dynamikou pinakas
        float* h_A = new float[(grid_y+2)*(grid_x+2)];
        float* h_B = new float[(grid_y+2)*(grid_x+2)];
        float* p_A = new float[(grid_y+2)*(grid_x+2)];
        float* p_B = new float[(grid_y+2)*(grid_x+2)];
        //arxikopoiei to h_old klp, deixnoun sthn idia mnhmh
        float* h_old = h_A;
        float* h_new = h_B;
        float* p_old = p_A;
        float* p_new = p_B;

        //sizeof(float) or (int)
        memset(grid, 0x00, sizeof(int)*(grid_y+2)*(grid_x+2));
        memset(h_A,  0x00, sizeof(int)*(grid_y+2)*(grid_x+2));
        memset(h_B,  0x00, sizeof(int)*(grid_y+2)*(grid_x+2));
        memset(p_A,  0x00, sizeof(int)*(grid_y+2)*(grid_x+2));
        memset(p_B,  0x00, sizeof(int)*(grid_y+2)*(grid_x+2));

        //open up file for landscape to copy grid into landscape.dat
		/*fstream FHandle;
		FHandle.open("grades.dat", ios::out);
		if(FHandle.is_open())
			cout << "Opened !";
		else
			cout << "Not Opened !";*/
        //.txt kalutera... ofstream anoigei reuma (stream) gia na diavasei apto arxeio, landscape anti cout (<<) edw...
		ofstream landscape;
		landscape.open ("landscape.dat");
		landscape << grid_x << grid_y <<"\n";
        //tyxaios arithmos cid
		srand(time(0));
        //init grid, hare, and puma

        for(int y = 1; y <= grid_y ; ++y){
                for(int x = 1; x <= grid_x; ++x){
                        //giati to periorizei se 2,3?? kanei grammiko ton pinaka k ta pernaei etsi . algorithmos
                        if(y == 1 && x == 1){
                                grid[y][x]=0;
                                h_old[y*(grid_x+2)+x]=0;
                                p_old[y*(grid_x+2)+x]=0;
                        } else {
                                grid[y][x]=1;
                                h_old[y*(grid_x+2)+x]=rand()%5;
                                p_old[y*(grid_x+2)+x]=rand()%5;
                        }
                         //cout<<"grid ["<< y << "," << x <<"] is : "<< grid [y][x]<<endl;
                }
            //landscape << "\n";
        }

	cout << "Grid: " << std::endl;
	for(int y = 0; y < grid_y+2 ; ++y){
        	for(int x = 0; x < grid_x + 2; ++x){
			std::cout << grid[y][x] << " ";
		}
		std::cout << std::endl;
	}
	cout << std::endl;
	cout << std::endl;


        for(int y = 1; y <= grid_y ; ++y){
                for(int x = 1; x <= grid_x; ++x){
                        cout<<"h["<< y<< "," << x<< "] : "<< h_old[y*(grid_x+2)+x] << "  p["<< y<< ","<< x << "] : " << p_old[y*(grid_x+2)+x] << endl;

                 }
        }
        //end initialization
        //

		landscape.close(); //closing write file

        std::cout << "Begin simulation..."<< endl;
        //mesure begin time
	int width = grid_x+2;
        for(float T=0; T<0.3; T=T+delta_t){
                for(int y = 1; y <= grid_y; ++y){// y=0, y<grid_y
                        for(int x = 1; x <= grid_x; ++x){//x=0, x<grid_x
			if(grid[y][x] != 0){
									int N =
											grid[y][x-1] + grid[y][x+1]+
											grid[y-1][x] + grid[y+1][x];

									float hare_old = h_old[y*width+x];
									float puma_old = p_old[y*width+x];

									//As given in the problem statement
									h_new[y*width+x] =
											 hare_old+delta_t*
											(
											 r*hare_old-a*hare_old*puma_old+//xehase puma_old
											 k*((
											 h_old[(y-1)*width+x]+
											 h_old[(y+1)*width+x]+
											 h_old[(y)*width+(x-1)]+
											 h_old[(y)*width+(x+1)]
											 ) - N*hare_old)
											);

									p_new[y*width+x]=
											puma_old + delta_t*
											(
											 b*hare_old*puma_old - m*puma_old +
											 l*((
											  p_old[(y-1)*width+x]+
											  p_old[(y+1)*width+x]+
											  p_old[(y)*width+(x-1)]+
											  p_old[(y)*width+(x+1)]
											 )-N*puma_old)
											);
                                cout<<" hare ["<<y<<"],["<<x<<"]: "<< h_new[y*width+x]<<endl << "puma ["<<y<<"],["<<x<<"] :"<< p_new[y*width+x]<< endl<<endl;
				}
                        }

                }

                //Things to do
                //calculate and display  average
                //dump new values to file


                //swap pointers
                //mporw na to kanw synarthsh
                float* p_temp = p_old;
                p_old = p_new;
                p_new = p_temp;

                float* h_temp = h_old;
                h_old = h_new;
                h_new = h_temp;
	}


        //Things to do
        //measure end time and display difference.
        //na bgalw to std
        std::cout << "end" << std::endl;
        //svhnie mnhmh pou exei desmeush dynamika
        delete[] h_A;
        delete[] h_B;
        delete[] p_A;
        delete[] p_B;

        return 1;
}


