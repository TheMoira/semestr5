public class Student
{
    String imie;
    String nazwisko;
    int wiek;

    public Student() {}

    public Student(String n, String s, int age) 
    {
        imie = n;
        nazwisko = s;
        wiek = age;
    }

    public void setImie(String name)
    {
        imie = name;
    }

    public void setNazwisko(String n)
    {
        nazwisko = n;
    }

    public void setWiek(int n)
    {
        wiek = n;
    }

    public String getImie()
    {
        return imie;
    }

    public String getNazwisko()
    {
        return nazwisko;
    }

    public int getWiek()
    {
        return wiek;
    }

}