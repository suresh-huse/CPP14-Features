//==============================================================
// C++14 Library Features
//==============================================================


//==============================================================
// 1. User-defined literals for standard library types
//==============================================================

/*
	// New user-defined literals for standard library types, 
	// including new built-in literals for chrono and basic_string. 
	// These can be constexpr meaning they can be used at compile-time. 
	// Some uses for these literals include compile-time integer parsing, 
	// binary literals, and imaginary number literals.

	using namespace std::chrono_literals;
	auto day = 24h;
	day.count(); // == 24
	std::chrono::duration_cast<std::chrono::minutes>(day).count(); // == 1440
*/

//==============================================================
// 2. Compile-time integer sequences
//==============================================================

/*
	// The class template std::integer_sequence represents a compile-time 
	// sequence of integers. There are a few helpers built on top:

	// std::make_integer_sequence<T, N> - creates a sequence of 0, ..., N - 1 with type T.
	// std::index_sequence_for<T...> - converts a template parameter pack into an integer sequence.
	// Convert an array into a tuple:

	template<typename Array, std::size_t... I>
	decltype(auto) a2t_impl(const Array& a, std::integer_sequence<std::size_t, I...>) {
	  return std::make_tuple(a[I]...);
	}

	template<typename T, std::size_t N, typename Indices = std::make_index_sequence<N>>
	decltype(auto) a2t(const std::array<T, N>& a) {
	  return a2t_impl(a, Indices());
	}
*/

//==============================================================
// 3. std::make_unique
//==============================================================

/*
	// std::make_unique is the recommended way to create instances of std::unique_ptrs 
	// due to the following reasons:

	// Avoid having to use the new operator.
	// Prevents code repetition when specifying the underlying type the pointer shall hold.
	// Most importantly, it provides exception-safety. Suppose we were calling a function foo like so:

	foo(std::unique_ptr<T>{new T{}}, function_that_throws(), std::unique_ptr<T>{new T{}});

	// The compiler is free to call new T{}, then function_that_throws(), and so on... Since we have allocated data on the heap in the first construction of a T, we have introduced a leak here. With std::make_unique, we are given exception-safety:

	foo(std::make_unique<T>(), function_that_throws(), std::make_unique<T>());

*/
