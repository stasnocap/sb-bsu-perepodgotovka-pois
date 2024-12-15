<?php
function isPrime($num) {
    if ($num <= 1) {
        return false;
    }
    for ($i = 2; $i <= sqrt($num); $i++) {
        if ($num % $i == 0) {
            return false;
        }
    }
    return true;
}

$primes = [];
$num = 2;
while (count($primes) < 10) {
    if (isPrime($num)) {
        $primes[] = $num;
    }
    $num++;
}
?>

<!DOCTYPE html>
<html>
<head>
    <title>Prime Numbers</title>
</head>
<body>
    <table border="1">
        <tr>
            <th>Number</th>
            <th>Prime</th>
        </tr>
        <?php
        foreach ($primes as $index => $prime) {
            echo "<tr><td>" . ($index + 1) . "</td><td>" . $prime . "</td></tr>";
        }
        ?>
    </table>
</body>
</html>