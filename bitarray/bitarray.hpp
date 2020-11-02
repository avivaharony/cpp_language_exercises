#ifndef BITARRAY_HPP_
#define BITARRAY_HPP_

#include <iosfwd> 			// operator<< , size_t
#include <cstring>			// strlen
#include <algorithm>    	// std::for_each, transform
#include <vector> 			// std::vector

// Temp For testing
#include <iostream> 		//  cout

namespace ilrd
{

template<size_t SIZE = 1>
class BitArray
{
private:
	static const int BITS = sizeof(size_t) * 8;

	// Temp For testing
	static void print_func(size_t i);

	class Proxy;

public:

	explicit BitArray(const char* bitarray = "0"); 		// default CTOR : BitArray(50).
	
	//default : ~BitArray();									// generated DTOR
	// default : BitArray(const BitArray& other); 				// generated CCTOR
	// default : BitArray& operator=(const BitArray& other);	// generated Assignment operator
	
	// b1[3] = true, if (b2[1]== false).
	Proxy operator[](size_t index);
	// const str ;if (b1[1]== true) . if (true == b1[1]); . bool b = b1[2];
	bool operator[](size_t index) const;

	// b1 &= b2; compilation error if size of bitarrays differs.
	BitArray& operator&=(const BitArray& rhs);
	// b1 |= b2; compilation error if size of bitarrays differs.
	BitArray& operator|=(const BitArray& rhs);
	// b1 ^= b2; compilation error if size of bitarrays differs.
	BitArray& operator^=(const BitArray& rhs);
	// b1 <<= bits_number
	BitArray& operator<<=(size_t shift_bits);
	

	// Temp For testing
	void print_bitarray();

private:
	struct ShiftFunctor;
	inline static void calc_position(size_t index, size_t& arr_idx, unsigned long& mask);
		// change bit of array to value
	void change_bit(bool value, size_t index);
	// turn on bit of array
	void set_bit(size_t index);
	// turn off bit of array
	void clear_bit(size_t index);
	// returns bit value
	bool is_set(size_t index) const;


	static void op_clear_cell(size_t& element);
	inline static size_t op_and(size_t lhs, size_t rhs);
	inline static size_t op_or(size_t lhs, size_t rhs);
	inline static size_t op_xor(size_t lhs, size_t rhs);

	// static const size_t m_arr_size = (SIZE / BITS) + (SIZE % BITS != 0);	
	static const size_t m_arr_size = (SIZE / BITS) + 1;	

	std::vector<size_t> m_array; 
}; //end class BitArray

//----------------------------------------------------------
//--------------------------Proxy --------------------------
template <size_t SIZE>
class BitArray<SIZE>::Proxy
{
  public:
	explicit Proxy(size_t index, BitArray *m_bit_array); // CTOR

	bool operator=(const BitArray::Proxy &rhs); // Assignment operator b1[2] = b2[1]
	bool operator=(bool rhs);					// Assignment operator overloaded b1[3]= true

	operator bool() const;

  private:
	size_t m_index;
	BitArray *m_bit_array;
}; //end class Proxy

//----------------------------------------------------------
//--------------------------ShiftFunctor -------------------
template<size_t SIZE>
struct BitArray<SIZE>::ShiftFunctor
{
public:
	explicit ShiftFunctor(size_t shift_bits);

	size_t operator() (size_t dest_element, size_t other_element); 
private:
	size_t m_shift;
};

//------------------ShiftFunctor Definitions---------------------------
template<size_t SIZE>
BitArray<SIZE>::ShiftFunctor::ShiftFunctor(size_t shift_bits):m_shift(shift_bits)
{}

template<size_t SIZE>
size_t BitArray<SIZE>::ShiftFunctor::operator() (size_t dest_element, size_t other_element)
{
	dest_element <<= m_shift;
	dest_element |= ((other_element) >> (BITS - m_shift));
	
	return dest_element; 
}

//----------------------------------------------------------
//-----------------------BitArray---------------------------
//-----------------------Definitions------------------------
template<size_t SIZE>
BitArray<SIZE>::BitArray(const char* bitarray) :	
					 m_array(m_arr_size, 0)
{
	size_t len = strlen(bitarray);
	size_t bytes_number = SIZE < len ? SIZE : len;
	
	for (size_t i = 0 ; i < bytes_number ; ++i)
	{
		change_bit(bitarray[len - i - 1] - '0', i);
	}
}


//----------------------------------------------------------
template<size_t SIZE>
size_t BitArray<SIZE>::op_and(size_t lhs, size_t rhs)
{
	return (lhs & rhs); 
}

template<size_t SIZE>
inline size_t BitArray<SIZE>::op_or(size_t lhs, size_t rhs)
{
	return (lhs | rhs); 
}

template<size_t SIZE>
inline size_t BitArray<SIZE>::op_xor(size_t lhs, size_t rhs)
{
	return (lhs ^ rhs); 
}

template<size_t SIZE>
inline void BitArray<SIZE>::op_clear_cell(size_t& element)
{
	element = 0;
}

//----------------------------------------------------------
template<size_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::operator<<=(size_t shift_bits)
{
	if (shift_bits > SIZE)
	{
		// clear all vector elements.
		std::for_each(m_array.begin(), m_array.end(), op_clear_cell);
		return (*this);
	}
	
	size_t jumps = shift_bits / BITS;
	size_t local_shifts = shift_bits & (BITS - 1);

	ShiftFunctor sf1(local_shifts);

	std::vector<size_t>::iterator iter_begin = m_array.begin();
	std::vector<size_t>::iterator iter_src = m_array.begin() + jumps;
	std::vector<size_t>::iterator iter_end = m_array.end();
	std::vector<size_t>::iterator iter_res;

	iter_res = std::transform (iter_src,
								iter_end - 1,
								iter_src + 1,
								iter_begin, 
								sf1);


	*iter_res = (*(iter_end - 1) << local_shifts);
	
	// clear last vector elements remaining from shift.
	std::for_each(iter_res + 1, iter_end, op_clear_cell);

	
	return (*this);
}
//----------------------------------------------------------
template<size_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::operator&=(const BitArray<SIZE>& rhs)
{
	std::transform (m_array.begin(),
					m_array.end(),
					rhs.m_array.begin(),
					m_array.begin(), op_and);
	
	return (*this);
}
//----------------------------------------------------------
template<size_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::operator|=(const BitArray<SIZE>& rhs)
{
	std::transform (m_array.begin(),
					m_array.end(),
					rhs.m_array.begin(),
					m_array.begin(), op_or);
	
	return (*this);
}
//----------------------------------------------------------
template<size_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::operator^=(const BitArray<SIZE>& rhs)
{
	std::transform (m_array.begin(),
					m_array.end(),
					rhs.m_array.begin(),
					m_array.begin(), op_xor);
	
	return (*this);
}
//---------------------------------------------------

template<size_t SIZE>
inline void BitArray<SIZE>::calc_position(size_t index, size_t& arr_idx, unsigned long& mask)
{
	arr_idx = SIZE / BITS - index / BITS;
	// arr_idx = m_arr_size ;
	
	mask = 1UL << (index & (BITS - 1)); 
}
	
//---------------------------------------------------

template<size_t SIZE>
void BitArray<SIZE>::set_bit(size_t index)
{
	size_t arr_idx = 0;
	unsigned long mask = 0;

	calc_position(index, arr_idx, mask); 

	m_array[arr_idx] |= mask;
}

//---------------------------------------------------

template<size_t SIZE>
void BitArray<SIZE>::clear_bit(size_t index)
{
	size_t arr_idx = 0;
	unsigned long mask = 0;

	calc_position(index, arr_idx, mask);

	m_array[arr_idx] &= (~mask);
}


template<size_t SIZE>
void BitArray<SIZE>::change_bit(bool value, size_t index)
{
	if (1 == value)
	{
		set_bit(index);
	}
	else
	{
		clear_bit(index);
	}
}


//---------------------------------------------------

template<size_t SIZE>
bool BitArray<SIZE>::is_set(size_t index) const
{
	size_t arr_idx = 0;
	unsigned long mask = 0;

	calc_position(index, arr_idx, mask);

	return (m_array[arr_idx] & mask);
}

//-------------------------- operator[] -------------------------

template<size_t SIZE>
typename BitArray<SIZE>::Proxy BitArray<SIZE>::operator[](size_t index)
{
	return (Proxy(index, this));
}

template<size_t SIZE>
bool BitArray<SIZE>::operator[](size_t index) const
{
	return (is_set(index));
}

// -------------------------------------------------
// -------  BitArray::Proxy Definitions-------------
// -------------------------------------------------
template<size_t SIZE>
BitArray<SIZE>::Proxy::Proxy(size_t index, BitArray<SIZE> *m_bit_array): m_index(index), m_bit_array(m_bit_array)
{}


// -------------------------------------------------
template<size_t SIZE>
bool BitArray<SIZE>::Proxy::operator=(bool rhs)
{
	m_bit_array->change_bit(rhs, m_index);

	return (*this);
}

template<size_t SIZE>
bool BitArray<SIZE>::Proxy::operator=(const BitArray::Proxy& rhs)
{
	*this = static_cast<bool>(rhs);
	
	return (*this);
}

template<size_t SIZE>
BitArray<SIZE>::Proxy::operator bool() const
{
	return (m_bit_array->is_set(m_index));
}

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
// Temp For Testing
template<size_t SIZE>
void BitArray<SIZE>::print_func(size_t i)
{
	unsigned long mask = 1UL << (BITS - 1);
	for (int j = BITS - 1; j >= 0  ; --j)
	{
		std::cout << ((i & mask) >> j) ;
		mask >>= 1;
		if ((j % 8) == 0)
		{
			std::cout << '.';
		}
	}
	std::cout << std::endl;
}
// ----
template<size_t SIZE>
void BitArray<SIZE>::print_bitarray()	
{
	std::cout << "bitarray address :" << this << std::endl;
	std::for_each(m_array.begin(), m_array.end(), print_func);
		std::cout << std::endl;

}

/*********************************************************************/

} // end namespace ilrd


#endif   /*   BITARRAY_HPP_    */
