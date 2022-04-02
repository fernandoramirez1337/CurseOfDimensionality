#include <iostream>
#include <random>
#include <math.h>
#include <iomanip>  
#include <ctime>
#include <chrono> 
using namespace std;

#define NPOINTS 20000

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> distrib(1,1000);

template <int N> struct canvas;
template <int N> struct point;

template <int N> struct canvas
{
    point<N> points[NPOINTS];
    double min,max;
    int list[10] = {0};
    canvas()
    {
        max = 0;
        min = numeric_limits<double>::max();
        points[0].dist=0;
        for (int i = 1; i < NPOINTS; i++)
        {
            double tmp_ = 0;
            for (int j = 0; j < N; j++)
            {
                tmp_ += pow(points[0].data[j]-points[i].data[j],2);
            }
            points[i].dist = sqrt(static_cast<double>(tmp_)); 

            if(points[i].dist>max) max=points[i].dist;
            if(points[i].dist<min) min=points[i].dist;
        } 
        for (int i = 1; i < NPOINTS; i++)
        {
            points[i].dist = (points[i].dist-min)/(max-min);
            for (int j = 1; j <= 10; j++)
            {
                if(points[i].dist <= static_cast<double>(j)/10)
                {
                    list[j-1]++;
                    j=11;
                }
            }
        }   
    }
};

template <int N> struct point
{
    int data[N];
    double dist;
    point()
    {
        for (int i = 0; i < N; i++)
        {
            data[i]=distrib(gen);
        }
    }
};

int main()
{
    chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = chrono::high_resolution_clock::now();

    const int dimeeeeee = 25;
    cout << fixed;
    cout.precision(1);

    canvas<dimeeeeee> canv;
    cout<<endl<<"Curse of Dimensionality"<<endl;
    cout<<"Number of points: "<<NPOINTS<<endl;
    cout<<"Number of dimensions: "<<dimeeeeee<<endl;
    cout<<"Ratio: (min: "<<canv.min<<" max: "<<canv.max<<")"<<endl;
    int eval = 0;
    for (int i = 0; i < 10; i++)
    {
        cout<<static_cast<double>(i+1)/10<<"  "<<canv.list[i]<<endl;
        eval+=canv.list[i];
    }
    cout<<"Evaluated points: "<<eval<<endl;

    end = std::chrono::high_resolution_clock::now();
    int duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    cout<<"Duration: "<<duration<<endl<<endl;   
    return 0;
}