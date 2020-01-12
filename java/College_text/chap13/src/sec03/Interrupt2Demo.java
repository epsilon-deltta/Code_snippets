package sec03;

public class Interrupt2Demo {
	public static void main(String[] args) {
		Runnable task = () -> {
			while (!Thread.currentThread().isInterrupted()) {
				System.out.println("실행 중...");
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