<?php

include 'find_book_utils.php';

session_start();

$email = $_SESSION['user'];
$select = $_POST['showtime'];
$value = $_POST['data'];
$proceed = true;

if($select != "all" && $select != "random" && $select != "exchange")
{
    if(empty($value))
    {
        echo ("<div id='err'>PROSZĘ WYPEŁNIĆ POLA!</div></b>");
        $proceed = false;
    }
}

// echo "email = $email</br>";

if ( !empty($email) )
{
    if($proceed)
    {
        // if($select == 'genre')
        // {

        //     echo $value."</br>";
        //     $value = genre_dict($value);
        //     echo $value."</br>";
        // }

        find_book($select, $email, $value);
    }
}
else
{
    echo "Użytkownik niezalogowany</br>";
}

echo "<p><a href='main_page.php'>Powrot do programu glownego</a></p>";

// echo
// "
// <form name='test2' action='index.php' method='post'>
// <input type='text' name='title' required><br/>
// <input type='submit'>
// </form>
// "

?>