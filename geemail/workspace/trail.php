<?php
// Echo session variables that were set on previous page
$name = "p.py";
$show = exec("python $name");
echo $show;

?>