/*
	Template Metaprogramming
	-------------------------------
	Programming that manipulates program entities
	such as classes and functions.

	Think of templates as generators, they 
	are used to make classes and functions.

	An exercise in writing programs that compute
	at compile time and generate programs.

	Reasons for metaprogramming.
	1. Improved type safety: we can compute the exact
	   types needed for a data structure or algorithm
	   so that we don't need to directly manipulate
	   low-level data structures.
	2. Improved run-time performance: we can compute
	   values at compile-time and select functions to
	   be called at runtime.
	   That way, we don't need to do those computations
	   at run time.

	Templates were designed to very general and able to
	generate optimal code.
	
	When I write a generic algorithm or type, I don't feel
	that I am writing a compile time program.

	Generic programming is primarily a design philosophy.
	
	Metaprogramming is programming. The emphasis is on
	computation, often involving selection and some form
	of iteration.

	4 levels of implementation complexity:
	1. No computation (just pass type and value arguments)
	2. Simple computatioon.
	3. Computation using explicit compile-time tests,
	   for example compile time if.
	4. Computation using compile-time iteration (in the
	   form of recursion)

    A metaprogram is a compile-time computation yielding
	types or functions to be used at run time.

	Generic programming usually falls into the first,
	"no computation" category, but it is quite possible
	to support generic programming using metaprogramming
	techniques.

	Generic programming focuses on interface specification,
	whereas metaprogramming is programming, usually with
	types as the values.

*/

/* 
	Type Functions
	-----------------------------------------
	A type function is a function that either takes
	at least one type argument or produces at least
	one type as a result.

	For example:

	sizeof(T) - Is a built-in type function that given
	a type T returns the size of an object (measured in
	chars).
	
	Type functions don't have to look like conventional
	functions.
	is_polymorphic<T>: takes its argument as template
	argument and returns its result as a member called 
	value.

	if (is_polymorphic<int>::value) cout << "Big surprise!";

	STL convention is that a type function that returns
	a type does so by a member called type.

*/

enum class Axis : char { x, y, z};
enum flags { off, x=1, y=x<<1, 
             z=x<<2, t=x<<3 };
typename std::underlying_type<Axis>::type x;
typename std::underlying_type<Axis>::type y;

/*
	A type function can take more than one 
	argument and return several result values.
*/

template<typename T, int N>
struct Array_type {
	using type = T;
	static const int dim = N;
	// ..
};

using Array = Array_type<int, 20>;
Array::type x; // x is an int
constexpr int s = Array::dim; // s is 3

/*
	C++ type functions are mostly templates.
	They can perform very general computations
	using types and values.

	For example, we might want to allocate
	an object on the stack provided that it is
	small and on the free store otherwise: 

*/

constexpr int on_stack_max = sizeof(std::string);

template<typename T>
struct Obj_holder {
	using type = 
		typename std::conditional<(sizeof<T> <= on_stack_max),
									Scoped<T>,
									On_Heap<T>>::type;

};

/*
	The standard-library template conditional is
	a compile-time selector between two alternatives.
*/

void f() {
	
	typename Obj_holder<double>::type v1;
	typename Obj_holder<array<double, 200>>::type v2;

	*v1 = 77;
	v2[77] = 9.9;

}

template<typename T>
struct On_heap {
	On_heap(): p(new T) {}
	~On_heap() { delete p}
	
	T& operator*() { return *p; }
	T* operator->() { return p; }
	On_heap(const On_heap&) = delete;
	On_heap operator=(const On_heap&) = delete;
private:
	T* p;
};

template<typename T>
struct Scoped {
	T& operator*() {return x; }
	T* operator->() { return &x; }
	Scoped(const Scoped&) = delete;
	Scoped operator=(const Scoped&) = delete;
private:
	T x;
}


/* 
	Type Aliases
	----------------------------------------
	By introducing a type alias, we can hide
	::type implementation details and make
	a type function look much more like a function
	returning a type.
*/

template<typename T>
using Holder = typename Obj_holder<T>::type;

void f2()
{
	Holder<double> v1; // goes on the stack
	Holder<std::array<double, 200>> v2; // goes on the heap
}

/* 
	When a function provides a type function (type property
	predicate or composite category predicate) such as conditional
	, I define a corresponding type alias.
*/

template<typename C, typename T, typename F>
using Conditional = typename std::conditional<C,T,F>::type;

/*
	When not to use an Alias
	If one of the alternatives is supposed to be
	a valid type.
*/

conditional<
	is_integral<T>::value,
	make_unsigned<T>,
	Error<T>>::type;

/*
	In the rare cases where we can't use aliases
	to hide ::type, we can fall back on the
	more explicit, implementation-oriented type.
	Alternatively we can introduce a Delay type
	function to delay evaluation of a type function
	until its use
*/
Conditional<
	std::is_integral<T>::value,
	Delay<Make_unsigned,T>,
	Error<T>
>

template<template<typename ...> class F, typename... Args>
using Delay = F<Args...>;

/*
	Type Prediates
	--------------------------------
	A predicate is a function that returns a Boolean value.
*/

template<typename T>
constexpr bool Is_bool()
{
	return std::is_pod<T>::value;
}

template<typename T>
constexpr bool Is_big()
{
	return 100<sizeof(T);
}

template<typename T>
using Obj_holder = Conditional<(Is_big<T>()), Scoped<T>, On_heap<T>>;

/* 
	Selecting A Function
	-------------------------------------

	Traits
	-------------------------------------
	The standard library relies heavily on traits.
	A trait is used to associate a property with 
	a type.

	Control Structures
	---------------------------------------
	
	1. Selection
	---------------------------------------

	Selecting between two types
	---------------------------------------
*/

	template<bool C, typename T, typename F>
	struct conditional {
		using type = T;
	};
	
	template<typename T, typename F>
	struct conditional<false, T,F>
	{
		using type = F;
	}

	
	template<bool B, typename T, typename F>
	using Conditional = typename std::conditional<B,T,F>::type;

	Conditional<(std::is_polymorphic<T>()), X, Y> z;
	
	/* 
	   Selecting among several types.
	   --------------------------------------------
	 
	*/

	template<unsigned N, typename... Cases>
	struct select;

	template<unsigned N, typename T, typename... Cases>
	struct select <N,T, Cases...> : select<N-1, Cases...>
	{};

	template<typename T, typename... Cases>
	struct select<N, T, Cases...>
	{
	  using type = T;
	}

	template<unsigned N, typename... Cases>
	using Select = typename select<N, Cases...>::type;

	/*
		Iteration and Recursion
		--------------------------------------------
	*/

	template<int N>
	struct Fac 
	{
		static const int  value = N*Fac<N-1>::value;
	};

	template<>
	struct Fac<1> {
		static const int value = 1;
	};
	
	constexpr int x8 = Fac<8>::value;

/*
	Conditional Definition: Enable_if
	-------------------------------------------------
	When we write a template, we sometimes want to
	provide an operation for some template argument,
	but not for others.

	enable_if in the stl lib <type_traits>
*/
template<typename T>
class Smart_pointer {
	// ..
	T& operator*();
	Enable_if<Is_class<T>(), T>* operator->();
	// ..
};

template<bool B, typename T>
using Enable_if = typename std::enable_if<B,T>::type;

template<typename T>
bool Is_class()
{
	return std::is_class<T>::value;
}

/*
	If Enable_if's condition evaluates to true,
	its result is its second argument (here, T).
	If Enable_if's condition evaluates to false,
	the whole function declaration of which it 
	is part is completely ignored.
*/

void f(Smart_pointer<double> p,
		Smart_pointer<complex<double>> q)
{

	auto d0 = *p; //Ok
	auto c0 = *q; //Ok
	auto d1 = q->real(); // Ok
	auto d2 = p->real(); // error
	// ..
}

/* 
	Use of Enable_if
	-------------------------------------
	Some declarations do not have a return
	type.

*/

template<typename T>
class Vector<T> {
	public:
		Vector(size_t n, const T& val);

		template<typename Iter,
				typename = Enable_if<input_iterator<iter>(),iter>>
				Vector(Iter b, Iter e);
}

/* 
	Implementing Enable_if
*/
template<bool B,typename T=void>
struct std::enable_if {
	typedef T type;
};

template<typename T>
struct std::enable_if<false, T> {};

template<bool B, typename T=void>
using Enable_if = typename std::enable_if<B,T>::type;

/* More enable_if examples  */
template<typename T>
Enable_if<Ordered<T>()> fct(T*,T*);

template<typename T>
Enable_if<!Ordered<T>()> fct(T*,T*);

void f(vector<int>& vi,
			vector<complex<int>>& vc)
{
	if (vi.size == 0|| vc.size() == 0)
		throw runtime_error("bad fact arg");
	fct(&vi.front(), &vi.back());
	fct(&vc.front(), &vc.back());
}

/*
	When using Enable_if, sooner or later we 
	want to ask if a class has a member with
	a specific name and an appropriate type.

	Let's build our own predicate.

	Consider the question "Can we call f(x) if x
	is of type X?".
*/

struct substitution_failure {};

template<typename T>
struct substitution_succeeded : std::true_type
{};

template<>
struct substitution_succeded<sustitution_failure> :
	std::false_type {};

template<typename T>
struct has_f : susbsitution_succeded<
						typename get_f_result<T>::type>
{};

template<typename T>
struct get_f_result {
	private:
		template<typename T>
			static auto check(X const& x) -> decltype(f(x));
		static substitution_failure check(...);
	public:
		using type: std::decltype(check(std::declval(T)));
};

template<typename T>
constexpr bool Has_f()
{
	return has_f<T>::value;
}

template<typename T>
class X {
	// ..
	Enable_if<Has_f<T>()> use_f(const T&)
	{
		// ..
		f(t);
		// ..
	}
	
};

/*
	
	A class template cannot deduce its template
	arguments, but a function template can 
	deduce them from its function arguments.


	Variadic templates
	----------------------------------------
	Having to deal with an unknown number of
	elements is a common problem.

	For example printf()
	1. Handle cases where there is just one 
	   argument.
	2. Handle the case where there is at least
	   one additional argument.
*/

void print(const char* s)
{
	if (s == nullptr) return;
	while (*s)
	{
		if (*s == '%' && *++s == '%')
			throw runtime_error("Invalid format: missing arguments");
		std::cout << *s++;
	}

}

template<typename T, template ... Args>
void printf(const char* s, T value, Args... args)
{
	while (s && *s) {
		if ( *s=='%' && *++s!='%') {
			std::cout << value;
			return printf(++s, args...);
		}
		std::cout << *s++;
	}
	throw std::runtime_error("extra arguments provided to printf");
}
/*
	The Args... defines what is callled a parameter pack.
	A parameter pack is a sequence of (type/value) pairs
	from which you can "peel off" arguments starting with
	the first.
	
	A variadic template is defined with the ... notation.
	
	template<typename... Types>
	void f(Types... args);

	The typename... in the declaration of Types
	specifies that Types is a template parameter pack.
	The ... in the type of args specifies that args
	is a function parameter pack.

	The ellipsis (...) is a separate lexical token,
	so you can place whitespace before or after it.
	It means zero or more occurrences of something.

	If you have a parameter pack, you can expand it
	into its sequence of elements by placing a ...
	after it.
*/

template<typename T, typename ... Args>
void printf(const char *s, T value, Args ... args)
{
	//..
	printf(++s, args...);
	// ..
}

/*
	Expansion of a parameter pack into its
	elments is not restricted to function
	calls.
*/
template<typename ... Bases>
class X : public Bases...{
	pubilc:
		X(const Bases&... b) : Bases(b)... {}
};

X<> x0;
X<Bx> x1(1);
X<By, bX> x2(2, 3);
X<Bx, By, Bz> x3(2,3,4);

/*
	We can use the ellipsis to mean
	"zero or more elements of something"
	in most places where a list of
	elements is required.

	1. A template argument list.
	2. A function argument list.
	3. An initializer list.
	4. A base specifier list.
	5. A base or member initializer list.
	6. A sizeof... expression

	A sizeof... expression is used to obtain
	the number of elements in a parameter
	pack. 
	For example we can define a constructor
	for a tuple given a pair provided the
	number of tuple elements is two:	
*/

template<typename ... Types>
class tuple {
	// ..
	template<typename T, typename U, 
		typename = Enable_if<sizeof...(Types)==2> 
		tuple(const pair<T,U>>&);
};

/*
	Forwarding
	----------------------------------
	One of the major uses of variadid templates
	is forwarding from one function to another.

	Consider how to write a function that takes
	as arguments something to be called and a
	possibly empty list of arguments to give 
	to the "something" as arguments.

*/

template<typename F, typename ... T>
void call(F&& f, T&& ... t)
{
	f(std::forward<T>(t)...);
}
/*
	Above use pass-by-rvalue-reference of
	a deduced template argument type to
	be able to correctly distinguish between
	rvalues and lvalues.

	call() can accept functions, pointers to
	functions, function objects and lambdas.
*/

































