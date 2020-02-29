<?php

include 'functions.php';


$email = $_SESSION['user'];


if ( !empty($email) )
{
    $exists = true;
    $id_user = get_new_index('club_user', $email, $exists);

    $query1 = "SELECT t.trans_type, t.trans_date, t.price, b.title, id.id_desc 
    FROM ((book_club.transaction t join book_club.book b on t.id_book1 = b.id_book OR t.id_book2 = b.id_book) 
    join book_club.book_item bi on b.id_book = bi.id_book)
    join book_club.item_description id on bi.id_desc = id.id_desc
    WHERE t.id_owner1 = $id_user";

    $query2 = "SELECT t.trans_type, t.trans_date, t.price, b.title, id.id_desc 
    FROM ((book_club.transaction t join book_club.book b on t.id_book1 = b.id_book OR t.id_book2 = b.id_book)
    join book_club.book_item bi on b.id_book = bi.id_book)
    join book_club.item_description id on bi.id_desc = id.id_desc
    WHERE t.id_owner2 = $id_user";

        
    $res1 = Result($query1);
    $res2 = Result($query2);

    $rows1 = pg_num_rows($res1);
    $rows2 = pg_num_rows($res2);

        if(!$rows1 && !$rows2)
        {
            echo "<p>Lista pusta</p></br>";
            echo "<p><a href='main_page.php'>Powrot do programu glownego</a></p>";
        }
        else
        {
            echo "<table>";
            echo "<tr>
        <th>Tytuł</th>
        <th>Rodzaj transakcji</th>
      <th>Cena</th>
      <th>Data</th>
      <th>Szczegóły</th>
      </tr>";
            while($row1=pg_fetch_assoc($res1)) 
            {
                echo "<tr>";
                echo "<td align='center' width='200'>" . $row1['title'] . "</td>";
                echo "<td align='center' width='200'>" . $row1['trans_type'] . "</td>";
                if($row1['trans_type'] == 'sale') 
                {
                    echo "<td align='center' width='200'>" . $row1['price'] . "</td>";
                }else
                {echo "<td align='center' width='200'>Brak</td>";}
                echo "<td align='center' width='200'>" . $row1['trans_date'] . "</td>";
                echo "<td align='center' width='200'><form name='test2' method='post' action='Show_details.php'>
        <button name='details' type='submit' value='".$row1['id_desc']."'>Szczegóły</button></form></td>";
            }
            
            while($row2=pg_fetch_assoc($res2)) 
            {
                echo "<td align='center' width='200'>" . $row2['title'] . "</td>";
                echo "<td align='center' width='200'>" . $row2['trans_type'] . "</td>";
                if($row2['trans_type'] == 'sale') echo "<td align='center' width='200'>" . $row2['price'] . "</td>";
                echo "<td align='center' width='200'>" . $row2['trans_date'] . "</td>";
                echo "<td align='center' width='200'><form name='test2' method='post' action='Show_details.php'>
        <button name='details' type='submit' value='".$row2['id_desc']."'>Szczegóły</button></form></td>";
                echo "</tr>";   
            }
            echo "</table>";
            echo "<p><a href='main_page.php'>Powrot do programu glownego</a></p>";

        }

}


?>