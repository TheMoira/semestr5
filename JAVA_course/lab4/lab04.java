public class lab04
{
    public static void main(String[] args)
    {
        int x_size = Integer.parseInt(args[0]);
        int y_size = Integer.parseInt(args[1]);
        int steps = Integer.parseInt(args[2]);
        int preset = Integer.parseInt(args[3]);

        gra_w_zycie.play(y_size,x_size,steps,preset);
    }
}

