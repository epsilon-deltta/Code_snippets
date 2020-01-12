package challenge.three;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Stream;

public class DicTest {
	public static void main(String[] args) {
		Map<String, String> dic = new HashMap<>();

		dic.put("cat", "������");
		dic.put("head", "�밡����");
		dic.put("aunt", "������");
		dic.put("noodle", "����");
		dic.put("teacher", "��");
		dic.put("child", "���");

		dic.forEach((x, y) -> System.out.print(x + "=" + y + "  "));
		System.out.println();

		Collection<String> collection1 = dic.values();
		List<String> list1 = new ArrayList<>(collection1);
		Collections.shuffle(list1);
		list1.forEach(x -> System.out.print(x + "  "));
		System.out.println();

		Collection<String> collection2 = dic.keySet();
		collection2.forEach(x -> System.out.print(x + " "));
		System.out.println();

		Stream<String> stream = collection2.stream();
		stream.sorted().filter(x -> x.length() > 4).forEach(x -> System.out.print(x + " "));
	}
}