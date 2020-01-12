package challenge.one;

interface Controllable {
	default void repair() {
		System.out.println("���񽺼��Ϳ��� �����ؾ� �Ѵ�.");
	}

	static void reset() {
		System.out.println("���� �ʱ�ȭ�� �� �ִ�.");
	}

	void power(boolean onOff);
}

class TV implements Controllable {
	String who;

	public TV(String who) {
		this.who = who;
	}

	public void power(boolean onOff) {
		String verb = onOff == true ? "�Ҵ�." : "����.";
		System.out.println(who + " TV ������ " + verb);
	}
}

public class ControllableTest {
	public static void main(String[] args) {
		Controllable tv = new TV("�浿�̴�");

		tv.power(true);
		tv.power(false);
		tv.repair();
		Controllable.reset();
	}
}
