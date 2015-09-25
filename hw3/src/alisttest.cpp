#include "../lib/alistint.h"
#include "gtest/gtest.h"

class AListIntTest : public testing::Test {
protected: 

	virtual void SetUp() {
		a.insert(0, 1);
		a.insert(1, 2);
		a.insert(2, 3);
		a.insert(3, 4);
		a.insert(4, 5);
	}


	AListInt a;


};

TEST_F(AListIntTest, sizeAndResize) {
	EXPECT_EQ(a.size(), 5); 
	for(int i = 5; i<165; ++i) {
		a.insert(i, i+1);
		EXPECT_EQ(a.size(), i+1);
	}
	AListInt b(165);
	AListInt c;
	EXPECT_EQ(c.size(), 0);
	EXPECT_EQ(b.size(), 0);
	for(int i=0; i<400; ++i) {
		b.insert(i, -(i+1));
		EXPECT_EQ(b.size(), i+1);
	}


}

TEST_F(AListIntTest, empty) {
	EXPECT_EQ(a.empty(), false);
	AListInt b;
	EXPECT_EQ(b.empty(), true);
	b.insert(0, 6);
	EXPECT_EQ(b.empty(), false);
	AListInt c(165);
	EXPECT_EQ(c.empty(), true);
}

TEST_F(AListIntTest, get) {
	// nominal case
	for(int i =0; i<5; ++i) {
		EXPECT_EQ(a.get(i), i+1);
	}

	// off-nominal cases
	EXPECT_EQ(a.get(1005), a.get(a.size()-1));
	EXPECT_EQ(a.get(-194), a.get(0));

	// calling on empty list, will not test behavior but do not want it to crash
	AListInt b;
	b.get(1000);
	b.get(-545);
	b.get(0);

}

TEST_F(AListIntTest, copyConstructor) {

	AListInt b(a);
	EXPECT_EQ(a.size(), b.size());
	for(int i = 0; i < b.size(); ++i) {
		EXPECT_EQ(a.get(i), b.get(i));
	}
	for(int i = 5; i<1000; ++i) {
		b.insert(i, -i);
	}
	EXPECT_EQ(b.size(), 1000);
	AListInt c(b);
	EXPECT_EQ(c.size(), b.size());
	for(int i =0; i <b.size(); ++i) {
		EXPECT_EQ(c.get(i), b.get(i));
	}
	// now change some values of b, make sure does not affect c
	b.set(29, 5);
	b.set(65, 6422);
	EXPECT_EQ(c.get(29), -29);
	EXPECT_EQ(c.get(65), -65);
	// call on empty list
	AListInt d(25);
	AListInt f(d);
	EXPECT_EQ(d.size(), f.size());
	EXPECT_EQ(d.size(), 0);

}

TEST_F(AListIntTest, operator_equals) {
	AListInt b;
	for(int i=0; i<400; ++i) {
		b.insert(i, -(i+1));
	}
	b = a;
	EXPECT_EQ(b.size(), 5);
	for(int i =0; i<5; ++i) {
		EXPECT_EQ(b.get(i), i+1);
	}
	b = b;
	EXPECT_EQ(b.size(), 5);
	for(int i =0; i<5; ++i) {
		EXPECT_EQ(b.get(i), i+1);
	}
	for(int i=5; i<600; ++i) {
		b.insert(i, i+200);
	}
	AListInt c;
	c = b;
	b.set(430, 0);
	EXPECT_EQ(c.size(), 600);
	for(int i=5; i<600; ++i) {
		EXPECT_EQ(c.get(i), i+200);
	}

	AListInt d;
	AListInt e;
	e = d;
	EXPECT_EQ(e.empty(), true);
	e = c;
	EXPECT_EQ(e.empty(), false);

}

TEST_F(AListIntTest, insert) {
	// nominal cases
	a.insert(2, 8);
	EXPECT_EQ(a.size(), 6);
	EXPECT_EQ(a.get(1), 2);
	EXPECT_EQ(a.get(2), 8);
	EXPECT_EQ(a.get(3), 3);
	EXPECT_EQ(a.get(5), 5);
	a.insert(0, 8);
	EXPECT_EQ(a.size(), 7);
	EXPECT_EQ(a.get(0), 8);
	EXPECT_EQ(a.get(1), 1);
	EXPECT_EQ(a.get(6), 5);
	a.insert(7, 9);
	EXPECT_EQ(a.get(7), 9);
	EXPECT_EQ(a.get(0), 8);

	// ofd nominal cases
	a.insert(-1, 9);
	EXPECT_EQ(a.size(), 8);
	a.insert(9, 103);
	EXPECT_EQ(a.size(), 8);
}

TEST_F(AListIntTest, set) {
	a.set(1, 7);
	EXPECT_EQ(a.get(1), 7);
	EXPECT_EQ(a.get(0), 1);
	EXPECT_EQ(a.get(2), 3);
	EXPECT_EQ(a.size(), 5);

	// make sure program does not crash
	a.set(-1, 90);
	a.set(5, 8);
}

TEST_F(AListIntTest, remove) {
	for(int i = 5; i < 15; i++) {
		a.insert(i, i+1);
	}
	a.remove(8);
	EXPECT_EQ(a.size(), 14);
	EXPECT_EQ(a.get(7), 8);
	EXPECT_EQ(a.get(8), 10);
	EXPECT_EQ(a.get(12), 14);
	a.remove(0);
	EXPECT_EQ(a.size(), 13);
	EXPECT_EQ(a.get(0), 2);
	EXPECT_EQ(a.get(12), 15);
	a.remove(12);
	EXPECT_EQ(a.size(), 12);
	EXPECT_EQ(a.get(11), 14);

	a.remove(-5);
	a.remove(12);
	EXPECT_EQ(a.size(), 12);

}

TEST_F(AListIntTest, operator_add) {
	AListInt b(a);
	b.insert(5, 6);
	AListInt m; 
	m.insert(0, 1);
	m = a + b;
	EXPECT_EQ(m.size(), 11);
	for(int i=0; i<5; i++) {
		EXPECT_EQ(m[i], a[i]);
	}
	for(int i =5; i < 11; i++) {
		EXPECT_EQ(m[i], b[i-5]);
	}

	a = a + a;
	EXPECT_EQ(a.size(), 10);
	for(int i=0; i<5; i++) {
		EXPECT_EQ(a[i], i+1);
	}
	for(int i=5; i<10; i++) {
		EXPECT_EQ(a[i], i-4);
	}

	AListInt c;
	AListInt d(100);
	AListInt e; 
	e = c + d;
	EXPECT_EQ(e.size(), 0);

	e = e + m;
	EXPECT_EQ(e.size(), 11);
	for(int i=0; i<5; i++) {
		EXPECT_EQ(e[i], i+1);
	}
	for(int i =5; i < 11; i++) {
		EXPECT_EQ(m[i], i-4);
	}

}

TEST_F(AListIntTest, operator_accessor) {
	for(int i =-5; i<25; i++) {
		a[i] = a.get(i);
	}
} 
