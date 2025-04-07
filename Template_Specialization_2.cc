/*
	Specialization
	
	By default, a template gives a single
	definition to be used for every template
	argument (or combination of template 
	arguments) that a user can think of.

	user-defined specialization/specializations

	template<> prefix says that this is a
	specialization that can be specified without
	a template parameter.

*/

template<>
class Vector<void*> {
	void** p;
	// ..
	void*&operator[](int i);
};

/* 
	This specialization can be used as
	the common implementaion for all 
	Vectors of pointers.
*/
template<typename T>
class Vector<T*> : private Vector<void*>
{
	public:
		using Base = Vector<void*>;
		Vector() {}
		
		explicit Vector(int i: : Base(i) {}
		
		T*& elem(int i) { return
			reinterpret_cast<T*&>(Base::elem(i)); }
		
		T*& operator[](int i){ 
			return reinterpret_cast<T*&>(Base::operator[](i));
		}

		// ..
};

Vector<Shape*> vps; // <T*> is <Shape*> so T is Shape
Vector<int**> vppi; // <T*> is <int*> so T is int*

/* 
	A specialization with a pattern containing
	a template parameter is called partial
	specialization.

	Specialization is a way of specifying
	alternative implementations of different
	uses of a common interface.

	Interface specialization.

	Implementation Specialization

	Specialization can be used to provide
	alternative implementations of a class
	template for a specific set of template
	parameters.

*/
template<typename T, int N>
class Matrix;

template<typename T, 0>
class Matrix {
	T val;
	// ..
};

template<typename T, 1>
class Matrix {
	T* elem;
	int sz;
	// ..
};

template<typename T, 2>
class Matrix {
	T* elem;
	int dim1;
	int dim2;
	// ..
};

/*
	
	The Primary Template
	
	The primary template defines the
	interface to all specializations.

	It is used to determine if a use
	is valid and takes part in 
	overload resolution.

	The primary template must be declared
	before any specialization.
	
	The critical information supplied by the
	primary template is the set of template
	parameters that a user must supply it
	or any of its specializations.

	If we have defined a constraint check
	for a template, the primary template is
	where it belongs because concepts are 
	something a user cares about and must
	understand to use the template.

	A declaration of the primary template
	is sufficient to allow the definition
	of specialization.

	If the primary template is never instantiated,
	it need not be defined.
*/

template<typename T>
class List { 
	// ..
}

template<typename T>
class List<T*> {
	// ..
}




/*
	Order of Specialization   
	
	One specialization is more specialized
	than another if every argument list 
	that matches its specialized pattern
	also matches the other, but not vice versa.

	The most specialized version will be
	preferred over others in declarations of
	objects. pointers, etc.

	A specialization pattern can be specified
	in terms of types composed using constructs
	allowed for template parameter deduction.


*/

template<typename T>
class Vector;

template<typename T>
class Vector<T*>;

template<>
class Vector<void*>;

/*
	
	Functions take part in overloading
	whereas only the primary template
	takes part in specialization.

*/






























