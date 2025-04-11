/*
	Templates and Hierachies
	------------------------------------
	Templates and derivation are mechanisms
	for building new types out of existing
	ones, for specifying interfaces and 
	generally for writing code that is
	useful that exploits the various
	forms of commonality.

	1. A template class defines an interface.
	   The template's own implementation and
	   those of its specialization can be
	   accessed through that interface.

	   A specialization can add functionality
	   to what the primary template offers.

	2. A base class defines an interface.
	   A derived class can add functionality
	   to what the base class offers.

	  From a design perspective, the two approches
	  are close enough and deserve a common name.
	  Since both allow an algorithm to be expressed
	  once and applied to a variety of types, people
	  refer to both as polymorphic.

	  To distinguish them, what virtual functions
	  provide is called run-time polymorhphism,
	  and what template offer is called compile-time
	  polymorphism or parametric polymorphism.

	  Object-oriented programmers tend to focus 
	  on the design of hierachies of classes (types)
	  with an interface being an individual class.

	  Generic programmers tend to focus on the design
	  of algorithms with the concepts for template
	  arguments providing an interface that can 
	  accomodate many types.

	  Master both techniques.

	  vector<Shape*> is a compile-time polymorphic
	  (generic) container holding elements from
	  a run-time polymorphic (object-oriented) 
	  hierachy.

      Parametization and Hierachy
	  ---------------------------------------

	  Combinations of templates and class hierachies
	  are the basis for many useful techniques.

	  1. When do we choose to use a class template?
	  2. When do we rely on a class hierachy?
*/

template<typename X>
class Ct { // interface expressed in terms of parameter
	X mem;
public:
	X f();
	int g();
	void h(X);
};

template<>
class Ct<A> { // specialization for A
	X* mem;
public:
	A f();
	int g();
	void h(A);
	void k(int); // added functionality
};

Ct<A> cta;
Ct<B> ctb;

/*
	I used explicit specialization
	to show that implementations can vary
	from what the primary template offers
	and that it is possible to add functionality.

*/

class X {
	// ..
};

class Cx {
	X mem;
public:
	virtual X& f();
	virtual int g();
	virtual void h(X&);
};

class DA : public Cx {
	public:
		X& f();
		int g();
		void h(X&);
};

class DB: public Cx {
	DB* p;
	public:
		X& f();
		int g();
		void h(X&);
		void k(int);
};

Cx& cxa {*new DA};
Cx* cxb {*new DB};

/*
	I use references in the hierachial version
	to reflect that we must manipulate derived
	class objects through pointers or references
	to preserve run-time polymorphic behaviour.
*/

/*
	How to choose between derived classes or templates
	
	1. If the types in the interface to the generated
	   or derived classes need to differ, templates
	   have an advantage.
	2. If the implementations of generated or derived
	   classes differ only through a parameter or 
	   differ only in a few special cases, templates
	   have an advantage.
	3. If the actual types objects used cannot be known
	   at compile time, a class hierachy is essential
	4. If a hierachial relationship is required between
	   generated or derived types, hierachies have 
	   an advantage.
	5. If explicit use of free store is undesirable,
	   templates have an advantage.
	6. If run-time efficiency is expensive, templates
	   should be used.

*/

/*
	Generated Types
	--------------------------------------
	
	A class template is usefully understood as a
	specification of how particular types are
	to be created.

	A class template is sometimes called a
	type generator.
	
	As far as the C++ language rules are concerned
	, there is no relationship between two classes
	generated form a single class template.

	The combination of an array and a base class
	is particularl nasty because a built-in array
	does not offer type safety provided by 
	containers.

	Nb-------------------

	1. Prefer containers over built-in arrays.

	Template Conversions
	-----------------------------------------
	There cannot be any default relationship
	between classes generated from the same 
	template.

	However,for some templates we would like
	to express such a relationship.
	For example, when we define a pointer
	template, we would like to reflect
	inheritance relationships among the objects
	pointed to.

	An alternative solution to this probleme
	uses type traits and enable_if().


	Hierachies of Class Templates
	--------------------------------------
	Using oop, a base class is often used to
	provide a common interface to a set of 
	derived classes.

	Try to avoid parameters that only affect
	a few members.

	If only a few member functions are affected
	by a parameter, try to make those function
	templates with that parameter.

	Templates as Interfaces
	--------------------------------------------
	A template class can be used to provide
	a flexible and type-safe interface to a
	common implementation.

	In general, this technique can be used to
	provide type-safe interfaces and for localizing
	casts to implementation, rather than forcing
	users to write them.
	
	Template Parameters as Base Classes
	-----------------------------------------
	In classical OOP using class hierachies, we place
	information that can be different for different
	classes in a derived class and access it through
	virtual functions in a base class.

	This technique does not allow us to vary the types
	used in the interface.

	To compensate, we might pass the specialized infomatoin
	and operations to the base class as template arguments.

	In fact, a template argument can be used as a base
	class.

	CRTP Curiously Recurring Template Pattern.

	Linearizing Class Hierachies
	--------------------------------------------




*/























