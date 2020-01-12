package sec02;

public class Anonymous1Demo {
	Bird e = new Bird() {
		public void move() {
			System.out.println("독수리가 난다~~~.");
		}

		void sound() {
			System.out.println("휘익~~~.");
		}
	};

	public static void main(String[] args) {
		Anonymous1Demo a = new Anonymous1Demo();
		a.e.move();
		// a.e.sound();
	}
}