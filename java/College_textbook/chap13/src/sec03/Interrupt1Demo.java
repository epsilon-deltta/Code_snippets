package sec03;

public class Interrupt1Demo {
	public static void main(String[] args) {
		Runnable task = () -> {
			try {
				while (true) {
					System.out.println("실행 중...");
					Thread.sleep(1);
				}
			} catch (InterruptedException e) {
				// 인터럽트 처리 코드
			}
			System.out.println("정상 종료");
		};

		Thread t = new Thread(task);
		t.start();

		try {
			Thread.sleep(2);
		} catch (InterruptedException e) {
		}
		t.interrupt();
	}
}