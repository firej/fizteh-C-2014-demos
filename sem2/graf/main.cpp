#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <stack>
//#include <pairs>
using namespace std;

class NotFound{};
class FoundAnotherOne{};
class IteratorAtEnd{};

template <class V, class T>
class graph {
private:
	map<string, V>						vertexes;
	multimap<string, pair<string, T>>	links;
	bool								directional;
public:
	graph(){};
	~graph(){};

	void	add_vertex(string vertex, V info) {
		if (vertexes.find(vertex) != vertexes.end()) {
			throw FoundAnotherOne();
		}
		vertexes[vertex] = info;
	}

	void	add_link(string from, string to, T info) {
		if (vertexes.find(from) == vertexes.end() || vertexes.find(to) == vertexes.end()) {
			throw NotFound();
		}
		links.insert(make_pair(from, make_pair(to, info)));
	}

	friend istream& operator>>(istream& istr, graph& g) {
		string tmp;
		getline(istr, tmp);
		if ("nondir" == tmp) {
			g.directional = false;
		}
		else {
			g.directional = true;
		}

		g.vertexes.clear();
		g.links.clear();

		while (istr.good()) {
			getline(istr, tmp);
			if ('(' == tmp[0]) {
				string from = tmp.substr(1, tmp.find(',') - 1);
				string to = tmp.substr(tmp.find(',') + 1, tmp.find(')') - tmp.find(',') - 1);
				string value = tmp.substr(tmp.find("=>") + 2);
				g.add_link(from, to, value);
			}
			else {
				string vertex = tmp.substr(0, tmp.find(' '));
				string value = tmp.substr(tmp.find(' ') + 1);
				g.add_vertex(vertex, value);
			}
		};
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const graph& g) {
		if (g.directional) {
			ostr << "dir" << endl;
		}
		else {
			ostr << "nondir" << endl;
		}
		//ostr << "Vertexes:" << endl;
		for (auto v : g.vertexes) {
			ostr << v.first << " " << v.second << endl;
		}
		//ostr << "Links:" << endl;
		for (auto l : g.links) {
			ostr << '(' << l.first << ","<< l.second.first << ")=>" << l.second.second << endl;
		}
		return ostr << endl;
	}

	class dfsiterator{
		graph*	master;
		set<string>		seen;
		string			v;
		stack<string>	dfs;
	public:
		dfsiterator(graph& m) : master(&m), v(master->vertexes.begin()->first) {}
		~dfsiterator(){}

		dfsiterator& operator++(int){
			if (v == "konec!") {
				throw IteratorAtEnd();
			}
			seen.insert(v);
			do {
				for (auto i = master->links.find(v); i->first == v; i++){
					if (seen.find(i->second.first) != seen.end()) {
						continue;
					}
					else {
						dfs.push(v);
						v = i->second.first;
						return *this;
					}
				}
				if (!dfs.empty()) {
					v = dfs.top();
					dfs.pop();
				}
				else {
					v = "konec!";
					return *this;
				}
			} while (!dfs.empty() || v == master->vertexes.begin()->first);
			return *this;
		}

		string	operator *(){
			if (v == "konec!") {
				throw IteratorAtEnd();
			}
			return v;
		}

		pair<string, V> operator ->() {
			if (v == "konec!") {
				throw IteratorAtEnd();
			}
			return makepair(v, master->vertexes[v]);
		}
	};
	void do_dfs() {}
};


int main(){
	graph<string, string> my_graph;
	ifstream test_file;
	test_file.open("test.txt", ifstream::in);
	test_file >> my_graph;

	graph<string, string>::dfsiterator it(my_graph);
	do {
		try {
			cout << *it << endl;
			it++;
		}
		catch (IteratorAtEnd i) {
			break;
		}
	} while (true);
	return 0;
}