#include <iostream>
#include "./shape.h"
using namespace std;

int main(){
	point p1, p2, cen, p3;
	double r;
	cout << "Enter first point: " << endl;
	cin >> p1.first >> p1.second;
	cout << "Enter second point: " << endl;
	cin >> p2.first >> p2.second;
	cout << "Enter circle parametrs: " << endl;
	cin >> r >> cen.first >> cen.second;
	Circle c(cen, r);
	segment s(p1,p2);
	try{
		p3 = c.Cross(s);
		cout << "Result: ( " << p3.first << "; " << p3.second << ")" << endl;
	}
	catch (const CircleException ce){
		cout << "Exception caught!" << endl;
	}
	system("pause");
	return 0;
}