package challenge.two;

interface Controllable {
	default void repair(String type) {
		System.out.println(type + "를 수리한다.");
	}

	static void reset(String type) {
		System.out.println(type + "를 초기화한다.");
	}

	void power(String type, boolean onOff);
}

public class ControllableTest {
	public static void main(String[] args) {
		String who = "나는 ";
		class TV implements Controllable {
			public void power(String type, boolean onOff) {
				String verb = onOff == true ? "켠다." : "끝다.";
				System.out.println(who + type + " 전원을 " + verb);
			}
		}
		Controllable tv = new TV();

		tv.power("TV", true);
		tv.power("TV", false);
		tv.repair("TV");
		Controllable.reset("TV");
	}
}
