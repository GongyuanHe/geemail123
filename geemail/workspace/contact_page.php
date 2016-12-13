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
<form action="shell.php" method="post">
<p>user:<input type="text"  name="user" class="button11" id="user"  onclick="myFunction2()"></button></p>
<p>receiver:  <input type="text"  name="receiver" class="button11" id="receiver"  onclick="myFunction2()"></button></p>
<p>message:</p>  <input type="text"  name="message" class="button2" id="myButton2"  onclick="myFunction2()"></button>
<p>passphrase:</p>  <input type="text"  name="passphrase" class="button22" id="myButton22"></button>
<p></p></p><input type="submit" value="write email" class="myButton">
</form>
<input type="button"  name="aaa" class="myButton" id="myButton222"  onclick="myFunction222()" value="read message"><br>
<input type="button"  name="aaaa" class="myButton" id="myButton2223"  onclick="myFunction2223()" value="logout"><br>
<?php
// Echo session variables that were set on previous page
$name=$_SESSION["varname"];
$s=exec("./infomation $name");
//shell_exec ('./showinfomation $name');//nice haishibuxing keshi ke
//echo $name;
   $fh = fopen("infomation.txt", 'r');//

    $pageText = fread($fh, 25000);

    
    echo nl2br($pageText);

?>
<script>
	var dom = "<?php echo $name ?>" ;
	document.getElementById("user").value= dom;

	var showinformation = "<?php echo $show ?>";
	document.getElementById("information").value=showinformation;
	function myFunction222(){window.location.assign("https://geemail-cloned-parkhe.c9users.io/shell2.php");}
	function myFunction2223(){window.location.assign("https://geemail-cloned-parkhe.c9users.io/login.php");}
	
</script>

</body>
</html>
