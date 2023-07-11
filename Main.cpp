#include<iostream>
#include<string>
#include<fstream>
using namespace std;
#include"HugeIntegers.h"
void load_all_integers(int size, HugeInteger* his,ifstream& rdr)
{
	for (int i = 0; i < size; i++)
	{
		while (rdr.peek() == '\n' || rdr.peek() == ' ')
			rdr.ignore();
		his[i].load_integer(rdr);
	}
}
void load_all_integers_2(int size, HugeInteger** his, ifstream& rdr)
{
	for (int i = 0; i < size; i++)
	{
		while (rdr.peek() == '\n' || rdr.peek() == ' ')
			rdr.ignore();
		his[i] = new HugeInteger(rdr);
	}
}
void print_all_integes(int size,HugeInteger*his)
{
	for (int i = 0; i < size; i++)
	{
		cout << his[i] << endl;
	}
}
void print_all_integes_2(int size, HugeInteger** his)
{
	for (int i = 0; i < size; i++)
	{
		cout << *his[i] << endl;
	}
}
int main() 
{
	ifstream rdr("Source.txt");
	int Isize;
	HugeInteger* his;
	HugeInteger** his_2;
	rdr >> Isize;
	his_2 = new HugeInteger * [Isize];
	his = new HugeInteger[Isize];
	//load_all_integers(Isize, his, rdr);
	load_all_integers_2(Isize, his_2, rdr);
	//print_all_integes(Isize, his);
	print_all_integes_2(Isize, his_2);
	(*his_2)[0].trim();
	//cout << (*his_2)[0] << endl;
	//cout << endl << endl << his_2[1]->add(*his_2[0]) << endl;
	HugeInteger R = *(his_2[0]);
	//R = (R + (*his_2)[0]) ;
	R;
	HugeInteger b = (*his_2[3]);
	//cout << (b <= R)<<endl;
	HugeInteger f ;
	f = R * b;
	cout << f << endl;
	//f = f * b;
	//cout << f << endl;
	//cout << (d > f) << endl;
}