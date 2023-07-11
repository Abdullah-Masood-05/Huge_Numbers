//#include<iostream>
#include<fstream>
#pragma once
class HugeInteger

{
	int* Ds;
	int size;
	bool isNeg;
	void assign(const HugeInteger&);
	static void insert_at_end(int*& vs, int& size, int t);
	const HugeInteger add(const HugeInteger& h)const;
	const HugeInteger sub(const HugeInteger& h)const;
	bool quantity_wise_lesser(const HugeInteger& h)const;
	bool quantity_wise_greater(const HugeInteger& h)const;
	bool quantity_wise_equal(const HugeInteger& h)const;
	bool quantity_wise_greater_or_equal(const HugeInteger& h)const;
	bool quantity_wise_lesser_or_equal(const HugeInteger& h)const;
	bool quantity_wise_not_equal(const HugeInteger& h)const;
	static HugeInteger one()
	{
		HugeInteger R(1);
		R.Ds[0] = 1;
		return R;
	}
	static HugeInteger zero()
	{
		HugeInteger R(1);
		R.Ds[0] = 0;
		return R;
	}
public:
	HugeInteger();
	HugeInteger(int s);
	HugeInteger(const HugeInteger&);
	void load_integer(ifstream& rdr);
	HugeInteger(ifstream& rdr);
	const HugeInteger operator+(const HugeInteger&)const;
	const HugeInteger operator-()const;
	const HugeInteger operator-(const HugeInteger& h)const;
	const HugeInteger operator*(const HugeInteger& h)const;
	const HugeInteger operator*=(const HugeInteger& h);
	const HugeInteger operator/( HugeInteger& )const;
	bool operator>(const HugeInteger&)const;
	bool operator<(const HugeInteger&)const;
	bool operator==(const HugeInteger&)const;
	bool operator>=(const HugeInteger& h) const;
	bool operator<=(const HugeInteger& h) const;
	const HugeInteger operator+=(const HugeInteger& h);
	const HugeInteger operator-=(const HugeInteger& h);
	const HugeInteger operator++();
	void trim();
	int& operator[](int i);
	int operator[](int i)const;
	const HugeInteger& operator=(const HugeInteger&);
	friend ostream& operator<<(ostream&, const HugeInteger&);
	~HugeInteger();
};

