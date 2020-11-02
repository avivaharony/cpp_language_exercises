#include <iostream>

#include "../utils.h"
#include "string.hpp"

using std::cout;
using std::cerr;
using std::cin;
using std::endl;

using namespace ilrd;


/******************************/
static int total_tests_count = 0;

/*********/
template <typename ResultType>
static int CheckResult(char *func_name, ResultType result, ResultType expected_result, int line_number);

/*********/


int TestStrAssignment();
int TestStrCompartions();

int TestStrInputOutput();
int TestStrCharOperator();

/*********/
int main()
{
	int err_count = 0;

	err_count += TestStrAssignment();
	
	err_count += TestStrCompartions();

	err_count += TestStrInputOutput();

	err_count += TestStrCharOperator();

	if (0 == err_count)
	{
		cout << "****************\n";
		cout << "All Tests Passed\n";
		cout << "****************\n";
		cout << "Total tests number: " << total_tests_count << endl;
	}	
	else
	{
		cout << "****************\n";
		cout << "FIXING REQUIRED.\n";
		cout << "****************\n";
		cout << "Number of errors : " << err_count << "\n" ;
		cout << "Total tests number: " << total_tests_count << endl;
		cout << "Correct the errors and try again" << endl;
	}
	
	cout << "Remember to Run Valgrind as well" << endl;
	

	return (0);
}


// -------------------------------------------------- 
// -------------------------------------------------- 
int TestStrCharOperator()
{
	char func_name[] = "TestStrCharOperator";

	int err_count = 0;
	char ch3 = 'b';
	
	Str s1 = "he";
	Str s2 = "lla";
	
	s1[1] = ch3;
	Str s_res = "hb";
	

	err_count += CheckResult(func_name, s1, s_res , __LINE__);
	err_count += CheckResult(func_name, s1[0] == 'h' ,true , __LINE__);

// const str ;if (s[1]== 'a') . if ('a' == str[1]); . char c = s[2];
	const Str s4 = "bgb";
	err_count += CheckResult(func_name, s4[2] , 'b'  , __LINE__);

	err_count += CheckResult(func_name, 'b' == s4[2] , true  , __LINE__);
	char ch1 = s4[1];
	err_count += CheckResult(func_name, ch1 == s4[1] , true  , __LINE__);

	s1+= s2+= s1;
	
	err_count += CheckResult(func_name, s2 == "llahb" , true  , __LINE__);
	err_count += CheckResult(func_name, s1 == "hbllahb" , true  , __LINE__);
	
	return (err_count);
}

// -------------------------------------------------- 

int TestStrInputOutput()
{
	int err_count = 0;

	Str s1 = "he";
	Str s2 = "lla";
	
	cout << "enter a string : ";
	cin >> s1;
	cout << "your entered string: " << s1 << endl;
//	cin.ignore('\n');	// '\n' discarded at operator>> implementation
	cout << "enter another string : ";
	cin >> s2;
	cout << "your entered string: " << s2 << endl;
	
	return (err_count);
}

// -------------------------------------------------- 

int TestStrAssignment()
{
	char func_name[] = "TestStrAssignment";
	int err_count = 0;
	
	Str s1 = "he";
	Str s2 = "lla";
	s2 = s1;
	Str s3 = "yybbb";

	s1.operator=(s2.operator=(s3));
	
	Str s4(s3);
	Str s5;
	
	err_count += CheckResult(func_name, s4 == "yybbb" , true  , __LINE__);
	err_count += CheckResult(func_name, s5 == "" , true  , __LINE__);
	
	s4 = "aviv";
	err_count += CheckResult(func_name, s4 == "aviv" , true  , __LINE__);
	
	s4=s4=s4;
	err_count += CheckResult(func_name, s4 == "aviv" , true  , __LINE__);
	
	
	return (err_count);
}

// -------------------------------------------------- 

int TestStrCompartions()
{
	int err_count = 0;
	char func_name[] = "TestStrCompartions";
	// check also s1.operator=(s2.operator=(s3))
	Str s1 = "he";
	Str s2 = "lla";
	s2 = s1;
	
	err_count += CheckResult(func_name, s2 == s1, true, __LINE__);
	err_count += CheckResult(func_name, s2 != s1, false, __LINE__);
	
	Str s3 = "yybbb";

	err_count += CheckResult(func_name, s2 != s3, true, __LINE__);
	
	err_count += CheckResult(func_name, s2 < s3, true, __LINE__);
	
	err_count += CheckResult(func_name, s3 < s2, false, __LINE__);
	
	err_count += CheckResult(func_name, s2 > s3, false, __LINE__);
	err_count += CheckResult(func_name, s3 > s2, true, __LINE__);
	
	err_count += CheckResult(func_name, s2 > s2, false, __LINE__);
	err_count += CheckResult(func_name, s3 < s3, false, __LINE__);
	
	err_count += CheckResult(func_name, "aaabb" < s3, true, __LINE__);
		
	return (err_count);
}


/* -------------------------------------------------- */

template <typename ResultType>
static int CheckResult(char *func_name, ResultType result, ResultType expected_result, int line_number)
{
	++total_tests_count;
	
	if (result != expected_result)
	{
		cerr << "Error with Function " << func_name << " See line " << line_number << "\n";
		cerr << "Expected result is: " << expected_result << " but result is: " << result << "\n";
		return (1);
	}
	
	
	return (0);
}


