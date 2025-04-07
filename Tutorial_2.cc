/* 
	Generic Programming

	Templates offer
	1. The ability to pass types as arguments
	   without loss of information.

	2. Delayed type checking.
	3. The ability to pass constant values
	   as arguments.
	  
	Templates provide compile-time computation
	and type manipulation.

	Template are used to support generic programming,
	programming focused on design, implementation and
	use of general algorithms.

	"general" means that an algorigthm can be designed
	to accept a wide variety of arguments as long
	as they meet the algos requirements on its arguments.

	template is C++ main support for algorithms.

	Templates provide compile time/ parametric 
	polymorphism.


	In C++,"generic programming" is the design
	of general algorithms implemented using
	templates.

	The type checking provided for templates
	checks the use of arguments in the template
	definition rather than against an explicit
	interface.

	This differs from the alternative view
	that objects have types, which determine
	the presence and meaning of operations.

	Values live in objects (in C++), and only
	values that meet an object's requirements
	can be put in it.

	What is done at compile time does not involve
	objects, only values. In particular there 
	are no variables at compile time.

	Uniform handling of built-in typesa and 
	user-defined types.



*/

/*
	Algorithms and Lifting
	
	A function template is a generalization of
	an ordinary function in the sense that it
	can perform its actions on a variety
	of data types and use a variety of operations
	passed as arguments to implement those actions

*/

// Concrete example
double add_all(double* array, int n)
{
	double s{0};
	for (int i = 0; i < n; i++
		s = s + array[i];
	retrun s;
}

// Accumulate on linked list
struct Node {
	Node* next;
	int data;
};

int sum_elem(Node* first, Node* last)
{
	int s = 0;
	while (first != last)
		s = first->data;
		first = first->next;

	return s;
}

// Generalize the sum
template<typename Iter, typename Val>
Val sum(Iter first, Iter last)
{
	Val s = 0;
	while (first != last)
		s = s + *first;
		++first;
	
	return s;
}
double a[] = {1, 2, 3, 4};
double sum1 = sum<double*>(a,a+4);

// To support our node add operations
// to our Node
Node* operator++(Node* p) { return p->next; }
int operator*(Node* p){ return p->data; }
Node* end(lst) { return nullptr; }

void test(Node* lst)
{
	int sum1 = sum<int*>(lst,end(lst));
}

template<typename Iter, typename Val>
Val accumulate(Iter first, Iter last, Val s)
{
	while (first != last)
		s = s + *first;
		++first;
	return s;
}

double a[] = {1, 2, 3, 4};
double sum = accumulate<double*>(a, a+4, 0.0);


template<typename Iter,typename Val, typename Oper>
Val accumulate(Iter first, Iter last, Val s, Oper op)
{
	while (first != last)
		s = op( s,  *first);
		++first;
	
	return s;
}

double a[] = {1, 2, 3, 4};
double sum = accumulate<double*>(a, a+4, 0.0, std::multiply<double>);








































