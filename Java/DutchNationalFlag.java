import java.util.*;
import java.math.*;

class DutchNationalFlag {

  public static enum Color { RED, WHITE, BLUE }
  private static void swap (List<Color> A, int first, int second) {
      Color temp = A.get(first);
      A.set(first, A.get(second));
      A.set(second, temp);
  }
  public static void dutchFlagPartition(int pivotIndex, List<Color> A) {
      int lo = 0;
      int hi = A.size() - 1;
      int i = 0;
      Color pivot = A.get(pivotIndex);
      
      while (i <= hi)
      {
          if (A.get(i).compareTo(pivot) < 0){
              swap(A, i, lo);
              lo++;i++;
          } else if (A.get(i).compareTo(pivot) > 0) {
              swap(A, i, hi);
              hi--;
          } else {
              i++;
          }
      }
    }
  public static void main(String[] args) {
	  ArrayList<Color> A = new ArrayList<Color>();
	  
	  A.add(Color.WHITE);
      A.add(Color.WHITE);
	  A.add(Color.WHITE);
	  A.add(Color.RED);
	  A.add(Color.BLUE);
	  A.add(Color.WHITE);
	  A.add(Color.BLUE);
	  A.add(Color.WHITE);
	  A.add(Color.RED);
	  A.add(Color.RED);
	  A.add(Color.WHITE);
	  A.add(Color.RED);
	  A.add(Color.BLUE);
	  A.add(Color.WHITE);
	  
	  System.out.println("Before:                      " + A);
	  Color pivot = A.get(3);
	  dutchFlagPartition(3, A);
	  System.out.println("After partition around "+pivot+ " : " + A);
	  pivot = A.get(6);
	  dutchFlagPartition(6, A);
	  System.out.println("After partition around "+pivot+ " : " + A);


  }
}
