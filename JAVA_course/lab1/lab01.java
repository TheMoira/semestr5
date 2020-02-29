public class lab01
{
    public static void main(String args[])
    {
        draw_line(28,65,28,84);
    draw_line(28,84,34,83);
    draw_line(34,83,38,79);
    draw_line(38,79,37,76);
    draw_line(37,76,34,73);
    draw_line(28,72,37,76);
    draw_line(58,25,53,23);
    draw_line(53,23,47,23);
    draw_line(47,23,44,25);
    draw_line(74,65,63,65);
    draw_line(63,65,73,74);
    draw_line(73,74,73,79);
    draw_line(73,79,70,82);
    draw_line(70,82,66,82);
    draw_line(66,82,63,80);
    draw_circle(50,74,9);
    draw_circle(50,29,14);
    draw_circle(55,34,2);
    draw_circle(46,34,2);    
    }

    public static double line_len(int x1, int y1, int x2, int y2)
    {
        return Math.sqrt( Math.pow(x1 - x2,2) + Math.pow(y1 - y2, 2) ); 
    }

    public static double circle_len(int r)
    {
        return 2 * Math.PI * r;
    }

    public static void draw_line(int x1, int y1, int x2, int y2)
    {
        double d_len = line_len(x1,y1,x2,y2);
        int len = (int)d_len;

        double xdiff = Math.sqrt(Math.pow(x2 - x1,2))/len;
        double ydiff = Math.sqrt(Math.pow(y2 - y1,2))/len;

        for(int i=0; i<len; i ++)
        {
            double xi = (double)x1 + i*xdiff;
            double yi = (double)y1 + i*ydiff;
            System.out.println( xi + " " + yi);
        }
        
    }

    public static void draw_circle(int x0, int y0, int r)
    {
        double d_len = circle_len(r);
        int len = (int)d_len;

        
        for(int i=0; i<len; i ++)
        {
            double alfa = i * 2 * Math.PI/len;
            System.out.println((double)x0 + Math.cos(alfa)*r + " " + (double)y0 + Math.sin(alfa)*r);
        }



    }

}


