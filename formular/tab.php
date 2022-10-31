<html>
<head><title>Calculator de medii</title></head>
<body>
<h1><b>Calculator de medii</b></h1>
<form name="note" action="da.php" method="POST">
<table border="0">
<?php
$n=$_POST["nr"];
for($i=1;$i<=$n;$i++) {
echo"<tr><td> <b>Nota ".$i." este </b>";
echo"<td><input name=k".$i." type=number value=1 min=1 max=10 step=0.1></td></tr>";
}
echo "<input name=nr type=hidden value=".$n.">"
?>

<tr>
<td><input name="trim" type="submit" value="da-mi de lucru"></td>
</tr>
</table>
</form>
</body>
</html>