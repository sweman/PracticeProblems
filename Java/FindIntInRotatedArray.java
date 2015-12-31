/**
 * Shifted Array Search
 *
 * 1. Find a given number num in a sorted array arr:
 * arr = [2, 4, 5, 9, 12, 17] 
 *
 * 2. If the sorted array arr is shifted left by an unknown offset and you don't have a pre-shifted copy of it, how would you modify your method to find a number in the shifted array?
 * shiftArr = [9, 12, 17, 2, 4, 5]
 *
 * Explain and code an efficient solution and analyze its runtime complexity
 * if num doesn't exist in the array, return -1
 * @author 
 *
 */


public class FindIntInRotatedArray {

	public static int findInRotatedArray(int[] A, int target) {
		int start = 0;
		int end = A.length - 1;
		int pivot = 0;
		// first find the start/end of the two sorted subarrays
		if (A[start] > A[end]) { // this is a rotated array
			while (start <= end) {
				int mid = start + (end - start)/2;
				if (mid == 0 || A[mid] < A[mid-1]) {
					pivot = mid;
					break;
				}
				if (A[mid] < A[start]) {
					end = mid - 1;
				} else {
					start = mid + 1;
				} 
			}
		}
		System.out.println("\npivot at "+pivot);
		// now do binary search on the subarray that might have the target
		int res = -1;
		if (target < A[0]) {
			start = pivot;
			end = A.length - 1;
		} else {
			start = 0;
			end = pivot - 1;
		}
		// regular binary search
		while (start <= end) {
			int mid = start + (end - start)/2;
			if (target < A[mid]) {
				end = mid - 1;
			} else if (target > A[mid]){
				start = mid + 1;
			} else {
				res = mid;
				break;
			}
		}
		return res;
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[] A = new int[7];
		int rotateBy = 3;
		int val = 1;
		for (int i = rotateBy - 1; i < A.length; i++) {
			A[i] = val++;
		}
		for (int i =0; i < rotateBy-1; i++) {
			A[i] = val++;
		}
		for (int n : A) {
			System.out.print(n+" ");
		}
		
		int target = 5;
		System.out.println("\nFound "+target+" at index "+findInRotatedArray(A, target));
	
	}

}
