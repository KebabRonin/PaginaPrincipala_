<html>
<head> <title>Generator de numere prime</title>
</head>
<body>
<h1>Generator tabel numere prime</h1>
<table border=2px><tbody>
<?php
$ned=$_POST["panlacat"];
$nrcol=$_POST["col"];
$v[1]=2; $c=3; $I=1;
while($c<=$ned) { $ok=1;
for($i=1;$i<=$I && $ok;$i+=1) {
if($c%$v[$i]==0) $ok=0;
}
if($ok==1) {$I++; $v[$I]=$c;}
$c++;
}
$c=$I/$nrcol; $c=floor($c);
for($i=1;$i<=$c;$i++){
echo "<tr>";
for($j=1;$j<=$nrcol;$j++) {
$k=($i-1)*$nrcol+$j;
echo "<td>".$v[$k]."</td>";
}
echo "</tr>";
}
$i=$c*$nrcol;
$c=$I-$i;
if($c) {
echo "<tr>";
for($j=1;$j<=$c;$j++) {
$k=$i+$j;
echo "<td>".$v[$k]."</td>";
}
$x=" ";
while($j<=$nrcol) {echo "<td></td>";$j++;}
echo "</tr>";
}
?>
</tbody></table>
</body>
</html>