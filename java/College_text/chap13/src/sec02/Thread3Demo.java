package sec02;

public class Thread3Demo {
	public static void main(String[] args) {
		Runnable task = () -> {
			for (int i = 0; i < 5; i++) {
				System.out.print("Àß°¡. ");
				try {
					Thread.sleep(500);
				} catch (InterruptedException e) {
				}
			}
		};
		new Thread(task).start();

		for (int i = 0; i < 5; i++) {
			System.out.print("¾È³ç. ");
			try {
				Thread.sleep(500);
			} catch (InterruptedException e) {
			}
		}
	}
}