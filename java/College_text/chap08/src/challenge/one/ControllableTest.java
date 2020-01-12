package challenge.one;

interface Controllable {
	default void repair() {
		System.out.println("서비스센터에서 수리해야 한다.");
	}

	static void reset() {
		System.out.println("내가 초기화할 수 있다.");
	}

	void power(boolean onOff);
}

class TV implements Controllable {
	String who;

	public TV(String who) {
		this.who = who;
	}

	public void power(boolean onOff) {
		String verb = onOff == true ? "켠다." : "끈다.";
		System.out.println(who + " TV 전원을 " + verb);
	}
}

public class ControllableTest {
	public static void main(String[] args) {
		Controllable tv = new TV("길동이는");

		tv.power(true);
		tv.power(false);
		tv.repair();
		Controllable.reset();
	}
}
