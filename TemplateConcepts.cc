/* 

	Concepts

	What are a template's requirements for its
	arguments?

	What must a type provide to be acceptable
	as an argument to a template?

	What we need to do is to identify a small
	number of concepts (set of requirements)
	that can be used for many templates 
	and many types of arguments.

	Stages of analysis when looking for concepts

	1. First, we look at our(initial) implementation
	   and determine which properties (operations, 
	   functions, member types, etc).

	2. Next we look at plausible template implementations
	   and list their requirements on their template
	   arguments.
	3. Finally, we look at the resulting list of
	   required properties and compare to lists
	   of requirements that we have used for other
	   templates.

	A concept is a carefully crafted entity that
	reflest the fundamental properties of an
	application domain.

	We can approximate concepts using code
	that performs compile-time checks
	of template argument properties.

	A concept is a predicate; that is
	we think of a concept as a compile-time
	function that looks at a set of template
	arguments and returns true if they meet
	the concept's requirements and false if
	they don't.

	So, we implement a concept as constexpr
	function.

	Axioms

	It is something we assume to be true.
	
	In the context of requirements for
	template arguments, we use "axiom" to
	refer to semantic properties.

	We use an axiom to state what a class
	or an algorithm assumes about its
	set of inputs..


*/
































