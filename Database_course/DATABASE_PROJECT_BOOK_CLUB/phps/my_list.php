<?php

include 'functions.php';


$email = $_SESSION['user'];
$mode = $_POST['ex'];

if ( !empty($email) )
{
    $exists = true;
    $id_user = get_new_index('club_user', $email, $exists);

    if($mode == 'wish')
    {
        //WYSWIETLAJ KSIAZKI Z WISH_LIST TEGO UZYTKOWNIKA
        $query = "SELECT b.title, a.surname, id.id_desc FROM ((((book_club.author a join book_club.book b on a.id_author = b.id_author)
        join book_club.book_list bl on b.id_book = bl.id_book) join book_club.wish_list wl on bl.id_list = wl.id_list) 
        join  book_club.book_item bi on b.id_book = bi.id_book) join book_club.item_description id on bi.id_desc = id.id_desc 
        WHERE wl.id_user = $id_user ";
        
        $res = Result($query);

        $rows = pg_num_rows($res);

        if(!$rows)
        {
            echo "<p>Lista pusta</p></br>";
            echo "<p><a href='main_page.php'>Powrot do programu glownego</a></p>";
        }
        else
        {
            echo "<table>";echo "<tr>
            <th>Tytuł</th>
            <th>Autor</th>
            <th>Szczegóły</th>
          </tr>";
            while($row=pg_fetch_assoc($res)) 
            {
                echo "<tr>";
                echo "<td align='center' width='200'>" . $row['title'] . "</td>";
                echo "<td align='center' width='200'>" . $row['surname'] . "</td>";
                echo "<td align='center' width='200'><form name='test2' method='post' action='Show_details.php'>
        <button name='details' type='submit' value='".$row['id_desc']."'>Szczegóły</button></form></td>";
                echo "</tr>";   
            }
            echo "</table>";

            echo "<p><a href='main_page.php'>Powrot do programu glownego</a></p>";
        }
    }
    else if($mode == 'mine')
    {
        //WYSWIETLAJ KSIAZKI Z BOOK_ITEM TEGO UZYTKOWNIKA
        $query = "SELECT b.title, a.surname, id.id_desc FROM ((book_club.author a join book_club.book b on a.id_author = b.id_author)
        join book_club.book_item bi on b.id_book = bi.id_book)
        join book_club.item_description id on bi.id_desc = id.id_desc 
        WHERE bi.id_owner = $id_user ";

        $res = Result($query);

        $rows = pg_num_rows($res);

        if(!$rows)
        {
            echo "<p>Nie masz książek</p></br>";

            echo "<p><a href='main_page.php'>Powrot do programu glownego</a></p>";
        }
        else
        {
            echo "<table>";echo "<table>";echo "<tr>
            <th>Tytuł</th>
            <th>Autor</th>
            <th>Szczegóły</th>
          </tr>";
            while($row=pg_fetch_assoc($res)) 
            {
                echo "<tr>";
                echo "<td align='center' width='200'>" . $row['title'] . "</td>";
                echo "<td align='center' width='200'>" . $row['surname'] . "</td>";
                echo "<td align='center' width='200'><form name='test2' method='post' action='Show_details.php'>
        <button name='details' type='submit' value='".$row['id_desc']."'>Szczegóły</button></form></td>";
                echo "</tr>";   
            }
            echo "</table>";

            echo "<p><a href='main_page.php'>Powrot do programu glownego</a></p>";

        }
    }
    else
    {
        echo "Wystąpił błąd</br>";
        exit;
    }
}


?>