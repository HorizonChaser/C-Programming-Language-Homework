public class wifi {
    public static void main(String[] args) {
        final char[] a = { 'T', 'h', 'i', 's', 'I', 's', 'T', 'h', 'e', 'F', 'l', 'a', 'g', 'H', 'o', 'm', 'e' };
        final char[] b = { 'p', 'v', 'k', 'q', '{', 'm', '1', '6', '4', '6', '7', '5', '2', '6', '2', '0', '3', '3',
                'l', '4', 'm', '4', '9', 'l', 'n', 'p', '7', 'p', '9', 'm', 'n', 'k', '2', '8', 'k', '7', '5', '}' };
        char[] x = new char[17];
        char[] y = new char[38];
        for (int i = 0; i < 17; i++) {
            if ((a[i] < 'I' && a[i] >= 'A') || (a[i] < 'i' && a[i] >= 'a')) {
                x[i] = (char) (a[i] + 18);
            } else if ((a[i] < 'A' || a[i] > 'Z') && (a[i] < 'a' || a[i] > 'z')) {
                x[i] = a[i];
            } else {
                x[i] = (char) (a[i] - '\b');
            }
        }

        System.out.print(String.valueOf(x));

        for (int i2 = 0; i2 < 38; i2++) {
            if ((b[i2] < 'A' || b[i2] > 'Z') && (b[i2] < 'a' || b[i2] > 'z')) {
                y[i2] = b[i2];
            } else {
                y[i2] = (char) (b[i2] + 16);
                if ((y[i2] > 'Z' && y[i2] < 'a') || y[i2] >= 'z') {
                    y[i2] = (char) (y[i2] - 26);
                }
            }
        }
        System.out.print(String.valueOf(y));
    }
}