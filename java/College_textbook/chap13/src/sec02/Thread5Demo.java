package sec02;

public class Thread5Demo {
	public static void main(String[] args) {
		new Thread() {
			public void run() {
				for (int i = 0; i < 5; i++) {
					System.out.print("Àß°¡. ");
					try {
						Thread.sleep(500);
					} catch (InterruptedException e) {
					}
				}
			}
		}.start();

		for (int i = 0; i < 5; i++) {
			System.out.print("¾È³ç. ");
			try {
				Thread.sleep(500);
			} catch (InterruptedException e) {
			}
		}
	}
}