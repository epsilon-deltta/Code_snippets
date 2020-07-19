package challenge.two;

public class EnglishScore implements Comparable<EnglishScore> {
	String name;
	int score;

	public EnglishScore(String name, int score) {
		this.name = name;
		this.score = score;
	}

	@Override
	public int compareTo(EnglishScore e) {
		if (this.score > e.score)
			return 1;
		else if (this.score == e.score)
			return 0;
		else
			return -1;
	}

	@Override
	public String toString() {
		return name + ", " + score;
	}
}