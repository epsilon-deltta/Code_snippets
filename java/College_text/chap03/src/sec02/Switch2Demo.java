package sec02;

public class Switch2Demo {
	public static void main(String[] args) {
		String english = "odd";

		switch (english) {
		case "odd":
			System.out.println("Ȧ���Դϴ�.");
			break;
		case "even":
			System.out.println("¦���Դϴ�.");
			break;
		default:
			System.out.println("¦���� Ȧ���� �ƴմϴ�.");
		}
	}
}