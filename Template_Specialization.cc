/*
	Template Specialization
	
	Templates are key techniques for
	
	1. Improving type safety. (by elimination the use of
		casts)
	2. Raising the general level of abstraction
	   of programs.
	3. Providing more flexible, type-safe, and efficient
	   parameterization of types and algorithms.
	
	These techniques all critically rely on the
	ability of template code to use template
	arguments without overhead and in a type-safe
	manner.

	Most techniques also rely on the type deduction
	mechanisms offered by templates ( compile-time
	polymorphism).

	Template Parameters And Arguments

	A template can take parameters
		1. Type parameters
		2. Value parameters - built in types ie ints
			and pointers to functions
		3. Template parameters
*/

// Types as Arguments 

template<typename T>
void f(T);

template<typename T>
class W {};

f(1); // T deducet to be int
f<double>(1); // T is double
f<complex<double>>(1); // T is complex<double>

W<double> w1; // T is double
W<complex<double>> w2; // T is complex<double>

/* 
	Values as Arguments
	
	A template param that is not a type
	or a tmplate is called a value param
	and an argument passed to it a 
	value argument.
*/

template<typename T, int max>
class Buffer
{
	T v[max];
	public:
		Buffer() {}
		// ..
};

Buffer<char,120> cbuf;
Buffer<double, 20> dbuf;
Buffer<Record,9> rbuf;


/*
	An argument for a template value
	parameter can be.

	1. An integral constant expression.
	2. A pointer or a reference to an
	   object or a function with external
	   linkage.
    3. A nonoverloaded pointer to member.
	4. A null pointer.

	Think of template value arguments
	as a mechanims for passing integers
	and pointers to functions.

	A pointer used a template argument
	must of the form &of.
	A pointer to member must of the
	form &X::of, where of is the name
	of the member.
	
	A string literal is not acceptable
	as a template argument.

	Unfortunately, literal types cannot
	be used as template value arguments.

	An integer template argument must be
	a constant.
*/

template<typename T, char* label>
class X {
	/* .. */
};
X<int,"HELLO"> x1; // error: string literal as template
                   // argument
char lx2[] = "BMW450";
X<int,lx2> x2; // Ok

// 
constexpr int max = 9000;

void f(int i)
{
	Buffer<int, i> bint; // error: constant expectd
	Buffer<int, max> bm; // Ok: constant expression
}

/* A template type parameter can be
   used as a type later in a template
   parameter list.
*/

template<typename T, T default_value>
class Vec { };

Vec<int,39> c1;
Vec<string,""> c2;

/*
	This becomes useful when combined 
	with a default template  argument.
*/
template<typename T, T default_value = T{}>
class Vec { /*..   */ };

Vec<int, 30> v1;
Vec<int> c11; 
Vec<string, "Buddy"> v3;
Vec<string> v4;

/*
	Operations As Arguments
*/
template<typename Key, Class V,
	typename Compare=std::less<Key>>
class map
{
	public:
		map() { /* ..*/}
		map(Compare c) : cmp{c} {/* .. */}
		// ..
		Compare cmp {};
};
map<string,int> m1;
map<string,int,std::greater<string>> m2;

// Passing lambdas
auto cmp = [](const string& x, const string& y)
			{ return x<y; }

/*
	Templates As Arguments
	
	The point of using a template as
	a template parameter is usually
	that we want to instantiate it with
	a variety of argument types
	(such as T and T*).

	Only class templates can be template
	arguments.

*/

template<typename T, template<typename> class C>
class Xrefd {
	C<T> mems;
	C<T*> refs;
	// ..
};

template<typename T>
	using My_vec = vector<T>;

Xrefd<Entry,My_vec> x1;

/*
	The common use case in which a
	template needs only a container or two
	is better handled by passing the container
	types
*/

/*
	Default Template Arguments
	supplied as trailing arguments only.
*/

template<typename T1 = int, typename T2 = double>
class X {

};
X<,float> v1;
X<float> v2;

/* 
	Default Function Template Arguments
*/

template<typename Target = string,
			typename Source = double>
Target to(Source arg)
{
	Target result;

	//...
	
	return result;
}

auto x1 = to<string, double>(1.2);
auto x2 = to<string>(1.32);
auto x3 = to<>(1.2);
auto x4 = to(4.5);













