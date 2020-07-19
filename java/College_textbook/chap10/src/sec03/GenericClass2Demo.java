package sec03;

import sec03.generic.Cup;

public class GenericClass2Demo {
	public static void main(String[] args) {
		Cup<Boricha> c = new Cup<Boricha>();

		c.setBeverage(new Boricha());

		// c.setBeverage(new Beer());

		// Beer b = c.getBeverage();

		Boricha b = c.getBeverage();
	}
}