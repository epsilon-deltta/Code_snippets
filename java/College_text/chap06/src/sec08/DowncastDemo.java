package sec08;

public class DowncastDemo {
	public static void main(String[] args) {
		Student s1 = new Student();
		Person p = s1;
		Student s2 = (Student) p;
	}
}
