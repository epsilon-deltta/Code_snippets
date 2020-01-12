package sec02;

public class Switch2Demo {
	public static void main(String[] args) {
		String english = "odd";

		switch (english) {
		case "odd":
			System.out.println("È¦¼öÀÔ´Ï´Ù.");
			break;
		case "even":
			System.out.println("Â¦¼öÀÔ´Ï´Ù.");
			break;
		default:
			System.out.println("Â¦¼öµµ È¦¼öµµ ¾Æ´Õ´Ï´Ù.");
		}
	}
}