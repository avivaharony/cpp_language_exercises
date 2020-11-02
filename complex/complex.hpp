#ifndef COMPLEX_HPP_
#define COMPLEX_HPP_

#include <iosfwd> 		// operator<<
#include <sstream>		// std::stringstream

namespace ilrd
{

class Complex;
//Free Functions
// general : c is variable of type Complex, d is variable of type double 
// if (c==c), if (c == d), if (d==c)
inline bool operator==(const Complex& lhs, const Complex& rhs);
// if (c != c), if (c != d), if (d != c)
inline bool operator!=(const Complex& lhs, const Complex& rhs);

//c1 = c2 + c3, c1 = c + d, c1 = d + c
//const return value to reject (c1 + c2) = c3
inline const Complex operator+(const Complex& lhs, const Complex& rhs);
inline const Complex operator-(const Complex& lhs, const Complex& rhs);
inline const Complex operator*(const Complex& lhs, const Complex& rhs);
inline const Complex operator/(const Complex& lhs, const Complex& rhs);

inline std::ostream& operator<<(std::ostream& os, const Complex& c);
inline std::istream& operator>>(std::istream& is, Complex& c);

class Complex
{
public:

	inline Complex(double real = 0, double imag = 0);	//CTOR - non explicit on purpose
	// ~Complex() = default;
	// Complex(Complex& other) = default;
	// Complex& operator=(const Complex& other) = default;
	
	// c1 += c2, c1 += d, c1 += c2 += c3
	inline Complex& operator+=(const Complex& other);
	inline Complex& operator-=(const Complex& other);
	inline Complex& operator*=(const Complex& other);
	inline Complex& operator/=(const Complex& other);

	double get_real() const;
	double get_imag() const;
	void set_real(double real);
	void set_imag(double imag);
	
private:
	
	double m_real;
	double m_imag;

};	// end class Complex

inline Complex::Complex(double real, double imag)
		:m_real(real),
		m_imag(imag)
{}

// -------------------------------------------------

inline bool operator==(const Complex& lhs, const Complex& rhs)
{
	return ((lhs.get_real() == rhs.get_real()) &&
			 (lhs.get_imag() == rhs.get_imag())); 
}

inline bool operator!=(const Complex& lhs, const Complex& rhs)
{
	return (!(lhs == rhs)); 
}

// -------------------------------------------------

inline const Complex operator+(const Complex& lhs, const Complex& rhs)
{
	Complex result(lhs);
	result += rhs;
	
	return (result);
}

inline const Complex operator-(const Complex& lhs, const Complex& rhs)
{
	Complex result(lhs);
	result -= rhs;
	
	return (result);
}

	
//(a+bi)*(c+di) = (a*c - b*d) + i*(b*c + a*d);
inline const Complex operator*(const Complex& lhs, const Complex& rhs)
{
	Complex result(lhs);
	result *= rhs;
	
	return (result);
}

// (a+bi) / (c+di) = (a*c + b*d)/(c^2 + d^2) + i* (b*c - a*d)/(c^2 + d^2);
inline const Complex operator/(const Complex& lhs, const Complex& rhs)
{
	Complex result(lhs);
	result /= rhs;
	
	return (result);
}

// -------------------------------------------------
inline std::ostream& operator<<(std::ostream& os, const Complex& c)
{
	return (os << "(" << c.get_real() << ", " << c.get_imag() << ")") ;
}

inline std::istream& operator>>(std::istream& is, Complex& c)
{
	std::string str;
	std::stringstream str_stream;

	std::getline(is, str);
	str_stream << str;

	char ch1, ch2, ch3;
	double real = 0.0;
	double imag = 0.0; 

	str_stream >> ch1 >> real >> ch2 >> imag >> ch3;

	if ((ch1 != '(' ) || (ch2 != ',') || (ch3 != ')'))
	{
		is.setstate(std::ios_base::failbit);
		return is;
	}
	
	c.set_real(real);
	c.set_imag(imag);
	
	return is;
}


// -------------------------------------------------
// -------------------------------------------------

inline Complex& Complex::operator+=(const Complex& other)
{
	m_real += other.m_real;
	m_imag += other.m_imag;

	return (*this);
	
}

inline Complex& Complex::operator-=(const Complex& other)
{
	m_real -= other.m_real;
	m_imag -= other.m_imag;

	return (*this);
}

inline Complex& Complex::operator*=(const Complex& other)
{
	double a = m_real;
	double b = m_imag;
	double c = other.m_real;
	double d = other.m_imag;
	
	
	m_real = (a * c) - (b * d);
	m_imag = (b * c) + (a * d);

	return (*this);
}

inline Complex& Complex::operator/=(const Complex& other)
{
	double a = m_real;
	double b = m_imag;
	double c = other.m_real;
	double d = other.m_imag;
	
	double divisor = c * c + d *d;

	m_real = (a * c + b * d) / divisor;
	m_imag = (b * c - a * d) / divisor;
	
	return (*this);
}


// -------------------------------------------------
double Complex::get_real() const
{
	return (m_real);
}

double Complex::get_imag() const
{
	return (m_imag);
}

void Complex::set_real(double real)
{
	m_real = real;
}

void Complex::set_imag(double imag)
{
	m_imag = imag;
}

// -------------------------------------------------
	
}	//namespace ilrd

#endif   /*   COMPLEX_HPP_    */ 
