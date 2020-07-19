package sec03;

import sec03.generic.Cup;

public class GenericClass3Demo {
	public static void main(String[] args) {
		Cup c1 = new Cup();

		c1.setBeverage(new Beer());

		// Beer beer = c1.getBeverage();
		Beer beer = (Beer) c1.getBeverage();
	}
}