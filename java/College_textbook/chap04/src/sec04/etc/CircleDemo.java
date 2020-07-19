package sec04.etc;

public class CircleDemo {
	static double radius;

	static double findArea() {
		return 3.14 * radius * radius;
	}

	static void show(double x, double y) {
		System.out.printf("������ = %.1f, ���� = %.1f\n", x, y);
	}

	public static void main(String[] args) {
		radius = 10.0;

		double area = findArea();

		show(radius, area);
	}
}