package challenge.one;

public class ScoreTest {
	static EnglishScore findBest(EnglishScore[] a) {
		EnglishScore best = a[0];

		for (int i = 0; i < a.length; i++)
			if (best.compareTo(a[i]) < 0)
				best = a[i];
		return best;
	}

	public static void main(String[] args) {
		EnglishScore[] ea = { new EnglishScore("±è»ñ°«", 77), new EnglishScore("Àå¿µ½Ç", 88), new EnglishScore("È«±æµ¿", 99) };

		System.out.println("¿µ¾î ÃÖ°í Á¡¼ö: " + findBest(ea));
	}
}
