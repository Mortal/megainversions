#include <vector>
#include <iostream>

using namespace std;

struct fenwick {
	inline fenwick(size_t n)
		: n(n)
		, data(n)
	{}

	inline static size_t lowbit(size_t n) {
		return n & -n;
	}

	inline void add(size_t k, int x = 1) {
		if (!k) return;
		while (k <= n) {
			data[k] += x;
			k += lowbit(k);
		}
	}

	inline size_t query(size_t k) {
		size_t result = 0;
		while (k > 0) {
			result += data[k];
			k -= lowbit(k);
		}
		return result;
	}

	size_t n;
	vector<int> data;
};

int main() {
	size_t n;
	cin >> n;

	// round up to nearest power of two
	size_t upperbound = 1;
	while (upperbound < n) upperbound *= 2;

	fenwick numbers(upperbound);
	fenwick inversions(upperbound);
	size_t megainversions = 0;

	for (size_t _ = 0; _ < n; ++_) {
		int num;
		cin >> num;
		numbers.add(num);
		inversions.add(numbers.query(n)-numbers.query(num));
		megainversions += inversions.query(n)-inversions.query(num);
	}
	cout << megainversions << endl;
	return 0;
}
// vim:set sw=4 sts=4 ts=4:
