#include <array>
#include <cstdint>
#include <chrono>
#include <iostream>

#define ROUNDS 1000
#define TOKEN  0xdeadbeef

static std::array<uint32_t, 1000000> arr[4];

void by_index( uint32_t index )
{
	auto start = std::chrono::high_resolution_clock::now();
	for( uint32_t n = 0; n < ROUNDS; n++ )
	{
		for( uint32_t i = 0; i < index; i++ )
		{
			if( arr[0][i] == TOKEN ) break;
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "by_index:\t" << std::chrono::duration_cast< std::chrono::microseconds >( end - start ).count() / ROUNDS << "us" << std::endl;
}

void by_element( uint32_t index )
{
	auto start = std::chrono::high_resolution_clock::now();
	for( uint32_t n = 0; n < ROUNDS; n++ )
	{
		uint32_t i = 0;
		for( const auto& ele : arr[1] )
		{
			if( ele == TOKEN ) break;
			if( i == index ) break;
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "by_element:\t" << std::chrono::duration_cast< std::chrono::microseconds >( end - start ).count() / ROUNDS << "us" << std::endl;
}

void by_iterator( uint32_t index )
{
	auto start = std::chrono::high_resolution_clock::now();
	for( uint32_t n = 0; n < ROUNDS; n++ )
	{
		uint32_t i = 0;
		for( auto ele = arr[2].begin(); ele < arr[2].begin() + index; ele++, i++ )
		{
			if( *ele == TOKEN ) break;
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "by_iterator:\t" << std::chrono::duration_cast< std::chrono::microseconds >( end - start ).count() / ROUNDS << "us" << std::endl;
}

void by_while( uint32_t index )
{
	auto start = std::chrono::high_resolution_clock::now();
	for( uint32_t n = 0; n < ROUNDS; n++ )
	{
		uint32_t i = 0;
		while( i++ < index )
		{
			if( arr[3][i] == TOKEN ) break;
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "by_while:\t" << std::chrono::duration_cast< std::chrono::microseconds >( end - start ).count() / ROUNDS << "us" << std::endl;
}

int main( int, char** )
{
	for( uint8_t i = 0; i < 4; i++ )
	{
		arr[i][arr[i].size() - 2] = TOKEN;
	}

	by_index( arr[0].size() - 1 );
	by_element( arr[1].size() - 1 );
	by_iterator( arr[2].size() - 1 );
	by_while( arr[3].size() - 1 );

	return 0;
}