//============================================================================
// Name        : Effective_C++.cpp
// Author      : kevin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "rule_lib.h"
using namespace std;

int main() {
#if 0
	// Rule2: use const
	const TextBlock  text1("guopeng");
	TextBlock text2("shanshan");

    cout << text1[1] << endl;
    cout << text2[1] << endl;
#endif

#if 0
    House hou2(1);
    Drived * d1 = new Drived(1, 2);
    d1->GetDPart();
    d1->GetBase();
    House * h1 = d1;
    delete h1;
    d1->GetDPart();
    d1->GetBase();
#endif
#if 0
    // Rule: 12 copy each part of obj
    CopyClass c1(10);
    CopyClass c2(20);
    c1 = c2;
    DCopyClass dev1(10);
    dev1.GetBaseKey();
    dev1.GetDevKey();
    DCopyClass dev2(20);
    dev2 = dev1;
    dev2.GetBaseKey();
    dev2.GetDevKey();
#endif

#if 0
    // std::auto_ptr<CopyClass> aps(new DCopyClass(10));
    CopyClass * prt = new DCopyClass(10);
#endif

#if 0
    std::set_new_handler(OutofMem);
    int *p = new int[1000000000L];
#endif
#if 0
    PDeriveClass* a = new PDeriveClass;
    a->print(1);
    a->print();
    a->print("");
#endif

    Cb b;
    b.getName();

	cout << "Hello World!!!" << endl; // prints Hello World!!!
	return 0;
}
