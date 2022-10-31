<html>
<head><title>Lucru cu fisiere</title>
</head>
<body>
<h1>Lucru cu fisiere</h1>
<form action="index.php" method=POST>
<input name=nume value="Nume" type=text>
<input name=prenume value="Prenume" type=text>
<input name=varsta default="Varsta" type=number>
<div style="display:inline-block; border:2px solid; margin:auto; padding:5px;">
<input type=radio name=sex value=masculin> <label for=masculin>masculin</label><br>
<input type=radio name=sex value=feminin> <label for=feminin>feminin</label><br>
</div>
<input type=submit value="Introdu">
</form>
<?php
$file=fopen("elevi.txt",a);
$x=$_POST['$nume']." ".$_POST['$prenume']." ".$_POST['$varsta']." ".$_POST['$sex'];
if($x) $file=$x."<br>";
$file=fopen("elevi.txt","ra");
echo "<table border=1px><th>Nume</th><th>Prenume</th><th>Varsta</th><th>Sex</th>";
echo "</table>";
?>
</body>
</html>