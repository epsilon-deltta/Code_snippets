package challenge.two;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class DicTest {
	public static void main(String[] args) {
		Map<String, String> dic = new HashMap<>();

		dic.put("cat", "꼬네이");
		dic.put("head", "대가빠리");
		dic.put("aunt", "아지매");
		dic.put("noodle", "국시");
		dic.put("teacher", "쌤");
		dic.put("child", "얼라");
		
		dic.forEach((x, y) -> System.out.print(x + "=" + y + "  "));
		System.out.println();

		Collection<String> collection1 = dic.values();
		List<String> list = new ArrayList<>(collection1);	// Collection 타입을 List 타입으로 변환
		Collections.shuffle(list);							// List 객체의 원소 섞기
		list.forEach(x -> System.out.print(x + "  "));
	}
}