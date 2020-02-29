import java.io.IOException;
import java.io.File;
import java.nio.charset.Charset;
import java.nio.file.Paths;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.util.ArrayList;
// import java.io.*;


class My_NoFileException extends IOException {}
class My_NoFileException2 extends IOException {}
class My_ZeroException extends ArithmeticException {}
class My_NoContentException extends IOException {}

public class Srednia
{
    private int len;
    private Path fin;
    private Path fout;
    private ArrayList<double> arr = new ArrayList<double>();
    public double wynik;



    public void readLength(int len)
    {
        try
        {
            if(len == 0)
            {
                throw new My_NoFileException();
            }
            else if(len == 1)
            {
                throw new My_NoFileException2();
            }

            this.len = len;
        }
        catch(My_NoFileException e1)
        {
            System.out.println("Nie mozna otworzyc pliku wejsciowego");
        }
        catch(My_NoFileException2 e2)
        {
            System.out.println("Nie mozna otworzyc pliku wejsciowego");    
        }

    }

    public void readFileIn(Path rfile)
    {
        try
        {
            byte[] fileArray;
            fileArray = Files.readAllBytes(rfile);
            if(fileArray.length() == 0)
            {
                throw new My_NoContentException();
            }
        }
        catch(My_NoContentException e3)
        {
            System.out.println("Plik wejściowy nie moze byc pusty!");
        }

        fin = rfile;

        Charset charset = Charset.forName("US-ASCII");

        try (BufferedReader reader = Files.newBufferedReader(fin, charset)) {
            String line = null;
            while ((line = reader.readLine()) != null) 
            {
                arr.add(Double.parseDouble(line));
            }
        } 
        catch (My_NoContentException e4) 
        {
            System.out.println("Plik wejściowy nie moze byc pusty!");
        }

    }

    public void countM()
    {
        double sum = 0;
        for(int i=0; i< arr.size(); i++)
        {
            sum += arr.get(i);
        }

        wynik = sum/arr.size();
    }

    public void writeFileOut(Path ofile)
    {

        Charset charset = Charset.forName("US-ASCII");

        try (BufferedWriter writer = Files.newBufferedWriter(ofile, charset)) 
        {
            writer.write(arr, 0, data.size());
        } 
        catch (IOException e5) 
        {
            System.out.println("Problem z plikiem wyjsciowym");
        }
    }
}