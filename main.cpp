#include"lru.h"

int main() {
	LRU test;
	for (int i = 0; i < 10; i++) {
		test.put(i);
	}
	test.show();
	test.call(5);
	test.show();
	test.call(7);
	test.show();
	test.displace();
	test.show();
	test.displace();
	test.show();
	return 0;
}