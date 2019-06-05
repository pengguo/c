//============================================================================
// Name        : More_Effective_C++.cpp
// Author      : kevin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "TestCase.h"



int Print(int a) {
	std::cout << "in void Print(int a)" << a << std::endl;
	return 0;
};


int main() {

#if 0
	// Rule:2  use C++ cast instead of C
	Base *ptr = new Derived();
    Derived obj;
	const Derived &anthor_name = obj;
	// function(ptr); //error
	function(dynamic_cast<Derived *>(ptr));
	function(const_cast<Derived *>(&anthor_name));

	typedef void (*Func_Ptr)(int );
	Func_Ptr f_ptr = reinterpret_cast<Func_Ptr>(&Print);
    (*f_ptr)(11);
#endif

#if 0
    // Rule26: control num of obj
    std::string msg("Printer::hello world");
    ThePrint().LogPrint(msg);
    MoreOfClass * obj1 = MoreOfClass::MakeObj();
    MoreOfClass * obj2 = MoreOfClass::MakeObj(*obj1);
    delete obj1;
    delete obj2;
#endif

#if 0
    // Rule28: smart pointer,����ָ��
    std::auto_ptr<TestAutoPrt> p1(new TestAutoPrt(1));
    std::cout << "GetKey()=" << p1->GetKey() << std::endl;
    PrintObj(p1); //����ָ�봫��ʱ, ��p2 = p1, ��ֵ��, p1���Զ������

    std::auto_ptr<TestAutoPrt> der_p(new DerivedAutoPrt(2));
    std::cout << "GetKey()=" << der_p->GetKey() << std::endl;
    // attention!!!:
    // if use like this:
    //   TestAutoPrt new_der = *der_p;
    // then
    //   new_der.GetKey() = 2!!, not 3
    TestAutoPrt & new_der = *der_p;
    std::cout << "new_der.GetKey()=" << new_der.GetKey() << std::endl; //is 3
    std::cout << "der_p->GetKey()=" << der_p->GetKey() << std::endl; // ok
#endif

#if 0
    // Rule29: ���ü���
    CountString obj1("guopeng");
    std::cout << (obj1.GetString()) << std::endl;
    CountString obj2(obj1);
    std::cout << (obj2.GetString()) << " and " << obj2.GetCount() << std::endl;
    CountString obj3("c++");
    obj3 = obj1;
    std::cout << (obj3.GetString()) << " and " << obj3.GetCount() << std::endl;

    // ����String�����Ƿ�֧��'дʱ����'
    std::string s1("abcd");
    char *p = &s1[1];
    std::string s2 = s1;
    std::cout << "s1=" << s1 << ", s2=" << s2 << std::endl;
    *p = 'M';
    std::cout << "s1=" << s1 << ", s2=" << s2 << std::endl;
    // ����CountString��ȫ�Ƿ�֧�� 'дʱ����'
    CountString cs1("abcd");
    char *cp = &cs1[1];
    CountString cs2 = cs1;
    std::cout << "cs1=" << cs1.GetString() << ", cs2=" << cs2.GetString() << std::endl;
    *cp = 'M';
    std::cout << "cs1=" << cs1.GetString() << ", cs2=" << cs2.GetString() << std::endl;
#endif

#if 0
    // Rule:30 proxy class
    Array2D<int> arr(10,10);
    char c = arr;
    std::cout << arr[0][0] << ", " << c << std::endl;
#endif

#if 0
    // Rule31: double dispatching, ��ʵ��'����'������黯
    SpaceShip ship1;
    SpaceStation station1;
    ship1.collide(station1);
#endif

    Animal ani1("monkey");
    Animal ani2("horse");
    ani2 = ani1;
    Animal * pig1 = new Pig("pig1");
    Animal * ch1 = new Chicken("chicken1");
    Animal * ch2 = new Chicken("chicken2");
    *ch1 = *ch2;


	std::cout << "Hello World!!!" << std::endl; // prints Hello World!!!
	return 0;
}
