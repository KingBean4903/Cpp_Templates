/* 
	Function Templates

	When a function template is called
	the types of the function arguments
	determine which version of the template is
	used; that is, the template arguments
	are deduced from the function arguments

	A function template must be defined somewhere.

	Function Template Arguments______________

	Function templates are essential for writing
	generic algorithms to be applied to a wide
	variety of container types.

	A compiler can deduce type and non-type
	arguments from a call, provided the function
	argument list uniquely identifies the set of
	template arguments.

	A class template params are never deduced.
	Instead specialization provides a mechanism
	for implicitly choosing between alternative
	definitions of a template.

	If we need to create an object of a deduced
	type, we can often do that by calling a
	function to do the deduction(and creation).
*/

template<typename T1, typename T2>
pair<T1, T2> make_pair(T1 a, T2 b)
{
	return { a, b};
}

auto p1 = make_pair(1, 2); // p1 is a pair<int, int>
auto p2 = make_pair(string("Foo"), 5.85); // p2 is a pair<string, double>

/*
	If a template argument cannot be
	deduced from the function arguments
	we must specify it explicitly.
*/

template<typename T>
T* create();

void f()
{
	vector<int> v; // class, template argument int
	int* p = create<int>(); // function template argument int
	int* q = create(); // error: can't deduce template argument
}

/*
	Reference Deduction

	Lvalue and rvalues are distinguished by 
	template argument deduction: an lvalue of type X
	is deduced as an X& and an rvlaue as X.

*/
template<typename T>
class Xref {
	
	public:
		Xref(int i, T& s): index{i}, elem{&s}, owned{false} {}
		
		Xref(int i, T&& s) : index{i}, elem{new T{std::move(s)} }, owned{true} {}

		Xref(int i, T* s) : index{i}, elem{p} owned {true}

	private:
		int index;
		T* elem;
		bool owned;

}

string x {"HEllo"};
Xref<string> r1 {3, "Foo"};
Xref<string> r2 {8, new string{"Hello"}};
Xref<string> r3 {4, x};

/*
	This differs from the binding of values
	to non-template argument rvalue references
	but is especially useful for argument forwarding.

	Consider writing a factory function that makes 
	Xrefs on the free store and returns unique_otrs to
	them.

*/

template<typename T>
 T&& std::forward(typename remove_reference<T>::type& t) noexcept;

template<typename T>
 T&& std::forward(typename remove_reference<T>::type&& t) noexcept;

template<typename TT, typename A>
unique_ptr<TT> make_unique(int i, A&& a)
{
	return unique_ptr<TT>{new TT{i, forward<A>(a)}};
}

auto p1 = make_unique<Xref<string>>(7, "Hello");
auto p2 = make_unique<Xref<string>>(9, x);

/*
	Function template overloading

	When an overloaded function is called,
	overload resolution is necessary to find
	the right function or function template
	to invoke.

*/

template<typename T>
 T sqrt(T);

template<typename T>
 complex<T> sqrt(complex<T>);

double sqrt(double);

void f(complex<double> z)
{
  sqrt(2); // sqrt<int>(int)
  sqrt(2.0); // sqrt(double)
  sqrt(z); // sqrt<double>(complex<double>)

}
/*
	Argument substitution Failure

	When looking for a best match for a
	set of arguments for a function template,
	the compiler considers whether the
	argument can be used in the way required
	by the complete function template declaration

	SFINAE - Substitution Failure Is Not An Error

	So, if - in the process of generating a candidate
	function to resolve a function call - the compiler
	finds itself generating a template specialization
	that would be nonsensical, that candidate is
	not entered into the overloading set.

	
*/

/*
	Overloading and Derivation

*/

template<typename T>
class B {/* .. */}

template<typename T>
 class D : public B<T> { /* ...*/  }

template<typename T> void f(B<T>*);

void f(B<int>* pb, D<int>* pd) 
{
	f(pb);  // f<int>(pb)
	f(pd);  // f<int>(static_cast<B<int>*>(pd))
			// standard conversion D<int>* to B<int>* used
}

/*

	Overloading and Non-Deduced parameters 
	
	A function argument that is not involved
	in the deduction of a template parameter
	is treated exactly as an argument of 
	a non-template function.

	This notation is sometimes called explicit specializtion.

*/

template<typename T, typename C>
T get_nth(C& p, int n);

struct Index {
	operator int();
}

void f(vector<int>& v, short s, Index it)
{

	int i1 = get_nth<int>(v, 2); // exact match
	int i2 = get_nth<int>(v, s); // standard conversion: short to int
	int i3 = get_nth<int>(v, i); // user-defined conversion: Index to int

}


















