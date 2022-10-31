<html>
<head><title>Calculator de medii</title></head>
<body>
<h1><b>Calculator de medii</b></h1>
<body>
<?php
$med=($_POST['nota1']+$_POST['nota2'])/2;
echo "Ai media ".$med.".<br>";
if($med>=9) echo"Excelent!";
else if($med>=7) echo"Esti ok";
else if($med>=5) echo"Esti la limita";
else echo"Nu treci anul. Mai invata!";
?>
</body>
</html>