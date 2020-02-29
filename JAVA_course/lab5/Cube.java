/**
*klasa dziedziczaca po Square
*@autor Maria Korkuć 
*/
public class Cube extends Square
{
    double depth;

    /**
    *konstruktor Cube
    *ustawia wartości area (oblicza) oraz volume (oblicza)
    *ustawia wartosc name na Cube
    *@param n_side dlugosc boku, n_x wspolrzedna x, n_y wspolrzedna y
    */
    Cube(double n_side, double n_x, double n_y)
    {
        /**
        *inicjalizacja klasy nadrzędnej Square
        */
        super(n_side, n_x, n_y);

        depth = n_side;

        area = 6 * n_side * n_side;
        volume = n_side * n_side * n_side; 
        name = "Cube";
    }

    /**
    *tworzy odpowiednie wypisywanie dla klasy Cube
    *nadpisuje dziedziczoną metodę po klasie Square
    *@return sformatowane wyswietlanie
    */
    public String toString()
    {
        return super.toString() + "; depth = " + depth;
    }


}
