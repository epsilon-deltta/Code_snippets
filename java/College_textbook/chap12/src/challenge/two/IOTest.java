package challenge.two;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class IOTest {
	public static void main(String[] args) {
		String fileName = "D:\\temp\\file.txt";
		String line = null;

		try {
			FileReader fr = new FileReader(fileName);
			BufferedReader br = new BufferedReader(fr);

			while ((line = br.readLine()) != null)
				System.out.println(line);

			fr.close();
			br.close();
		} catch (FileNotFoundException ex) {
			System.out.println(fileName + " 파일을 열 수 없습니다.");
		} catch (IOException ex) {
			System.out.println(fileName + " 파일을 읽을 수가 없습니다.");
		}
	}
}
