package sec03;

interface Showable {
	void show(String s);
}

interface Pickable {
	char pick(String s1, int i);
}

interface Operable {
	int operator(int x, int y);
}

interface Newable {
	String getString(String s);
}

interface IntArray {
	int[] getArray(int size);
}

class Utils {
	int add(int a, int b) {
		return a + b;
	}
}