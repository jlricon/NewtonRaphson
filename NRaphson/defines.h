#pragma once
#include <ostream>
#include <vector>

//Max number of iterations for NR
#define NITMAX 100
//Accuracy for NR
#define TOL 1e-5
//Max gradient allowed
#define LIMITER 1e4
//Epsilon for differentiation
#define EPSILON 1e-5
using std::vector;

//Define vector class
class Vector {
private:
	vector<double> nums;
public:
	vector<double> get_n()const { return nums; }
	vector<double>* get_np() { return &nums; }
	unsigned len() const;
	void set(std::initializer_list<double>);
	void set(vector<double> in);
	Vector(std::initializer_list<double>);
	Vector(){}
	Vector(const Vector &in);
	Vector(int siz);
	Vector(vector<double> in);
	Vector(const unsigned &rhs);
	void operator=( const double &b);
	double operator()(const unsigned & a) const;
	void assign(const  unsigned& pos, const double & val);

};
//Define Matrix class
class Matrix {
private:
	vector<vector<double>> nums;
	unsigned rows;
	unsigned cols;
public:
	vector<vector<double>> const get_n();
	vector<vector<double>>* get_np();
	unsigned get_cols() const;
	unsigned get_rows() const;
	Matrix(int r, int c);
	Matrix(const Matrix & a);
	Matrix operator=(const Matrix & a) {
		if (&a == this) return *this;
		rows = a.get_rows();
		cols = a.get_cols();
		nums.resize(a.get_rows());
		for (unsigned i = 0; i < nums.size(); i++) {
			nums[i].resize(cols);
		}
		for (unsigned i = 0; i <rows; i++) {
			for (unsigned j = 0; j < cols; j++) {
				nums[i][j] = a(i, j);
			}
		}
		return *this;
		
	}

	double operator()(const unsigned & r, const unsigned & c) const;
	Matrix inv() const;
	
	void assign(const  unsigned& i,const unsigned& j, const double & val);
	Matrix tr() const;
		
};

//Declare the overloads that are defined in the header

Vector operator+(const Vector& a, const Vector& b);
Vector operator-(const Vector& a, const Vector& b);
Vector operator-(const Vector& a, const double b);
Vector operator+(const Vector& a, const double b);
Vector operator*(const Vector& a, const Vector& b);
Vector operator*(const double& a, const Vector& b);
Vector operator/(const Vector& a, const Vector& b);
Vector operator/(const Vector& a, const double b);
std::ostream& operator<<(std::ostream& os, const Vector& obj);
Vector abs(const Vector &a);
bool operator<(const Vector &a, const double b);
bool operator>(const Vector &a, const double b);
bool isnan(const Vector &a);
Matrix operator*(const double & a, const Matrix & mat);
Matrix operator*(const Matrix & a,const Matrix & b);
Matrix operator-(const Matrix & a, const Matrix & b);
Vector operator*(const Matrix& mat, const Vector& rhs);



