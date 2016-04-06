#include<vector>
#include<functional>
#include <iterator>
#include <algorithm>
#include <ostream>
#include <iostream>
#include "defines.h"
using std::vector;

Vector::Vector(const  Vector &in) { nums = in.get_n(); }
Vector::Vector(vector<double> in) { nums = in; }
Vector::Vector(std::initializer_list<double> i) { nums = i; }
Vector::Vector(int siz) { nums.resize(siz, 0); }
void Vector::set(std::initializer_list<double> in) { nums = in; }
void Vector::set(vector<double> in) { nums = in; }
int Vector::len() const { return nums.size(); }


std::ostream& operator<<(std::ostream& os, const Vector& obj)
{
	os << obj.get_n()[0] << " " << obj.get_n()[1];
	return os;
}
Vector operator+(const Vector& a, const Vector& b) {
	Vector result;
	vector <double> work;
	vector <double> va=a.get_n();
	vector <double> vb=b.get_n();
	work.reserve(va.size());
	std::transform(va.begin(), va.end(), vb.begin(),std::back_inserter(work), std::plus<double>());
	result.set(work);
	return result;
}
Vector operator-(const Vector& a, const Vector& b) {
	
	vector <double> work;
	vector <double> va = a.get_n();
	vector <double> vb = b.get_n();
	//work.reserve(a.len());
	std::transform(va.begin(),va.end(), vb.begin(), std::back_inserter(work), std::minus<double>());
	Vector result(work);
	return result;
}
Vector operator-(const Vector & a, const double b)
{
	Vector result;
	vector <double> va = a.get_n();
	std::transform(va.begin(), va.end(), va.begin(), bind2nd(std::minus<double>(), b));
	result.set(va);
	return result;
}
Vector operator+(const Vector& a, const double b) {
	Vector result;
	vector <double> va = a.get_n();
	std::transform(va.begin(), va.end(), va.begin(),bind2nd(std::plus<double>(), b));
	result.set(va);
	return result;
	}
Vector operator*(const Vector& a, const Vector& b) {
	Vector result;
	vector <double> work;
	work.reserve(a.get_n().size());
	std::transform(a.get_n().begin(), a.get_n().end(), b.get_n().begin(), std::back_inserter(work), std::multiplies<double>());
	result.set(work);
	return result;
}
Vector operator*(const double & a, const Vector & b)
{
	Vector result;
	vector <double> va = b.get_n();
	std::transform(va.begin(), va.end(), va.begin(), bind2nd(std::plus<double>(), a));
	result.set(va);
	return result;
}
Vector operator/(const Vector& a, const Vector& b) {
	Vector result;
	vector <double> work;
	work.reserve(a.get_n().size());
	std::transform(a.get_n().begin(), a.get_n().end(), b.get_n().begin(), std::back_inserter(work), std::divides<double>());
	result.set(work);
	return result;
}
Vector operator/(const Vector& a, const double b) {
	Vector result;
	vector <double> va = a.get_n();
	std::transform(va.begin(), va.end(), va.begin(), bind2nd(std::divides<double>(), b));
	result.set(va);
	return result;
}

Vector abs(const Vector &a) {
	Vector result;
	vector <double> va = a.get_n();
	for (int i = 0; i < va.size(); i++) {
		if (va[i] < 0) va[i] = -va[i];
	}
	result.set(va);
	return result;
}
bool operator<(const Vector &a, const double b) {
	vector <double> va = a.get_n();
	for (int i = 0; i < va.size(); i++) {
		if (va[i] > b) return 0;
	}
	return 1;
}
bool operator>(const Vector &a, const double b) {
	vector <double> va = a.get_n();
	for (int i = 0; i < va.size(); i++) {
		if (va[i] < b) return 0;
	}
	return 1;
}

void Vector::operator=( const double& b) {
	vector <double> va = this->get_n();
	for (int i = 0; i < va.size(); i++) {
		this->assign(i, b);
	
	}
	
}

bool isnan(const Vector& a) {
	vector <double> va = a.get_n();
	for (int i = 0; i < va.size(); i++) {
		if (isnan(va[i])) return 1;
	}
	return 0;
}

Vector::Vector(const unsigned &a) {
	nums.resize(a);
}

double Vector::operator()(const unsigned & a) const {
	return this->nums[a];
}

void Vector ::assign(const unsigned & pos, const double & val){
	nums[pos] = val;
}


//We need operators for vector/matrix

vector<vector<double>>  Matrix::get_n() { return nums; }
vector<vector<double>>*  Matrix::get_np() { return &nums; }
Matrix::Matrix(int r, int c) {
	rows = r;
	cols = c;
	nums.resize(r);
	for (unsigned i = 0; i < nums.size(); i++) {
		nums[i].resize(cols,0);
	}

}
Matrix::Matrix(const Matrix & a) {
	nums = a.nums;
	rows = a.get_rows();
	cols = a.get_cols();
}
unsigned Matrix::get_cols() const { return cols; }
unsigned Matrix::get_rows() const { return rows; }
double Matrix::operator()(const unsigned & r, const unsigned & c) const {
	return this->nums[r][c];
}


Vector Matrix::operator*(const Vector& rhs) {
	Vector result(rhs.len());

	for (unsigned i = 0; i<rows; i++) {
		for (unsigned j = 0; j<cols; j++) {
			result.assign(i, this->nums[i][j] * rhs(j)+result(i));
			
		}
	}

	return result;
}


Matrix Matrix::inv()const {
	Matrix ret = *this;
	try {
		if (ret.get_cols() == ret.get_rows()) {
			if (ret.get_cols() == 1) {
			ret.assign(0, 0, 1 / ret(0, 0));
			return ret;
		}
			else if (this->get_cols() == 2) {
				double i = ret(0, 0);
				double det = ret(0, 0)*ret(1, 1) - ret(0, 1)*ret(1, 0);
				ret.assign(0, 0, ret(1, 1)/det);
				ret.assign(1, 0, -ret(1, 0)/det);
				ret.assign(0, 1, -ret(0, 1)/det);
				ret.assign(1, 1, i/det);
				return ret;

			}

		}
		else {
			throw(2);
		}
	}
	catch (int n) { std::cout <<n<< " Matrices are not equal!"; }
	
}

void Matrix::assign(const unsigned & i, const unsigned& j, const double&val) {
	nums[i][j] = val;
}
