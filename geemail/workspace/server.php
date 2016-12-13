

<html>
    <style>
    .button {
    width: 10%;
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
    </style>
<body>
    <br>
    <br>
    <br>
    <br>
    <br>
    <?php
$name = $_POST["username"];
$password = $_POST["password"];
$name2 ="'$name'";

$tmp = exec("./register $name2 $password");
echo "<div style ='font:50px/60px Arial,tahoma,sans-serif;color:#ff0000'> welcome to our websit you have already been registered</div>";

?>
<br><br><br><br>

<input type="button" class="button" onclick="myFunction1()" value="return to login page"></button>


<script >
    function myFunction1(){
          window.location.assign("https://geemail-cloned-parkhe.c9users.io/login.php");}
</script>
</body>
</html>