import java.util.Scanner;
import java.util.ArrayList;

/**
 * Array of Array Products


Given an array of integers arr, write a function that returns another array at the same length where the value at each index i is the product of all array values except arr[i].

Solve without using division and analyze the runtime and space complexity

Example: given the array [2, 7, 3, 4]
your function would return: [84, 24, 56, 42] (by calculating: [7*3*4, 2*3*4, 2*7*4, 2*7*3])

 * @author Sajjad
 *
 */

public class ProductArray {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("Enter number of elements in the array:  " );
		Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        
		System.out.println("Enter array elements separated by spaces:  " );
		ArrayList<Integer> AList = new ArrayList<>();
		for(int i = 0; i < N; i++) {
			AList.add(sc.nextInt());
		}
		sc.close();
		
		int[] inArray = new int[AList.size()] ;
		int[] outArray = new int[AList.size()];
		
		// convert to int array ...
		for (int i = 0; i < inArray.length; i++) {
			inArray[i] = AList.get(i);
		}
		
		getArrayOfProducts(inArray, outArray, 0, 1);
		
		// print input and output arrays
		System.out.print("In: ");
		for(int n : inArray) {
			System.out.print(n + " ");
		}
		System.out.println("");
		
		System.out.print("Out: ");
		for(int n : outArray) {
			System.out.print(n + " ");
		}
		System.out.println("");	
	}
	// Main idea: at each recursion level (index == i), the product of the first i-1
	// integers is passed in as the fwdProduct parameter. Computes (recursively) the product 
	// of i+1 - n-1 integers and writes the result to outArray at index == i. Returns the revProduct, 
	// i.e., the product of i - n-1 integers.
	public static int getArrayOfProducts(int[] inArray, int[] outArray, int index, int fwdProduct)
	{
		int revProduct = 1;
		if (index < inArray.length) {
			revProduct = getArrayOfProducts(inArray, outArray, index+1, fwdProduct*inArray[index]);
			outArray[index] = fwdProduct * revProduct;
			revProduct *= inArray[index];
		}
		return revProduct;
	}

}
