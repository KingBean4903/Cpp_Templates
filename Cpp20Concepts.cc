/*
	What is a concept?

	These are a template's requirements
	for its arguments.

	In other words what must a type
	provide to be acceptable as an argument
	to a template ?
	
	Sample concept

*/

// Code below defines a floating point concept
template<typename T>
concept is_floating_point = std::is_floating_point_v<T>;

// We can also define a concept using a 
// requires expression
template<typename T>
concept IsInt = requires(T v, int i) {
	{ v.f(i) } -> std::same_ad<int>;
};

/*  How to use concepts   */
template<typename T>
requires CONDITION
void func(T param) { }

template<typename T>
requires std::integral<T> || std::floating_point<T>
constexpr double Average(std::vector<T>const &vec) {
	const double sum = std::accumulate(vec.begin(),
		vec.end(), 0.0);
	return sum / vec.size();
}

template<typename T>
void print(const std::vector<T>& vec) {
	for (size_t i = 0; auto& elem : vec)
		std::cout << elem << (++i == vec.size() ? "\n" : ", ");
}

// I used constrained auto
void print2(const std::vector<auto>& vec) {
	for (size_t i = 0; auto& elem : vec) 
		std::cout << elem << (++i == vec.size() ? "\n" : ", ");
}

void print3(const std::ranges::range auto& container){
	for (size_t i = 0; auto && elem : container)
		std::cout << elem << (++i == container.size() ? "\n" : ", ");
}

template<std::integral T>
auto sum(const std::vector<T>& vec) {
	// ..
}

/* Comparing Numbers  */
template<typename T>
requires std::is_floating_point_v<T>
constexpr bool close_enough20(T a, T b)
{
	return absolute(a - b) < precision_threshold<T>;
}

constexpr bool close_enough2(auto a, auto b)
{
	return a == b;
}

constexpr bool close_enough20(std::floating_point auto a,
							std::floating_point auto b)
{
	return absolute(a - b) < precision_threshold<
		std::common_type_t<decltype(a), decltype(b)>>;
}

constexpr bool close_enough2(std::integral auto a,
						std::integral auto b) {
	return a == b;
}

template<std::is_floating_point T>
constexpr bool close_enough20(T a, T b) {
	return absolute(a - b) < precision_threshold<T>;
}


// ---------------------------------------------------
/*
	Computing the Average
*/

template<typename T>
require std::is_integral_v<T> || std::is_floating_point<T>
constexpr double Average(const std::vector<T>& vec) {
	const double sum = std::accumulate(vec.begin(), vec.end(), 0.0);
	return sum / static_cast<double>(vec.size);
}

template<typename T>
concept numeric  = std::is_integral_v<T> || std::is_floating_point<T>;

template<typename T>
require numeric
constexpr double Average2(std::vector<T> const& vec) { 
	const double sum = std::accumulate(vec.begin(),
			vec.end(), 0.0);
	return sum / static_cast<double>(vec.size());
}

constexpr double Average3(std::vector<numeric auto> const &vec) {
	const double = std::accumulate(vec.begin(), vec.end(), 0.0);
	return sum / static_cast<double>(vec.size());
}
























