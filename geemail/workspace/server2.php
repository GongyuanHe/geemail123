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
    
    
<input type="button" style="visibility:hidden;" name="aaa" class="myButton" id="myButton1" value="prompt to your mailbox" onclick="function1()"></button>

<input type="button" style="visibility:hidden;" name="aaa" class="myButton" id="myButton2" value="return" onclick="myFunction2()"></button>
<p id="demo"></p>

<?php
$name = $_POST["username"];
$password = $_POST["password"];
$tmp = exec("./check_login $name $password");
if ($tmp == "true"){}
$_SESSION["varname"] = $name;
?>



<script>
var tmp 
tmp = "<?php echo $tmp ?>";
function show1()
{document.getElementById('myButton1').style.visibility="visible";}
function show2(){document.getElementById('myButton2').style.visibility="visible";}

function myFunction2(){
          window.location.assign("https://geemail-cloned-parkhe.c9users.io/login.php");
    }
    
function function1(){window.location.assign("https://geemail-cloned-parkhe.c9users.io/contact_page.php");}

if (tmp == "true"){show1();
    
    
}


else {document.getElementById("demo").innerHTML = "login failed you may get wrong password";
    show2();
	
}
    
    
    
</script>


</body>
<html>