package challenge.three;

public class ThreadTest {
	public static void main(String args[]) {
		int alphabet = 'a';
		Thread worker = new Thread(new Runnable() {
			public void run() {
				try {
					for (int i = 0; i < 5; i++) {
						System.out.println("작업 스레드 : " + i);
						Thread.sleep(1000);
					}
				} catch (InterruptedException e) {
				}
			}
		});
		worker.start();
		try {
			while (worker.isAlive()) {
				System.out.println("메인 스레드 : " + (char) alphabet++);
				Thread.sleep(1500);
			}
		} catch (InterruptedException e) {
		}
	}
}