package sec03;

import sec03.object.Cup;

public class GenericClass1Demo {
	public static void main(String[] args) {
		Cup c = new Cup();

		c.setBeverage(new Boricha());

		c.setBeverage(new Beer());

		Beer b1 = (Beer) c.getBeverage();

		Boricha b2 = (Boricha) c.getBeverage();
	}
}