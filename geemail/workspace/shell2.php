<?php
session_start();
?>
<!DOCTYPE html>
<html>
	
	<style>
	.button2{
	width: 600px;
	height: 120px;
	border: 3px solid #cccccc;
	padding: 5px;
	font-family: Tahoma, sans-serif;
	background-image: url(bg.gif);
	background-position: bottom right;
	background-repeat: no-repeat;
	
}
.button1{         font-family: times, Times New Roman, times-roman, georgia, serif;
 color: #444;
 margin: 0;
 padding: 0px 0px 6px 0px;
 font-size: 51px;
 line-height: 44px;
 letter-spacing: -2px;
 font-weight: bold;}
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
.button2{
	width: 600px;
	height: 120px;
	border: 3px solid #cccccc;
	padding: 5px;
	font-family: Tahoma, sans-serif;
	background-image: url(bg.gif);
	background-position: bottom right;
	background-repeat: no-repeat;
	
}


</style>


<body>
<form action="shell3.php" method="post">
<p>mid:<input type="text"  name="mid" class="button11" id="user"  onclick="myFunction2()"></button></p>
<p>sender:  <input type="text"  name="sender" class="button11" id="receiver"  onclick="myFunction2()"></button></p>
<p>passphrase:  <input type="text"  name="passphrase" class="button11" id="receiver"  onclick="myFunction2()"></button></p>
<p></p></p><input type="submit" value="read" class="myButton">
</form>
<input type="text"  name="aaa" class="myButton" id="myButton"  onclick="myFunction()" value="return"><br>
<script>
	function myFunction(){window.location.assign("https://geemail-cloned-parkhe.c9users.io/contact_page.php");}
	
	
	
</script>
<?php
// Echo session variables that were set on previous page
$name=$_SESSION["varname"];
   $fh = fopen("infomation.txt", 'r');

    $pageText = fread($fh, 25000);
    
    echo nl2br($pageText);

?>


</body>
</html>
