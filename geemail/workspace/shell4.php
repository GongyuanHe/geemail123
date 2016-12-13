<?php
session_start();
?>
<!DOCTYPE html>
<html>
<body>
	<style>
.myButton {
	-moz-box-shadow:inset 0px -3px 7px 0px #29bbff;
	-webkit-box-shadow:inset 0px -3px 7px 0px #29bbff;
	box-shadow:inset 0px -3px 7px 0px #29bbff;
	background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #2dabf9), color-stop(1, #0688fa));
	background:-moz-linear-gradient(top, #2dabf9 5%, #0688fa 100%);
	background:-webkit-linear-gradient(top, #2dabf9 5%, #0688fa 100%);
	background:-o-linear-gradient(top, #2dabf9 5%, #0688fa 100%);
	background:-ms-linear-gradient(top, #2dabf9 5%, #0688fa 100%);
	background:linear-gradient(to bottom, #2dabf9 5%, #0688fa 100%);
	filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#2dabf9', endColorstr='#0688fa',GradientType=0);
	background-color:#2dabf9;
	-moz-border-radius:3px;
	-webkit-border-radius:3px;
	border-radius:3px;
	border:1px solid #0b0e07;
	display:inline-block;
	cursor:pointer;
	color:#ffffff;
	font-family:Arial;
	font-size:15px;
	padding:9px 23px;
	text-decoration:none;
	text-shadow:0px 1px 0px #263666;
}
</style>
<?php
// Echo session variables that were set on previous page
$receiver=$_SESSION["receiver"];
$sender=$_SESSION["sender"];
$name=$_SESSION["varname"];
$show=exec("./write_message $name $receiver '$message'");
echo $show;
echo "<br>"; 




   $fh = fopen("write_message.txt", 'r');

    $pageText = fread($fh, 25000);
    
    echo nl2br($pageText);

?>

<br><br>
<input type="text"  name="aaa" class="myButton" id="myButton"  onclick="myFunction()" value="return">
<input type="text"  name="aaa" class="myButton" id="myButton2"  onclick="myFunction2()" value="if the passphrase is right">


<script>
	function myFunction(){window.location.assign("https://geemail-cloned-parkhe.c9users.io/shell3.php");}
	function myFunction2(){window.location.assign("https://geemail-cloned-parkhe.c9users.io/contact_page.php");}
	

	
	
	
</script>




</body>
</html>