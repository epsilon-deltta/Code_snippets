package sec02;

public class Thread4Demo {
	public static void main(String[] args) {
		Thread t = new WorkerThread();
		t.start();

		for (int i = 0; i < 5; i++) {
			System.out.print("¾È³ç. ");
			try {
				Thread.sleep(500);
			} catch (InterruptedException e) {
			}
		}
	}
}

class WorkerThread extends Thread {
	public void run() {
		for (int i = 0; i < 5; i++) {
			System.out.print("Àß°¡. ");
			try {
				Thread.sleep(500);
			} catch (InterruptedException e) {
			}
		}
	}
}