/*
 * TestCase.h
 *
 *  Created on: 2011-11-1
 *      Author: kevinguo
 */

#ifndef TESTCASE_H_
#define TESTCASE_H_
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>

class Base {
public:
	Base():m_data(0) {
		Initlation();
	}
	virtual void Initlation() {
		m_data = 10;
		printf("in Base::Initlation()\n");
	}
	virtual ~Base() {}
private:
	int m_data;
};

class Derived : public Base {
public:
	Derived() {}
    virtual void Initlation() {
    	printf("in Derived::Initlation()\n");
    }
    virtual ~Derived() {}
};

void function(Derived *ptr);

class MoreFunc {
public:
	MoreFunc() {}
	void Print() {
		printf("void Print()\n");
	}
	// 重载
	void Print(int a) {
		printf("void Print(int a)\n");
	}
};

// 控制class生成对象的数目
// 方法一:只允许生成一个对象, 不允许作为继承 或者组合
class NumOfClass {
public:
	// NumOfClass() {}
	void LogPrint(std::string &msg) {
		std::cout << msg << std::endl;
	}
friend NumOfClass & ThePrint();

private:
	NumOfClass() {}
	// static int num_obj;
};

// 方法二: 运行生成多个对象, 不允许作为继承 或者组合
class MoreOfClass {
public:
	void LogPrint(std::string &msg) {
			std::cout << msg << std::endl;
	}
	static MoreOfClass * MakeObj() {
		return (new MoreOfClass());
	}
	static MoreOfClass * MakeObj(const MoreOfClass &lrh) {
		return (new MoreOfClass(lrh));
	}
private:
	MoreOfClass() {}
	MoreOfClass(const MoreOfClass &lrh) {}

};

// 方法三: 采用baseClass方式进行
template <typename CountClass>
class Counted {
public:
	static int GetCount() {
		return obj_num;
	}
protected:
	Counted() {
		Init();
	}
	Counted(Counted &lns) {
		Init();
	}
	~Counted() {
		obj_num -= 1;
	}

private:
	static int obj_num;
	static const int max_obj_num;
	void Init() {
		if (obj_num > max_obj_num) {
			assert(false);
		} else {
			obj_num += 1;
		}
	}
};
class DrivedPrint : private Counted<DrivedPrint> {
public:
	DrivedPrint() {}
	virtual ~DrivedPrint() {}

};

class TestAutoPrt {
public:
	TestAutoPrt(int _key):key(_key) {}
	TestAutoPrt() {}

	virtual const int & GetKey() const {
		std::cout << "in TestAutoPrt::GetKey()" << std::endl;
		return key;
	}

private:
	int key;
};

class DerivedAutoPrt : public TestAutoPrt {
public:
	DerivedAutoPrt(int _key):TestAutoPrt(_key), new_key(_key+1) {}
	virtual const int &GetKey() const {
		return new_key;
	}

private:
	int new_key;
};

// 正确的做法, 是引用传递
void PrintObj(const std::auto_ptr<TestAutoPrt> obj);

class CountString {
public:
	CountString(const char *_value)
	: value(new StringValue(_value))
	{}
	~CountString() {
		if (--value->count == 0) delete value;
	}
    const char * GetString() const {
    	return value->data;
    }
    int GetCount() const {
    	return value->count;
    }
    CountString(const CountString &rhs) {
    	if (rhs.value->safe_to_copy) {
    	    value = rhs.value;
    	    value->count++;
    	} else {
    		value = new StringValue(rhs.value->data);
    	}
    }
    CountString & operator=(const CountString &rhs) {
    	if (value == rhs.value)
    		return *this;

    	// obj2 = obj1, obj2已经不在拥有之前的对象, 所以要释放掉

    	if (--value->count == 0) delete value; //

    	if (rhs.value->safe_to_copy) {
    	    value = rhs.value;
    	    ++value->count;
    	    return *this;
    	} else {
    		value = new StringValue(rhs.value->data);
    		return *this;
    	}
    }
    // 针对const string
    const char &operator[] (int _i) const {
    	return value->data[_i];
    }
    // string, 但无法区分读写操作, 只好已最复杂的写操作
    char & operator[](int _i) {
        value->safe_to_copy = false;
        return value->data[_i];
    }

private:
	struct StringValue {
		bool safe_to_copy;
		int count;
		char *data;
		StringValue(const char *value="")
		: count(1), safe_to_copy(true)
		{
			data = new char(strlen(value) + 1);
			strcpy(data, value);
		}
		~StringValue()
		{
			delete [] data;
		}
	};
	struct StringValue *value;
};

template <typename T>
class Array2D {
public:
	class Array1D {
	public:
		void SetArray1D(int _idx) {
			data = new T[_idx];
			if (NULL == data) {
				return;
			}
			memset(data, 0, sizeof(T)*_idx);
		}
		Array1D():data(NULL) {}
		T & operator[](int _index) {
			return data[_index];
		}
	private:
		T *data;
	};

public:
	Array1D & operator[] (int idx) {
		return array_1d[idx];

	}
	Array2D(int _id1, int _id2):mm('A') {
		array_1d = new Array1D[_id1];
		for (int i = 0; i < _id2; i++) {
			array_1d[i].SetArray1D(_id2);
		}
	}
	operator char() const {
		return mm;
	}

private:
	char mm;
	Array1D *array_1d;
};


class GameObj;
class SpaceShip;
class SpaceStation;

// base class
class GameObj {
public:
	virtual void collide(GameObj & obj) = 0;
};

class SpaceStation : public GameObj {
public:
	virtual void collide(GameObj & obj) {
	    printf("in SpaceShip::collide(GameObj & obj\n");
	}
	virtual void HitSpaceShip(GameObj &obj) {
		printf("in SpaceStation::HitSpaceShip(SpaceShip &obj) \n");
	}
	virtual void HitSpaceStation(GameObj &obj) {
		printf("in SpaceStation::HitSpaceStation(SpaceStation &obj) \n");
	}

private:

};


class SpaceShip : public GameObj {
public:
	virtual void collide(GameObj & other_obj) {
		printf("in SpaceShip::collide(GameObj & obj)\n");
		HitFuncPtr hit_func = LookUp(other_obj);
		if (hit_func) {
			(this->*hit_func)(other_obj);
		} else {
			printf("exception in SpaceShip::collide(GameObj & other_obj)\n");
		}
	}
	virtual void HitSpaceShip(GameObj &obj) {
		printf("in SpaceShip::HitSpaceShip(SpaceShip &obj) \n");
	}
	virtual void HitSpaceStation(GameObj &obj) {
		printf("in SpaceShip::HitSpaceStation(SpaceStation &obj) \n");
		SpaceStation & other_obj = dynamic_cast<SpaceStation &>(obj);
	}
private:
	typedef void (SpaceShip::*HitFuncPtr)(GameObj &obj);
	typedef std::map<std::string, HitFuncPtr> HitFuncMap;

	HitFuncMap * initFuncMap() {
		HitFuncMap * func_map = new HitFuncMap;
		(*func_map)["SpaceShip"] = &SpaceShip::HitSpaceShip;
		(*func_map)["12SpaceStation"] = &SpaceShip::HitSpaceStation;

		return func_map;
	}
	HitFuncPtr LookUp(const GameObj &obj){
		printf("in SpaceShip::LookUp(const GameObj &obj),"
				"class_type=%s\n", typeid(obj).name());
	    static std::auto_ptr<HitFuncMap> hit_map(initFuncMap());
	    HitFuncMap::iterator func = hit_map->find(typeid(obj).name());
	    if (func != hit_map->end()) {
	    	return func->second;
	    }
	    return NULL;
	}
};

class Animal {
public:
	Animal(const char * _name):name(_name) {}
	virtual ~Animal() {}
	virtual Animal & operator=(const Animal &other) {
		printf("in Animal::operator=(const Animal &other) \n");
		return *this;
	}
	virtual const std::string & GetName() const {
		return name;
	}

private:
	std::string name;
};

class Chicken:public Animal {
public:
	Chicken(const char * _name):Animal(_name) {}
	virtual ~Chicken() {}
	virtual Chicken & operator=(const Animal &other) {
		printf("in Chicken::operator=(const Animal &other) \n");
		return (operator=(dynamic_cast<const Chicken &>(other)));
	}
	Chicken & operator=(const Chicken &other) {
		return *this;
	}
};

class Pig : public Animal {
public:
	Pig(const char *_name):Animal(_name) {}
	virtual Pig & operator=(const Animal &other) {
		printf("in Pig::operator=(const Animal &other)\n");
	}
};

#endif /* TESTCASE_H_ */
