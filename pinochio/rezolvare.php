<html>
<head><title>Pinochio</title>
</head>
<body>
<h1>Problema mea Pinochio</h1>
<?php
echo "Dupa ".$_POST['nrzil']." zile, nasul lui pinochio are ";
$zil=$_POST['nrzil'];
$minci=$_POST['minc'];
$adevi=$_POST['adev'];
$lun=$_POST['init'];
$zia=$_POST['zi'];
if($zia=="Luni") $nrzi=1;
else if($zia=="Marti") $nrzi=2;
else if($zia=="Miercuri") $nrzi=3;
else if($zia=="Joi") $nrzi=4;
else if($zia=="Vineri") $nrzi=5;
else if($zia=="Sambata") $nrzi=6;
else if($zia=="Duminica") $nrzi=7;
$zil+=$nrzil;
for($i=$nrzi;$i<=$zil;$i=$i+1) {
if($i%7==0 || $i%7==6) $lun-=$adevi;
else $lun+=$minci;
}
echo $lun." cm."
?>
</body>
</html>