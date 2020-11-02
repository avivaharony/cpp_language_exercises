#include <cstring> //memcpy, strlen ,strcmp
#include <istream> //std::istream::getline()

#include "../utils.h"
#include "string.hpp"

#include <iostream>
using std::cout;


namespace ilrd
{

char* Str::create_and_copy_str(char* dest, const char* str)
{
	size_t length = strlen(str);
	dest = new char[length + 1]; 
	memcpy(dest, str, length + 1);
	
	return (dest);
}

Str::Str(const char* str)
{
	m_cp = create_and_copy_str(m_cp, str);
}

Str::~Str()
{
	delete[] m_cp;
	m_cp = nullptr;
}

Str::Str(const Str& other)
{
	m_cp = create_and_copy_str(m_cp, other.m_cp);
}

Str& Str::operator=(const Str& other)
{
	char *new_str = nullptr;
	new_str = create_and_copy_str(new_str, other.m_cp);
	
	delete[] m_cp;
	m_cp = new_str;

	return (*this);
}

// -------------------------------------------------

size_t Str::length() const
{
	return (strlen(m_cp));
}

const char* Str::to_c_string() const
{
	return (m_cp);
}
	
// -------------------------------------------------
	
std::ostream& operator<<(std::ostream& out_s, const Str& cp)
{
	return (out_s << cp.to_c_string());
}


/********/
std::istream& operator>>(std::istream& in_s, Str& cp)
{
	const int max_buffer_len = 256;
	char input_str[max_buffer_len] = {0};
	Str new_str;
	
	while (in_s.get(input_str, max_buffer_len))
	{
		new_str+= input_str;
	}
	
	in_s.clear();
	in_s.ignore();

	cp = new_str;
	
	return (in_s);
}
/*********/
// -------------------------------------------------

// if (s1 == s2) , (s1 != s2), (s1=="hk"), ("hello" == s1)
bool operator==(const Str& lhs, const Str& rhs)
{
	return (0 == strcmp(lhs.to_c_string(), rhs.to_c_string()));
}

bool operator!=(const Str& lhs, const Str& rhs)
{
	return (0 != strcmp(lhs.to_c_string(), rhs.to_c_string()));
}
// if (s1 > s2) , (s1 > "hk"), ("hk" > s1),
bool operator>(const Str& lhs, const Str& rhs)
{
	return (strcmp(lhs.to_c_string(), rhs.to_c_string()) > 0);
}

bool operator<(const Str& lhs, const Str& rhs)
{
	return (strcmp(lhs.to_c_string(), rhs.to_c_string()) < 0);
}
	
// -------------------------------------------------
char& Str::operator[](size_t index)
{
	return (m_cp[index]);
}

// const str ;if (s[1]== 'a') . if ('a' == str[1]); . char c = s[2];
char Str::operator[](size_t index) const
{
	return (m_cp[index]);
}
	
// -------------------------------------------------
// concatenate s2.to s1
Str& Str::concat (const Str& other)
{	
	size_t old_length = length();
	size_t other_length = other.length();
	size_t new_length = old_length + other_length;
	char *str_new = new char[new_length + 1];
	
	memcpy(str_new, m_cp, old_length);
	memcpy(str_new + old_length, other.m_cp, other_length + 1);

	delete[] m_cp;
	m_cp = str_new;	

	return (*this);
}

Str& Str::operator+=(const Str& other) // s1+=s2; s1+="hello";
{
	return (concat(other));
}	

// -------------------------------------------------


} // end namespace ilrd
