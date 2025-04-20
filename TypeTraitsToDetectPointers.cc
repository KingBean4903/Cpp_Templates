#include <iostream>
#include <type_traits>

// Type alias
template<bool B, typename T>
using Enable_if = typename std::enable_if <B,T>::type;


template<typename T>
constexpr bool IsPointer()
{
	return std::is_pointer<T>::value;
}

template<typename T>
Enable_if<IsPointer<T>()> check(const T& t)
{
	std::cout << "I am a pointer";
}

template<typename T>
Enable_if<!IsPointer<T>()> check(const T& t)
{
	std::cout << "I am not a  pointer";
}

template<typename T>
struct is_any_pointer : std::false_type {};


template<typename T>
struct is_any_pointer<T*> : std::true_type {};

template<typename T>
constexpr bool is_any_pointer_v = std::is_pointer<T>::value;

int main() {
	
	int a = 9;
	int *p = &a;

	check(a); // Iam not a pointer
	check(p); // I am a pointer

	std::cout << is_any_pointer_v<int> << std::endl; // false	
	std::cout << is_any_pointer_v<int*> << std::endl; // true 

}
