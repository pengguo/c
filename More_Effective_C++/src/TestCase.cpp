

#include "TestCase.h"



NumOfClass & ThePrint() {
	static NumOfClass obj1;
	return obj1;
}

void function(Derived *ptr) {
	printf("in void function(Base *ptr)\n");
}

void PrintObj(const std::auto_ptr<TestAutoPrt> obj) {
	std::cout << "in PrintObj=" << obj->GetKey() << std::endl;
}

// Counted<DrivedPrint>::max_obj_num = 1;


