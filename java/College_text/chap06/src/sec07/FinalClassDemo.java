package sec07;

class Good {
}

class Better extends Good {
}

final class Best extends Better {
}
// class NumberOne extends Best {}

public class FinalClassDemo {
	public static void main(String[] args) {
		// new NumberOne();
		new Best();
	}
}