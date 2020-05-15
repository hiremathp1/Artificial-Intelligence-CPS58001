#include<iostream>
#include<fstream>
#include<string>
#include <stdlib.h>
#include<math.h>
using namespace std;

struct model
{
    double w0;
    double w1;
    double w2;
};
int evaluate(model M,double height,double weight)
{
    double test = 1/(1+exp(-(M.w0+M.w1*height+M.w2*weight)));
    if (test >= 0.5)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int main()
{
    ifstream file("model.txt");
    string str;
    model M;
    getline(file, str);
    M.w0 = atof(str.c_str());
    getline(file, str);
    M.w1 = atof(str.c_str());
    getline(file, str);
    M.w2 = atof(str.c_str());

    ifstream file1("test.txt");
     

    getline(file1, str);//remove the first line which is the data description
    double su = 0.0;
    int n = 0;
    while (getline(file1, str))
    {
        int y = (int)(str[0]-48);

        int a = str.size();
        int b;
        for (int j = 2; j < a; j++)
        {
            if(str[j]==' ')
            {   
                b = j;
                break;
            }
        }
        double avg_height = 66.4388;
        double std_height = 3.86941;
        double avg_weight = 161.957;
        double std_weight = 32.2341;
        double heig = stod(str.substr(2,b-1));
        double weig = stod(str.substr(b+1,a-b));
        heig = (heig-avg_height)/std_height;
        weig = (weig-avg_weight)/std_weight;
        int y1 = evaluate(M,heig,weig);
        if (y1==y)
        {
            su++;
        }
        n++;

        
    }
    cout<<"Test accuracy is: "<<(su*100)/n<<"%"<<endl;

}