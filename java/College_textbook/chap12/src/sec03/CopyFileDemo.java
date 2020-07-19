package sec03;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class CopyFileDemo {
	public static void main(String[] args) {
		String input = "C:\\Temp\\org.txt";
		String output = "C:\\Temp\\dup.txt";

		try (FileReader fr = new FileReader(input); 
				FileWriter fw = new FileWriter(output)) {
			int c;

			while ((c = fr.read()) != -1)
				fw.write(c);
		} catch (IOException e) {
		}
	}
}