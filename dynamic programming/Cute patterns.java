import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.Scanner;

public class Main {
    static int m, MOD;
    static BigInteger n;

    public static int[][] mul(int[][] a, int[][] b, int n, int m, int p) {
        int[][] res = new int[n][m];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int sum = 0;
                for (int k = 0; k < p; ++k) {
                    sum = (sum + (a[i][k] * b[k][j]) % MOD) % MOD;
                }
                res[i][j] = sum;
            }
        }
        return res;
    }

    public static int[][] pow(int[][] a, BigInteger p, int n) {
        if (p.compareTo(BigInteger.ONE) == 0) {
            return a;
        }
        if (p.mod(BigInteger.valueOf(2)).equals(BigInteger.ZERO)) {
            int[][] res = pow(a, p.divide(BigInteger.valueOf(2)), n);
            return mul(res, res, n, n, n);
        }
        return mul(a, pow(a, p.subtract(BigInteger.ONE), n), n, n, n);
    }

    public static int can(int mask1, int mask2) {
        for (int i = 0; i + 1 < m; ++i) {
            int sum = 0;
            if ((mask1 & (1 << i)) == 0) {
                sum++;
            }
            if ((mask1 & (1 << (i + 1))) == 0) {
                sum++;
            }
            if ((mask2 & (1 << i)) == 0) {
                sum++;
            }
            if ((mask2 & (1 << (i + 1))) == 0) {
                sum++;
            }
            if (sum == 0 || sum == 4) {
                return 0;
            }
        }
        return 1;
    }

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);
        n = in.nextBigInteger();
        m = in.nextInt();
        MOD = in.nextInt();
        if (n.compareTo(BigInteger.ONE) == 0) {
            out.print((1 << m) % MOD);
            out.flush();
            System.exit(0);
        }
        int mm = (1 << m);
        int[][] a = new int[mm][mm];
        for (int mask1 = 0; mask1 < mm; ++mask1) {
            for (int mask2 = 0; mask2 < mm; ++mask2) {
                a[mask1][mask2] = can(mask1, mask2);
            }
        }
        a = pow(a, n.subtract(BigInteger.ONE), mm);
        int[][] b = new int[mm][1];
        for (int i = 0; i < mm; ++i) {
            b[i][0] = 1;
        }
        a = mul(a, b, mm, 1, mm);
        int ans = 0;
        for (int mask = 0; mask < mm; ++mask) {
            ans = (ans + a[mask][0]) % MOD;
        }
        out.print(ans);
        out.flush();
    }
}
