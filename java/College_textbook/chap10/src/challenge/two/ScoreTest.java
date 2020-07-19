package challenge.two;

public class ScoreTest {
	static <T extends Comparable> T findBest(T[] a) {
		T best = a[0];

		for (int i = 0; i < a.length; i++)
			if (best.compareTo(a[i]) < 0)
				best = a[i];
		return best;
	}

	public static void main(String[] args) {
		EnglishScore[] ea = { new EnglishScore("±è»ñ°«", 77), new EnglishScore("Àå¿µ½Ç", 88), new EnglishScore("È«±æµ¿", 99) };
		MathScore[] ma = { new MathScore("±è»ñ°«", 80), new MathScore("Àå¿µ½Ç", 98), new MathScore("È«±æµ¿", 70) };

		System.out.println("¿µ¾î ÃÖ°í Á¡¼ö : " + findBest(ea));
		System.out.println("¼öÇÐ ÃÖ°í Á¡¼ö : " + findBest(ma));
	}
}
