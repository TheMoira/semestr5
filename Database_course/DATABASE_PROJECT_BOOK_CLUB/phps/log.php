<?php
 
function __autoload($class_name) {
    include $class_name . '.php' ;
}
 
$user = new Register_new;
 
echo $user->_login() ;
echo "<p><a href='main_page.php'>Powrot do programu glownego</a></p>";
             
?>