#pragma warning(disable:4786)
#include <set>
#include <iostream>

using namespace std;

class A
{
public:
	A(){ cout << "Default Constructing A" << endl; }
	A(int i) { 
		cout << "Conversion Constructing A" << endl; 
		a = i;
	}

	~A(){ cout << "Destructing A" << endl; }
	A(const A& rA) { 
		cout << "Copy constructing A" << endl;
		a = rA.a;
	}
	A& operator=(const A& rhs) {
		cout << "Assignment operator A" << endl;
		if (this == &rhs)
			return *this;
		a = rhs.a;
	}

protected:
	int a;
};

class B
{
public:
	B(){ cout << "Constructing B" << endl; }
	B(int i) {
		cout << "Conversion Constructing B" << endl;
		b = i;
	}
	~B(){ cout << "Destructing B" << endl; }
	B(const B& rB) {
		cout << "Copy constructing B" << endl;
		b = rB.b;
	}
	B& operator=(const B& rhs) {
		cout << "Assignment operator B" << endl;
		if (this == &rhs)
			return *this;
		b = rhs.b;
	}

protected:
	int b;
};

class hasAandB

{
public:
	hasAandB() { cout << "hasAandB default constructor" << endl; }
private:
	A m_a;
	B m_b;
};
A returnsA(const A argA)
{

	cout << "Takes and returns A" << endl;
	A tmpA;

	cout << "Copying A" << endl;
	tmpA = argA;
	cout << "Returning A" << endl;

	return tmpA;
}
int main(int argc, char *argv[])
{
	A myA1, myA2(5);
	//B myB1, myB2(10);

	cout << "assign " << endl;
	myA1 = myA2;
	
	//B myB3 = myB2;
	cout << endl << endl << endl;
	A myA3 = returnsA(myA1);


	hasAandB hab1;

	hasAandB hab2 = hab1;
	cout << "Done" << endl;

}
