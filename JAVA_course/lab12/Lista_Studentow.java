import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;


public class Lista_Studentow
{
    ArrayList<Student> lista = new ArrayList<Student>();

    public Lista_Studentow() {}

    public void add(Student stud)
    {
        lista.add(stud);
    }

    public void add(String n, String s, int age)
    {
        Student stud = new Student(n,s,age);
        lista.add(stud);
    }

    public void wypisz_wszystkich()
    {
        for(int i=0; i<lista.size(); i++)
        {
            System.out.println(lista.get(i).getImie() + " " + lista.get(i).getNazwisko() + " " + lista.get(i).getWiek());
        }
    }

    public void sort_imie_rosnaca()
    {
        Collections.sort(lista,new sortNameUp());
    }

    public void sort_imie_malejaca()
    {
        Collections.sort(lista,new sortNameDown());
    }

    public void sort_nazwisko_rosnaca()
    {
        Collections.sort(lista,new sortLNameUp());
    }

    public void sort_nazwisko_malejaca()
    {
        Collections.sort(lista,new sortLNameDown());
    }

    public void sort_wiek_rosnaca()
    {
        Collections.sort(lista,new sortAgeUp());
    }

    public void sort_wiek_malejaca()
    {
        Collections.sort(lista,new sortAgeDown());
    }
}

class sortNameUp implements Comparator<Student>
{
    public int compare(Student s1, Student s2)
    {
        return s1.getImie().compareTo(s2.getImie());
    }
}

class sortNameDown implements Comparator<Student>
{
    public int compare(Student s1, Student s2)
    {
        return s2.getImie().compareTo(s1.getImie());
    }
}

class sortAgeUp implements Comparator<Student>
{
    public int compare(Student s1, Student s2)
    {
        return s1.getWiek() - s2.getWiek();
    }
}

class sortAgeDown implements Comparator<Student>
{
    public int compare(Student s1, Student s2)
    {
        return s2.getWiek() - s1.getWiek();
    }
}

class sortLNameUp implements Comparator<Student>
{
    public int compare(Student s1, Student s2)
    {
        return s1.getNazwisko().compareTo(s2.getNazwisko());
    }
}

class sortLNameDown implements Comparator<Student>
{
    public int compare(Student s1, Student s2)
    {
        return s2.getNazwisko().compareTo(s1.getNazwisko());
    }
}