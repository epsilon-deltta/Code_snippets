package challenge.two;

interface Controllable {
	default void repair(String type) {
		System.out.println(type + "�� �����Ѵ�.");
	}

	static void reset(String type) {
		System.out.println(type + "�� �ʱ�ȭ�Ѵ�.");
	}

	void power(String type, boolean onOff);
}

public class ControllableTest {
	public static void main(String[] args) {
		String who = "���� ";
		class TV implements Controllable {
			public void power(String type, boolean onOff) {
				String verb = onOff == true ? "�Ҵ�." : "����.";
				System.out.println(who + type + " ������ " + verb);
			}
		}
		Controllable tv = new TV();

		tv.power("TV", true);
		tv.power("TV", false);
		tv.repair("TV");
		Controllable.reset("TV");
	}
}
