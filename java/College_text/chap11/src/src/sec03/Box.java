package sec03;

public class Box implements Comparable<Box> {
	int number;

	public Box(int number) {
		this.number = number;
	}

	public String toString() {
		return "Box [number=" + number + "]";
	}

	public int compareTo(Box o) {
		return number - o.number;
	}
}