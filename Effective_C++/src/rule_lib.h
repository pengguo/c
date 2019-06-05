/*
 * rule_lib.h
 *
 *  Created on: 2011-12-20
 *      Author: kevinguo
 */

#ifndef RULE_LIB_H_
#define RULE_LIB_H_
#include <stdio.h>
#include <string>

class TextBlock {
public:
	TextBlock(const char * _str):m_text(_str) {}
    virtual ~TextBlock() {}
    char & operator[](int _idx) {
    	printf("char & operator[](int _idx) \n");
    	return const_cast<char &>(static_cast<const TextBlock>(*this)[_idx]);// !! 两次转型
    }
    const char & operator[](int _idx) const {
    	printf("const char & operator[](int _idx) const \n");
    	return m_text[_idx];
    }

private:
	std::string m_text;
};


class House{
public:
	House(int _i):id(_i) {}
	virtual ~House() {id=0;}
	void TestAutoCpy() const {
		printf("name = %d\n", id);
	}
	void GetBase() const {
		printf("in base, id=%d\n", id);
	}
private:
	// 禁止编译器自动生成拷贝和赋值函数
	House(const House &);
	House & operator=(const House &);
	int id;
};

class Drived : public House {
public:
	Drived(int _b, int _d):House(_b), d_part(_d) {}
	virtual ~Drived() {d_part=0;}
	void GetDPart() const {
		printf("d_part = %d\n", d_part);
	}
private:
	int d_part;
};

class BaseLog {
public:
	BaseLog() { FlushLog();}
	virtual ~BaseLog() {}
	virtual void FlushLog() const {
		printf("in BaseLog::FlushLog()\n");
	}
};

class WadeLog : public BaseLog{
public:
	WadeLog(int _k):key(_k) {}
	virtual void FlushLog() const {
		printf("in WadeLog::FlushLog()\n");
	}

	WadeLog & operator=(const WadeLog &rhs) {
		if (this == &rhs) return *this;
        key = 1000; // some thing like delete
        key = rhs.key;
	}
	void GetKey() const {
		printf("key=%d\n", key);
	}
private:
	int key;
};

class CopyClass{
public:
	CopyClass(int _i):base_key(_i)
	{
		printf("Construction in CopyClass\n");
	}
	virtual ~CopyClass() {
		printf("Destruction in CopyClass\n");
	}
	CopyClass & operator=(const CopyClass &rhs) {
		 if (this == &rhs)
			 return *this;
         base_key = rhs.base_key;
         return *this;
	}
	void GetBaseKey() const {
		printf("base_key=%d\n", base_key);
	}
private:
	int base_key;
};

class DCopyClass : public CopyClass{
public:
	DCopyClass(int _i): CopyClass(_i), dev_key(_i+1)
	{
		printf("Construction in DCopyClass\n");
	}
	virtual ~DCopyClass() {
		printf("Destruction in DCopyClass\n");
	}
	void GetDevKey() const {
		printf("dev_key=%d\n", dev_key);
	}
	DCopyClass & operator= (const DCopyClass &rhs) {
		if (this == &rhs) return *this;
		CopyClass::operator =(rhs);
		dev_key = rhs.dev_key;
	}
private:
	int dev_key;
};

void OutofMem()
{
	std::cerr << "OutofMem" << std::endl;
	std::abort();
}

// 名称覆盖，P158
class PBaseClass
{
public:
	PBaseClass() {
		printf("PBaseClass\n");
	}
	virtual void print() const {
		printf("PBaseClass print()\n");
	}
	void print(char* a) const {
		printf("PBaseClass print(double)\n");
	}
};
class PDeriveClass : public PBaseClass
{
public:
	using PBaseClass::print;
	void print(int x) {
		printf("PDeriveClass print()\n");
	}
};

class Ca
{
public:
	int getName() const {
		calName();
		return 0;
	}
private:
	virtual void calName() const = 0;
};
class Cb : public Ca
{
private:
	 virtual void calName() const {
		 printf("Cb::calName()\n");
	 }
};
class Cc : public Ca
{
};
#endif /* RULE_LIB_H_ */
