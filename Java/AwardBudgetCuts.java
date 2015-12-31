import java.util.Arrays;

/**
 *
 * The awards committee had planned to give n research grants this year, out of a its total yearly budget.
However, the budget was reduced to b dollars. The committee members has decided to affect the minimal number of highest grants, by applying a maximum cap c on all grants: every grant that was planned to be higher than c will now be c dollars.
Help the committee to choose the right value of c that would make the total sum of grants equal to the new budget.

Given an array of grants g and a new budget b, explain and code an efficient method to find the cap c.
Analyze the time and space complexity of your solution.
 * @author Sajjad (problem from Pramp)
 *
 * NOTE: Does not work if the cap c needs to be less than the lowest grant
 */
public class AwardBudgetCuts {
	public static int findCap(int[] g, int b) 
	{
		Arrays.sort(g);
		
		int[] partialSums = new int[g.length];
		int sum = 0;
		// partialSums stores sum of 0 - ith elements of g[] at index i
		for (int i=0; i<g.length; i++) {
			sum += g[i];
			partialSums[i] = sum;
		}
		if (sum <= b) {
			return g[g.length-1];  // no need to cap, got enough budget
		}
		int start = 0;
		int end = g.length - 1;
		
		while (start <= end) {
			int mid = start + (end - start)/2;
			int cappedSum = partialSums[mid] + g[mid] * (g.length - mid - 1); // try capping entries after mid to g[mid]
			if (cappedSum == b) {
				return g[mid];
			}
			if (cappedSum > b) {
				if (mid > 0) {
					int prevCappedSum = partialSums[mid-1] + g[mid-1] * (g.length - mid);
					if (prevCappedSum < b) {
						System.out.println("Found solution by capping at index "+mid);
						int c = (b - partialSums[mid-1]) / (g.length - mid);
						return c;
					} 
				}
				end = mid - 1;
			} else {
				start = mid + 1;
			}
		}
		return 0;
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int n = 10;
		int[] A = new int[6];
		for (int i=0; i<6; i++) {
			A[i] = n * (i+1);
//			A[i] = 10;
		}
		int c = findCap(A, 205);
		if (c != 55) {
			System.out.println("FAILED: Expected 55, Got "+c);
		} else {
			System.out.println("PASSED: Expected 55, Got "+c);
		}

	}

}
