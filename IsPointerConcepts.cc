// Program to check is pointer using
// c++20 concepts
#include <concepts>
#include <type_traits> 
#include <iostream>

// Define a concept 
/*
	Use the std::is_pointer_v(is a predicate
	returns true or false) to check
	for raw pointers.
	T::element_type detects  unique_ptr, shared_ptr, weak_ptr
*/
template<typename T>
concept IsPointer = std::is_pointer_v<T> ||
  requires(T v) {
		typename T::element_type
  }; 

// Using the IsPointer concept to
// type check the template parameter T
template<IsPointer T>
void check(const T& t)
{
	std::cout << "Iam a pointer";
}

// Using the requires clause
template<typename T>
void check(const T& t) requires(!IsPointer<T>)
{
	std::cout << "Iam not a pointer";
}


























