<?php
 
function __autoload($class_name) {
    include $class_name . '.php' ;
}
 

echo "<link rel='stylesheet' href = '../CSS/style.css'>";
$user = new Register_new;

if ( ! $user->_is_logged() )
{  
    echo "<h1>BOOK CLUB</h1>";
    echo "<p><a href='../htmls/reg.html'>Rejestracja</a></p>";
    echo "<p><a href='../htmls/log.html'>Logowanie</a></p>";

} 
else
{
    echo "<h1>BOOK CLUB</h1>";
    echo "<p><a href='../htmls/Add_book.html'>Dodaj książkę</a></p>";
    echo "<p><a href='../htmls/Find_book.html'>Znajdź książkę</a></p>";
    echo "<p><a href='../htmls/My_books.html'>Moje półki</a></p>";
    echo "<p><a href='my_transactions.php'>Moje transakcje</a></p>" ;
    echo "<p><a href='logout.php'>Wyloguj</a></p>" ;
}

?>