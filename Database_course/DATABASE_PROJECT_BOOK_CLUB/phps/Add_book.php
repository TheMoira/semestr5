<?php

include 'add_book_utils.php';
include 'Book.php';


$book = new Book;
$book->_set_values();

$email = $_SESSION['user'];

if ( !empty($email) )
{
    add_book($book, $email);
}
else
{
    echo "Użytkownik niezalogowany</br>";
}

echo "<p><a href='main_page.php'>Powrot do programu glownego</a></p>";

?>

<!-- 
echo "<table>\n";
while ($line = pg_fetch_array($result, null, PGSQL_ASSOC)) {
    echo "\t<tr>\n";
    foreach ($line as $col_value) {
        echo "\t\t<td>$col_value</td>\n";
    }
    echo "\t</tr>\n";
}
echo "</table>\n"; -->