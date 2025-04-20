#include <set>
#include <string>

struct Person {
	std::string name;
};

template<typename Comparator>
auto  make_set(Comparator &&comparator)
{
	return std::set<Person, std::decay_t<Comparator>>{std::forward<Comparator>(comparator)};
}



int main()  {
		
	/* auto comparator = [](const Person &lhs, const Person& rhs){
		return lhs.name < rhs.name;
	};
	 std::set<Person, decltype(comparator)> set{std::move(comparator)}; */

	auto set = make_set<Person>([](const Person &lhs, const Person &rhs){
		return lhs.name < rhs.name;
	};
}




























