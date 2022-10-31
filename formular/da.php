<html>
<head><title>Calculator de medii</title></head>
<body>
<h1><b>Calculator de medii</b></h1>
<body bgcolor=pink>
<?php
$n=$_POST["nr"];
for($i=1;$i<=$n;$i++) {
$var="k".$i;
$med=$med+$_POST["{$var}"];
}
$med=($med*1.00)/$n;
echo "Ai media ".$med.".<br>";
if($med>=9) echo"Excelent!";
else if($med>=7) echo"Esti ok";
else if($med>=5) echo"Esti la limita";
else echo"Nu treci anul. Mai invata!";
?>
</body>
</html>