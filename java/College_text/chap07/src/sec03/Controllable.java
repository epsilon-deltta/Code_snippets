package sec03;

public interface Controllable {
	default void repair() {
		System.out.println("장비를 수리한다.");
	}

	static void reset() {
		System.out.println("장비를 초기화한다.");
	}

	void turnOn();
	void turnOff();
}