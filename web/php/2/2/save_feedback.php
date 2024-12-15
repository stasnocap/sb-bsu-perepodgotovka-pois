<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $name = htmlspecialchars($_POST['name']);
    $email = htmlspecialchars($_POST['email']);
    $message = htmlspecialchars($_POST['message']);

    $file = 'feedback.txt';
    $data = "[---------------------------------]\n";
    $data .= "user:\n" . $name . "\n";
    $data .= "email:\n" . $email . "\n";
    $data .= "message:\n" . $message . "\n";

    file_put_contents($file, $data, FILE_APPEND);
    echo "Feedback successfully saved.";
}
?>