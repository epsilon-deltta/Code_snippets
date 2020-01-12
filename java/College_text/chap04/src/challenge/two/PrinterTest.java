package challenge.two;

class Printer {
	private int numOfPapers = 0;

	public Printer(int numOfPapers) {
		this.numOfPapers = numOfPapers;
	}

	void feed(int amount) {
		numOfPapers += amount;
	}

	void print(int amount) {
		if (numOfPapers == 0)
			System.out.println("용지가 없습니다.");
		else if (numOfPapers < amount) {
			System.out.printf("모두 출력하려면 용지가 %d매 부족합니다. ", amount - numOfPapers);
			System.out.println(numOfPapers + "장만 출력합니다.");
			numOfPapers = 0;
		} else {
			numOfPapers -= amount;
			System.out.print(amount + "장 출력했습니다. ");
			System.out.println("현재 " + numOfPapers + "장 남아있습니다.");
		}
	}
}

public class PrinterTest {
	public static void main(String[] args) {
		Printer p = new Printer(10);
		p.print(2);
		p.print(20);
		p.print(10);
	}
}