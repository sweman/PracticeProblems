import java.util.ArrayList;
import java.util.List;

public class MakeChange {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		List<Integer> den = new ArrayList<>();
		den.add(100);
		den.add(25);
		den.add(10);
		den.add(5);
		den.add(1);
		List<Integer> res = new ArrayList<>(den.size());
		for(int i = 0; i < den.size(); i++) {
			res.add(0);
		}

		int change = 172;
		makeChange(res, den, change);
	}
	public static void makeChange(List<Integer> res, List<Integer> den, int change) {
       
		// if it is a solution then process the solution
		if (change == 0) {
			for (int i = 0; i < den.size(); i++) {
				System.out.println(den.get(i) + ": " + res.get(i) + " coins");
			}
			return;
		}
		 		
		// get all candidates
		int i = 0;
		while (i < den.size() && change < den.get(i)) i++;
		// for each candidate ...
		
		//    add candidate to partial solution
		while (i < den.size()) {
			// add candidate to the partial solution
			int newcnt = res.get(i) + 1;
			res.set(i, newcnt);
			change -= den.get(i);
			makeChange(res, den, change);
			// remove candidate from solution
			res.set(i, newcnt - 1);
			change += den.get(i);
			i++;
		}
		
	}

}
