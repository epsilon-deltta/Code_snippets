package Convinience;

public class AttachQuotation {
	String str;

	public AttachQuotation(String str) {
		this.str = str;
	}

	String getAttachedStr() {
		String [] array = str.split("\n");
		String sum="";
		for (int i = 0; i < array.length; i++) {
			array[i]=array[i].replaceAll("[\"]", "\\\\\"");
			array[i]="\""+array[i]+"\""+"\n";
			sum+=array[i];
		}
		return sum;
	}
	public static void main(String[] args) {
		AttachQuotation a =new AttachQuotation("as\"df'a\"a'sf");
		System.out.println(a.getAttachedStr());
		System.out.println("\\\\");
	}
}
