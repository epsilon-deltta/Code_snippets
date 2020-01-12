package challenge.one;

import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Date;

public class DateServer {
	public static void main(String[] args) {
		try (ServerSocket ss = new ServerSocket(9000);
				Socket connection = ss.accept();
				PrintWriter out = new PrintWriter(connection.getOutputStream(), true);) {
			out.println("¼­¹ö > " + new Date().toString());
		} catch (Exception e) {
		}
	}
}