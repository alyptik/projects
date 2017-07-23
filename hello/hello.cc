#include <iostream>
#include <stddef.h>

using std::cout; using std::cin; using std::endl;

struct B {
	const char *derp = "weee";
	char const *noez = derp;
	B* next;
	//B() : derp("weee"), noez(derp) { cout << derp << endl; derp = "gerp"; noez = derp; }
	B() { cout << derp << endl; }
	~B() { cout << derp << endl << noez << endl; }
};
using A = struct B;
A derp;

class X {
	private:
	int foobar;

	public:
	X() : foobar(2), derp(2) {
		cout << "Object X at address: \"" <<
			this << "\" constructed" << endl;
	}
	~X() {
		cout << "Object X at address: \"" <<
			this << "\" destructed" << endl;
	}
	int derp;
	int operator+(const X &a);
	template <class T>
		X &operator=(const T &a);
};

template <class T>
	T expon(T, T);
template <class T>
	int get_bit(T);

int main(int argc, char **argv) {
	X x, y, z, *a, b[3];
	a = &b[0];
	char c[3] = { 'a', 'b', 'c' };
	for (int i=0; i < 3; i++)
		cout << (int *) &c[i] << endl;
	cout << c[0] << " in binary: " << get_bit(c[0]) << endl;
	cout << x.derp << " in binary: " << get_bit(x.derp) << endl;
	cout << x.derp << " " <<  y.derp << " " << z.derp << endl;
	cout << expon(10,2) << " " << expon<float>(10,-2) << endl;
	z = y + x;
	x = z;
	cout << "Size of int: " << sizeof(int) << endl;
	cout << x.derp << " " <<  y.derp << " " << z.derp << endl;
	cout << b[0].derp << " " <<  b[1].derp << " " << b[2].derp << endl;
	for (int i=0; i < 3; i++) {
		cout << "Object at \"" << a << "\" is " << sizeof(X) << " bytes" << endl;
		cout << a->derp << " " << endl;
		//a = (X *)((char *)a - 1);
		a++;
	}
	cout << "Hello World!" << endl;
	cout << "Total: " << argc << endl;
	for (int i=0; i < argc; i++)
		cout << "argv[" << i << "]: " << *(argv+i) << endl;
	return 0;
}

int X::operator+(const X &a) {
	return this->foobar + a.foobar;
}

template <class T>
	X &X::operator=(const T &a) {
	derp = foobar = a;
	return *this;
}

template <class T>
	T expon(T n, T e) {
	T c = 1;
	for(int k = 0; k < abs(e); k++)
		c *= n;
	c = (e < 0) ? 1/c : c;
	return c;
}

template <class T>
	int get_bit(T x) {
	int i = 0, b = 0, c = 1;
	bool a;
	//for (i=0; i < 8; i++) {
	while (i < sizeof(x) * 8) {
		a = ((1<<i) & x)/(1<<i);
		for (int k=0; k<i; k++)
			c *= 10;
		b += (c * a);
		c = 1;
		i++;
	}
	return b;
}

