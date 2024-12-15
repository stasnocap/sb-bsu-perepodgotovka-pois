<?php
function validateInput($input) {
    // Check for invalid characters
    if (strpos($input, '=') !== false || strpos($input, "\n") !== false || strpos($input, "\r") !== false) {
        return false;
    }
    return true;
}

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $username = $_POST['username'];
    $password = $_POST['password'];

    // Validate input
    if (!validateInput($username) || !validateInput($password)) {
        echo "Invalid input.";
        exit;
    }

    $file = 'users.txt';
    $lines = file($file);

    $validUser = false;
    for ($i = 0; $i < count($lines); $i += 2) {
        $file_user = trim(explode('=', $lines[$i])[1]);
        $file_pass = trim(explode('=', $lines[$i + 1])[1]);

        if ($username == $file_user && $password == $file_pass) {
            $validUser = true;
            break;
        }
    }

    if ($validUser) {
        echo "Login successful.";
    } else {
        echo "Access denied.";
    }
}
?>