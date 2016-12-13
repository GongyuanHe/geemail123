<html>
    <style>
input[type=text], select {
    width: 100%;
    padding: 12px 20px;
    margin: 8px 0;
    display: inline-block;
    border: 1px solid #ccc;
    border-radius: 4px;
    box-sizing: border-box;
}
.button {
    width: 100%;
    background-color: #008CBA;
     /* Green */
    border: none;
    color: white;
    padding: 15px 32px;
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: 16px;
    margin: 8px 2px;
    cursor: pointer;
}
p{ color: #685206; font-family: 'Helvetica Neue', sans-serif; font-size: 20px; line-height: 30px; margin: 0 0 40px; text-align: justify; text-justify: inter-word;  }
h2{ color: #685206; font-family: 'Helvetica Neue', sans-serif; font-size: 40px; line-height: 50px; margin: 0 0 50px; text-align: justify; text-justify: inter-word;  }
input[type=text]:hover {
    background-color: #45a049;
}
.button2{
    width: 100%;
    background-color: #555555;
    border: none;
    color: white;
    padding: 15px 32px;
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: 16px;
    margin: 8px 2px;
    cursor: pointer;
}
div {
    border-radius: 5px;
    background-color: #f2f2f2;
    padding: 20px;
}
</style>
<body
    â€œstyle="background-image:url(); background-repeat:repeat-y;"â€>
<h2>gee mail register</h2>
<form action="server.php" method="post">
<p>user name:</p><input type="text" name="username" id="myText1" value="">
<p>password:</p><input type="text" name="password" id="myText2" value="">
<input type="submit" class="button" value="confirm">
</form>




<input type="button" class="button2" onclick="myFunction2()" value="return"></button>

<script >

    
    
    function myFunction2(){
          window.location.assign("https://geemail-cloned-parkhe.c9users.io/login.php");}
          
    function myFunction1(){   
        var username = document.getElementById("myText1").value;
        var password = document.getElementById("myText2").value;
        var xmlhttp = new XMLHttpRequest();
           xmlhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("myText1").innerHTML = this.responseText;
            }
        };
        xmlhttp.open("POST", "server.php?q=" + username, true);
        xmlhttp.open("POST", "server.php?m=" + password, true);
        xmlhttp.send();}
</script>



  <?php
$a = "<script>document.writeln(username);</script>";
$b = "<script>document.writeln(password);</script>";
echo $a;
$tmp=exec ("./register $a $b");


?>


</body>
</html>