#include<fstream>
#include<iostream>
#include<string>
using namespace std;
#include"HugeIntegers.h"
void HugeInteger::assign(const HugeInteger&h)
{
	this->size = h.size;
	this->Ds = new int[this->size];
	for (int di = 0; di < h.size; di++)
	{
		this->Ds[di] = h.Ds[di];
	}
	this->isNeg = h.isNeg;
}
HugeInteger::HugeInteger()
{
	this->size = 0;
	this->Ds = nullptr;
	this->isNeg = false;
}
HugeInteger::HugeInteger(int s)
{
	this->size = s;
	this->Ds = new int [s] {};
	this->isNeg = false;
}
void HugeInteger::insert_at_end(int*& vs, int& size, int t)
{
	int* ha = new int [size + 1] {};
	for (int i = 0; i < size; i++)
		ha[i] = vs[i];
	ha[size] = t;
	delete[]vs;
	vs = ha;
	size++;
}
HugeInteger::HugeInteger(const HugeInteger&h)
{
	assign(h);
}
void HugeInteger::load_integer(ifstream& rdr) 
{
	char sym;
	sym = rdr.peek();
	if (sym == '-')
	{
		this->isNeg = true;
		rdr.ignore();
	}
	else
	{
		this->isNeg = false;
	}
	string aline;
	getline(rdr, aline);
	this->size = aline.size();
	this->Ds = new int[this->size];
	for (int di = 0; di < this->size; di++)
	{
		this->Ds[this->size - di - 1] = aline[di] - '0';
	}
	//rdr.get(sym);
	//while (rdr && sym != '\n')
	//{
	//	int d = sym - '0';
	//	insert_at_end(this->Ds, this->size, d);
	//	rdr.get(sym);
	//}
}
HugeInteger::HugeInteger(ifstream& rdr)
{
	this->load_integer(rdr);
}
const HugeInteger&HugeInteger:: operator=(const HugeInteger&h)
{
	if (this == &h)
		return *this;
	delete[] this->Ds;
	this->assign(h);
	return* this;
}
ostream& operator<<(ostream&, const HugeInteger&h)
{
	cout << ((h.isNeg) ? "-" : "+");
	for (int i = 0; i < h.size; i++)
	{
		cout << h.Ds[h.size - 1 - i];
	}
	return cout;
}
const HugeInteger HugeInteger::add(const HugeInteger& h)const
{
	int o = this->size;
	HugeInteger R(this->size + 1);
	int carry = 0;
	for (int i = 0; i < R.size; i++)
	{
		int ans = ((*this)[i] + h[i] + carry) % 10;
		carry = ((*this)[i] + h[i] + carry) / 10;
		R[i] = ans;
	}
	//R.trim();
	return R;
}
const HugeInteger HugeInteger::sub(const HugeInteger& h)const
{
	HugeInteger R(this->size + 1);
	int carry = 0;
	for (int i = 0; i < R.size; i++)
	{
		int ans = ((*this)[i] - h[i] - carry) % 10;
		carry = (ans < 0) ? 1 : 0;
		ans = (ans < 0) ? ans + 10 : ans;
		R[i] = ans;
	}
	R.trim();
	return R;
}
int& HugeInteger:: operator[](int i)
{
	return this->Ds[i];
}
int HugeInteger::operator[](int i)const
{
	if (i >= this->size)
		return 0;
	return this->Ds[i];
}
bool HugeInteger::quantity_wise_lesser(const HugeInteger& h)const
{
	if (this->size < h.size)
		return true;
	if (this->size > h.size)
		return false;
	for (int i = this->size - 1; i >= 0; i--)
	{
		if ((*this)[i] < h[i])
			return true;
		if ((*this)[i] > h[i])
			return false;
	}
	return false;
}
bool HugeInteger::quantity_wise_greater(const HugeInteger& h)const
{
	return h.quantity_wise_lesser(*this);
}
bool HugeInteger::quantity_wise_equal(const HugeInteger& h)const
{
	if (this->size != h.size)
		return false;
	for (int i = 0; i < this->size; i++)
		if ((*this)[i] != h[i])
			return false;
	return true;
}
bool HugeInteger::quantity_wise_greater_or_equal(const HugeInteger& h)const
{
	return ((*this).quantity_wise_equal(h) || (*this).quantity_wise_greater(h));
}
bool HugeInteger::quantity_wise_lesser_or_equal(const HugeInteger& h)const
{
	return ((*this).quantity_wise_equal(h) || (*this).quantity_wise_lesser(h));
}
bool HugeInteger::quantity_wise_not_equal(const HugeInteger& h)const
{
	return !(this->quantity_wise_equal(h));
}
const HugeInteger HugeInteger:: operator+(const HugeInteger& h)const
{
	int ii = this->size;
	if (this->isNeg == h.isNeg)
	{
		if (this->quantity_wise_greater(h))
		{
			HugeInteger R = add(h);
			R.isNeg = this->isNeg;
			R.trim();
			return R;
		}
		else
		{
			HugeInteger R = h.add(*this);
			R.isNeg = h.isNeg;
			R.trim();
			return R;
		}
	}
	else
	{
		if (this->quantity_wise_greater(h))
		{
			HugeInteger R = sub(h);
			R.isNeg = this->isNeg;
			R.trim();
			return R;
		}
		else
		{
			HugeInteger R = h.sub(*this);
			R.isNeg = h.isNeg;
			R.trim();
			return R;
		}
	}
}
const HugeInteger HugeInteger::operator-()const
{
	HugeInteger r = *this;
	r.isNeg = !(r.isNeg);
	return r;
}
const HugeInteger HugeInteger:: operator-(const HugeInteger& h)const
{
	return (*this) + (-h);
}
bool HugeInteger::operator>(const HugeInteger&h)const
{
	if (this->isNeg != h.isNeg)
		return this->isNeg == true;
	else if (this->isNeg == true)
		return this->quantity_wise_greater(h);
	else
		return this->quantity_wise_lesser(h);
}
bool HugeInteger::operator<(const HugeInteger& h)const
{
	return h > (*this);
}
const HugeInteger HugeInteger::operator++()
{
	*this = *this + one();
	return *this;
}
bool HugeInteger::operator==(const HugeInteger&h)const
{
	if (this->isNeg != h.isNeg)
		return false;
	if (this->size != h.size)
		return false;
	for (int i = 0; i < this->size; i++)
		if ((*this)[i] != h[i])
			return false;
	return true;
}
bool HugeInteger:: operator<=(const HugeInteger& h) const
{
	if ((*this == h) || (*this > h))
		return true;
}
bool HugeInteger:: operator>=(const HugeInteger& h) const
{
	return (((*this) < h) || ((*this) == h));
}
const HugeInteger HugeInteger ::operator+=(const HugeInteger& h)
{
	*this = *this + h;
	return *this;
}
const HugeInteger HugeInteger ::operator-=(const HugeInteger& h)
{
	*this = *this - h;
	return *this;
}
const HugeInteger HugeInteger ::operator*(const HugeInteger& h)const
{
	HugeInteger answer, r = *this, t = t.zero(), count = count.one(), c = h;
	if (this->isNeg == true && h.isNeg == true || this->isNeg == false && h.isNeg == false)
		t.isNeg = false;
	else
		t.isNeg = true;
	for (HugeInteger c = h; c < answer.zero(); c = c - count)
	{
		for (count = count.one(), r = (*this); count+count <= c; r = r + r)
			count += count;
		t = t + r;
	}
	return t;
}

const HugeInteger HugeInteger::operator*=(const HugeInteger& h)
{
	*this = *this * h;
	return *this;
}
const HugeInteger HugeInteger:: operator/( HugeInteger& H)const
{
	HugeInteger r = *this, t = t.zero(), count = count.one(), B = H, c = c.zero();
	r.isNeg = false;
	B.isNeg = false;
	if (r > B)
	{
		return c;
	}
	if (H.isNeg == true)
	{
		H.isNeg = false;
		for (; r >= H; c += count, r -= B)
		{
			count = count.one();
			for (B = H; B + B <= r; B += B, count += count);
		}
		H.isNeg = true;
	}
	else
	{
		for (; r >= H; c += count, r -= B)
			for (B = H, count = count.one(); B + B <= r; B += B, count += count);
	}
	c.isNeg = (this->isNeg != H.isNeg);
	return c;
}
void HugeInteger::trim()
{
	int i = this->size - 1;
	int count = 0;
	while (Ds[i] == 0)
	{
		if (Ds[i] == 0)
		{
			for (int k = i; k < size; k++)
			{
				Ds[k] = Ds[k + 1];
			}
			count++;
		}
		i--;
	}
	this->size = size - count;
	int* h = new int[size];
	for (int tr = 0; tr < size; tr++)
		h[tr] = Ds[tr];
	this->Ds = new int[size];
	for (int i = 0; i < size; i++)
		Ds[i] = h[i];
	delete[]h;
}
HugeInteger::~HugeInteger()
{
	delete[]this->Ds;
}
