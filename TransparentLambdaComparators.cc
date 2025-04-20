#include <set>
#include <string>

struct Person {
	std::string name;
};

template<typename Type, typename ...Comparator>
auto make_set(Comparator&& ... Comparator)
{
	// Inheriting from lambdas
	struct Compare: std::decay_t<Comparator>... {
		using std::decay_t<Comparator>::operator()...;
		using is_transparent = int;
	}

	// direct init base class of a struct using uniform init
	return std::set<Type, Compare>{Compare{std::forward<Comparator>(comparator)...}};
}

int main() {
	
	auto set = make_set<Person>(
		[](const Person &lhs, const Person& rhs){ return lhs.name < rhs.name; },
		[](const auto &lhs, const Person& rhs){ return lhs < rhs.name; },
		[](const Person &lhs, const auto &rhs){ return lhs.name < rhs; },
	);

}

























