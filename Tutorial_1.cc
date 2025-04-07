/* 
   Templates provide direct support for generic
   programming in the form of programming
   using types as parameters.
	
   The C++ template mechanism allows a type
   or a value to be a parameter in the
   definition of a class, function or type
   alias.

   A template depends only on the properties
   that it actually uses from its parameter
   types and does not require types
   used as arguments to be explicitly related.

   Built in types are acceptable and very common
   as template arguments.

   The composition offered by templates is type-safe
   (no object can be implicitly used in a way it
   disagrees with its definition).

   Every  major STL abstraction is represented as
   a template (string, tuple, function, list, thread
   , unique_ptr).

*/

// General string type 

template<typename C> // type argument C, C is a type name
class String {
	public:
		String();
		explicit String(const C*);
		String(const String&);
		String operator=(const String&);
		// ..
		C& operator[](int n) { return ptr[n]; }
		String& operator+=(C c);
		// ..
	private:
		static const int short_max = 15;
		int sz;
		C* ptr; 
};

String<char> cs;
String<unsigned char> us;
String<wchar_t> ws;

struct Kchar { /* ... */  };
String<Kchar> ks;
 
// ---------- Defining a Template ----------
/*
	A class generated from a template is a
	perfectly ordinary class.

	Using a template class can lead to a
	decrease of code generated because code
	for a member function of a class template
   is only generated if that member is used.


   A template is a specification of how to 
   generate something given suitable arguments.

   A member of a class template is defined
   exactly as they would have been for a 
   non-template class.

   A template member need not be defined
   within the template class itself.In that
   case, its definition must be provided
   somewhere else, just as for non-template
   class members.

   Members are parametized by the params
   of their template class.
   When such a member is defined outside
   its class, it must explicitly be
   declared a template.

*/

template<typename C>
String<C>::String() 
	: sz{0}, ptr{ch}
	{
		ch[0] = {};
	}

template<typename C>
String& String<C>::operator+=(C c)
{
	return *this;
}
/*
	It is not possible to overload a class
	template name, so if a class template
	is declared in a scope, no other entity
	can be declared there with the same
	name.

	A type used as a template argument must
	provide the interface expected by the
	template.

*/

/*

	Member functions
	can be defined in-class or outside the class/

	A member function can be virtual or not
*/

template<typename T>
struct X {
	void mf1() { /* ... */} // defined in class
	void mf2();
}

template<typename T>
void X<T>::mf2() { /* ... */  } // defined out of class

/*
  Member Type Aliases
  whether introduced by typedef of using
*/

template<typename T>
class Vector {
	public:
		using value_type = T;
		using iterator = Vector_iter<T>;
	    // ...
}

/* 
	static Members
	A static data or function member that
	is not defined in-class must have a 
	unique definition in a program.
*/
template<typename T>
struct X {

	static constexpr Point p{100, 250};
	static const int m1 = 7;
	static int m3;
	static int m2 = 8; // error: not const
	static void f1() {/* .. */}
	static void f2();
};

template<typename T> int X<T>::m1 = 8; // error: two init
template<typename T> int X<T>::m3 = 55;

template<typename T> X::<T>::f2() {/* .. */}

/* 
	A static member need be defined
	if it is used.
*/
template<typename T>
struct X {
	static int a;
	static int b;
};

int* a = &X<int>::a;
/*
	Member Templates

	A class or a class template can have
	members that are themselves templates.

	This allows us to represent related
	types with a degree of control
	and flexibility.

*/
template<typename Scalar>
class complex {
	Scalar re, im;
	public:
		complex() : re{}, im{} {}
		template<typename T>
		 complex(T re, T ii = 0) : re{rr} , imt {ii} {}

		complex(const complex*) = default
		template<typename T>
			complex(const complex<T>& c) :
				re {c.real()}, im {c.imag()} {}
		
		// ..

}

complex<float> cf; // default value
complex<double> cd {cf}; // Ok: uses float to double conversion
complex<float> cf2 {cd}; // error: no implicit double-> float conversion

complex<float> cf3 {2.0,3.0}; // error: no implicit double->float
complex<double> cd2 {2.0F,3.0F}; // Ok: uses float to double conversion

/*
	Formally, a member of template depends 
	on all of a template's arguments.

	Avoid nested types in templates
	unless they genuinely rely on every
	template parameter.

	We cannot directly make a template
	a friend of a class, but we can make
	a friend declaration a template

*/

template<typename U, typenameT>
class List;

template<typename T>
class Link {
	template<typename U, typename A>
		friend class List;
}


















