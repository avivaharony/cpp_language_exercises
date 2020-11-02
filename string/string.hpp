#ifndef STRING_HPP_
#define STRING_HPP_

#include <iosfwd> // operator<< , size_t

namespace ilrd
{

class Str;

//Free Functions
std::ostream& operator<<(std::ostream& outs, const Str& cp);	// cout << s
std::istream& operator>>(std::istream& ins, Str& cp);			// cin >> s

// if (s1 == s2) , (s1 != s2), (s1=="hk"), ("hello" == s1)
bool operator==(const Str& lhs, const Str& rhs);

bool operator!=(const Str& lhs, const Str& rhs);
// if (s1 > s2) , (s1 > "hk"), ("hk" > s1),
bool operator>(const Str& lhs, const Str& rhs);
bool operator<(const Str& lhs, const Str& rhs);

class Str
{
public:
	Str(const char* str = ""); // default CTOR : str s , str s("hello"), str s="hello". non-explicit on purpose
	
	~Str();					//DTOR

	Str(const Str& other); // CCTOR : Str s(s1)
	// Assignment operator : s1 = s2 , s1=s2=s3 , s1=s2=s3="hello". 
	Str& operator=(const Str& other);
	// s[2] = 'a', if (s[1]== 'a').
	char& operator[](size_t index);
	// const str ;if (s[1]== 'a') . if ('a' == str[1]); . char c = s[2];
	char operator[](size_t index) const;
	// concatenate s2.to s1
	Str& concat (const Str& other);
	Str& operator+=(const Str& other); // s1+=s2; s1+="hello";
	
	size_t length() const;
	// puts(s1.to_c_string());
	const char* to_c_string() const;

	friend std::istream& operator>>(std::istream& ins, Str& cp);	//cin>>s
	
private:
	static char* create_and_copy_str(char* dest, const char* str);
	char *m_cp;


}; //end class Str

/*********************************************************************/
} // end namespace ilrd

#endif   /*   STRING_HPP_    */
