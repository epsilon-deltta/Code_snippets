package challenge.one;

class Car {
	private String model;

	public Car(String model) {
		this.model = model;
	}

	@Override
	public String toString() {
		return "[" + model + "]";
	}
}

public class CarTest {
	public static void main(String[] args) {
		Car myCar = new Car("그랜저");
		Car yourCar = new Car("그랜저");

		if (myCar.equals(yourCar))
			System.out.printf("자동차 모델이 둘다 %s로 동일하다.\n", myCar);
		else
			System.out.printf("내 자동차는 %s, 너 자동차는 %s로 모델이 다르다.\n", myCar, yourCar);
	}
}