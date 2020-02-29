import static java.nio.file.StandardOpenOption.*;
import java.nio.file.*;
import java.io.*;

public class lab8
{
    public static void main(String[] args)
    {
        Srednia test = new Srednia();

        test.readLength(args.length());

        test.readFileIn(args[0]);

        test.countM();

        test.writeFileOut(args[1]);

    }
}