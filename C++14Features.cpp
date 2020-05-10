// C++14.cpp : 
#include "stdc++.h"

#define LOG(x) cout << x << endl

void myFunc(int i) { LOG(i); }

void add(int a, int b)
{
	printf("Addition is %d\n", a + b);
}
void subtract(int a, int b)
{
	printf("Subtraction is %d\n", a - b);
}
void multiply(int a, int b)
{
	printf("Multiplication is %d\n", a * b);
}


// Return type is `const int&`.
decltype(auto) retDecltype(const int& i) {
	return i;
}

// Return type is `int`.
auto retType(const int & i){
	return i;
};

template<typename T>
auto& retTypeTemplate(T& t)
{
	return t;
}

constexpr int factorial(int n) {
	if (n <= 1) {
		return 1;
	}
	else {
		return n * factorial(n - 1);
	}
}

auto main() -> int
{
//============================================================
//  C++14 Language Features
//============================================================

//============================================================
//  1. Literals
//============================================================

	// Literal suffixes

	unsigned int value1{ 5u }; // 5 has type unsigned int
	long value2{ 6L }; // 6 has type long

	float f{ 5.0f }; // 5.0 has type float


	// Scientific notation for floating point literals
	// There are two different ways to declare floating - point literals :

	double pi{ 3.14159 }; // 3.14159 is a double literal in standard notation
	double avogadro{ 6.02e23 }; // 6.02 x 10^23 is a double literal in scientific notation

	// In the second form, the number after the exponent can be negative :
	double electron{ 1.6e-19 }; // charge on an electron is 1.6 x 10^-19


	// Octal is base 8 -- 
	// that is, the only digits available are : 0, 1, 2, 3, 4, 5, 6, and 7.
	/*
	Decimal	0	1	2	3	4	5	6	7	8	9	10	11
	Octal	0	1	2	3	4	5	6	7	10	11	12	13
	*/


	// Hexadecimal is base 16
	/*
	Decimal	    0	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	16	17
	Hexadecimal	0	1	2	3	4	5	6	7	8	9	A	B	C	D	E	F	10	11
	*/

	// Binary literals provide a convenient way to represent a base - 2 number.
	// It is possible to separate digits with '

	// Prior to C++ 14
	int bin{};
	bin = 0x01; // assign binary 0000 0001 to the variable
	bin = 0x02; // assign binary 0000 0010 to the variable

	// C++ 14
	bin = 0b1;  // assign binary 0000 0001 to the variable
	bin = 0b11; // assign binary 0000 0011 to the variable
	bin = 0b1010; // assign binary 0000 1010 to the variable
	bin = 0b1111'0000; // assign binary 1111 0000 to the variable
	std::bitset<8> bin1{ 0b1100'0101 }; // binary literal for binary 1100 0101

//============================================================
//  2. Generic lambda expressions 
//============================================================
	auto identity = [](auto x) { return x; };
	int three = identity(3); // == 3
	std::string foo = identity("foo"); // == "foo"

	// pre-C++17 use std::array<const char*, 12>
	std::array months{ // pre-C++17 use std::array<const char*, 12>
	"January","February","March","April","May","June",
	"July","August","September","October","November","December"};

	// Search for two consecutive months that start with the same letter.
	auto sameLetter{ std::adjacent_find(months.begin(), months.end(),
										[](const auto& a, const auto& b) {
										  return (a[0] == b[0]);
										}) };

	// Make sure that two months were found.
	if (sameLetter != months.end())
	{
		// std::next returns the next iterator after sameLetter
		std::cout << *sameLetter << " and " << *std::next(sameLetter)
			<< " start with the same letter\n";
		// Output: : June and July start with the same letter
	}

	// However, auto isn’t always the best choice.Consider:
	// In this example, using auto would infer a type of const char* .
	// C - style strings aren’t easy to work with(apart from using operator[]).
	// In this case, we prefer to explicitly define the parameter as a std::string_view, 
	// which allows us to work with the underlying data much more easily
	// (e.g.we can ask the string view for its length, even if the user passed in a C - style array).

	// Count how many months consist of 5 letters
	auto fiveLetterMonths{ std::count_if(months.begin(), months.end(),
										 [](std::string_view str) {
										   return (str.length() == 5);
										 }) };

	std::cout << "There are " << fiveLetterMonths << " months with 5 letters\n";
	// Output: There are 2 months with 5 letters


	// In the below example, we define a lambda and then call it with two different parameters
	// (a string literal parameter, and an integer parameter).
	// This generates two different versions of the lambda(one with a string literal parameter,
	// and one with an integer parameter).

	// Print a value and count how many times @print has been called.
	auto print {
	  [](auto value) {
		static int callCount{ 0 };
		std::cout << callCount++ << ": " << value << '\n';
	  }
	};

	print("hello"); // 0: hello
	print("world"); // 1: world

	print(1); // 0: 1
	print(2); // 1: 2

	print("ding dong"); // 2: ding dong


//============================================================
//  3. Lambda capture initializers
//============================================================

	// This allows creating lambda captures initialized with arbitrary expressions.
	// The name given to the captured value does not need to be related to any variables 
	// in the enclosing scopesand introduces a new name inside the lambda body.
	// The initializing expression is evaluated when the lambda is created(not when it is invoked).

	auto factory = [] (int i){
		return i * 10;
	};

	auto f1 = [x = factory(2)] () {return x; }; // returns 20

	auto generator = [x = 0]() mutable {
		return x++;  // Wont compile without mutable as x is modified in each call.
	};

	auto a = generator(); // 0
	auto b = generator(); // 1
	auto c = generator(); // 2

	// Because it is now possible to move(or forward) values into a lambda 
	// that could previously be only captured by copy or reference 
	// we can now capture move - only types in a lambda by value.
	// Note that in the below example the p in the capture 
	// - list of task2 on the left - hand - side of = is a 
	// new variable private to the lambda body and does not refer to the original p.

	auto p = make_unique<int>(5);
	// auto task1 = [=] {*p = 10; } // Error : unique ptr cant be copies
	auto task2 = [ptr = move(p)](){ *ptr = 10; }; // OK: p is move-constructed into the closure object
											  // the original p is empty after task2 is created 


	// Using this reference - captures can have different names than the referenced variable.
	auto x = 1;
	auto lambdaRef = [&r = x, x = x * 10]{
	  ++r;
	  return r + x;
	};
	lambdaRef(); // sets x to 2 and returns 12

	// We don't know what fn will be. std::function works with regular functions and lambdas.
	// Can pass Function ptr/Lambda both

	auto repeat = [&](int repetitions, const std::function<void(int)>& fn)
	{
		for (int i{ 0 }; i < repetitions; ++i)
		{
			fn(i);
		}
	};
	
	repeat(3, [](int i) { LOG(i);}); // lambda

	repeat(3, myFunc); // funtion name

	void (*fun_ptr)(int) = myFunc;
	repeat(3, fun_ptr); // function ptr


	// Additional here : fun_ptr_arr is an array of function pointers 

	void (*fun_ptr_arr[])(int, int) = { add, subtract, multiply };
	auto ai = 15u, bi = 10u;

	switch (auto choice = 0 /*value in switch*/)
	{
	case 0: // add
		(*fun_ptr_arr[0])(ai, bi);
		break;

	case 1: // subtract
		(*fun_ptr_arr[1])(ai, bi);
		break;

	case 2: // multiply
		(*fun_ptr_arr[2])(ai, bi);
		break;

	default:
		break;
	}

//============================================================
//  4. Return type deduction
//============================================================
	
	// Using an auto return type in C++14, the compiler will attempt to deduce 
	// the type for you.With lambdas, you can now deduce its return type using auto, 
	// which makes returning a deduced reference or rvalue reference possible.

	// dedude return type
	auto ret = retType(10);

	// returns a reference to deduced type
	auto retTypelamba = [](auto& ref) -> auto& {
		return retTypeTemplate(ref);
	};

	int y = 123;

	int& ry = retTypelamba(y);


//============================================================
//  5. decltype(auto)
//============================================================

	
	// The decltype(auto) type - specifier also deduces a type like auto does.
	// However, it deduces return types while keeping their referencesand cv - qualifiers, 
	// while auto will not.

	const int ii = 0;
	auto ix1 = ii; // const int
	int yy = 0;
	int& y1 = yy; // 
	auto y2 = y1; // int&
	int&& zz = 0;
	auto z1 = std::move(zz); // int
	decltype(auto) z2 = std::move(zz); // int &&


	// Note: Especially useful for generic code!

	/*
	// Return type is `const int&`.
	decltype(auto) retDecltype(const int& i) {
		return i;
	}

	// Return type is `int`.
	auto retType(const int& i) {
		return i;
	}; */

	int x1 = 123;
	static_assert(std::is_same<const int&, decltype(retType(x1))>::value == 0);
	static_assert(std::is_same<int, decltype(retType(x1))>::value == 1);
	static_assert(std::is_same<const int&, decltype(retDecltype(x1))>::value == 1);

//============================================================
//  6. Relaxing constraints on constexpr functions
//============================================================
	
	// In C++11, constexpr function bodies could only contain a very limited set of syntaxes,
	// including(but not limited to) : typedefs, usings, and a single return statement.
	// In C++14, the set of allowable syntaxes expands greatly to include the most common syntax
	// such as if statements, multiple returns, loops, etc.

	/*constexpr int factorial(int n) {
		if (n <= 1) {
			return 1;
		}
		else {
			return n * factorial(n - 1);
		}
	}*/
	factorial(5); // == 120

	return 0;
}












