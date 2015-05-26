#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <map>
using namespace std;


class Graph {
public:
	map<string, vector<string>> nodes;
	//unordered_map<string, vector<string>> nodes;
	void add_node(std::string name, vector<string> deps) {
		if (nodes.find(name) != nodes.end()) {
			//nodes[name] = nodes[name]. deps;
		}
		else {
			nodes[name] = deps;
		}
	}

	bool cycle_deps_find_recurcive(set<string> finded, string node) {
		bool cycles = false;
		finded.insert(node);

		for (auto n : nodes[node]) {
			if (finded.count(n) > 0)
				return true;
			else {
				cycles |= cycle_deps_find_recurcive(finded, n);
			}
		}
		return cycles;
	}

	vector<string> cycle_deps_find() {
		vector<string> cycles;
		for (auto i : nodes) {
			if (cycle_deps_find_recurcive(set<string>(), i.first)) {
				cycles.push_back(i.first);
			}
		}
		return cycles;
	}
};



int main(){
	size_t	quantity;
	std::cin >> quantity;
	std::cin.ignore(1);

	Graph	my_graph;

	for (unsigned int i = 0; i < quantity; i++) {
		string name;
		vector<string> deps;
		size_t	links_q;
		cin >> name >> links_q;
		for (size_t j = 0; j < links_q; j++) {
			string depend;
			cin >> depend;
			deps.push_back(depend);
		}
		my_graph.add_node(name, deps);
	}

	vector<string> cycles = my_graph.cycle_deps_find();

	for (auto i : cycles) {
		cout << i << endl;
	}

	std::cout << std::endl;
	return 0;
}