<?php
    if ($_SERVER['REQUEST_METHOD'] === 'GET') {
        $server = $_SERVER['SERVER_SOFTWARE'];
        header('Content-Type: text/html; charset=utf-8');
        header('Content-length: 10;');
        $name = $_GET['name'] ?? 'World';
        $lastName = $_GET['lastName'] ?? 'World';
        $email = $_GET['email'] ?? 'World';
        $birthDay= $_GET['birthDay'] ?? 'World';
        echo "<h1>Hello, $name, you got</h1>";
        echo "<p>Your lastName is: $lastName and your email is $email. You were born at this date: $birthDay</p>";
    }

//     $_POST for application/x-www-form-urlencoded ou multipart/form-data //
//     php://input for other content
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
//         $postData = file_get_contents('php://input');
        $server = $_SERVER['SERVER_SOFTWARE'];
        header('Content-Type: text/html; charset=utf-8');
//         header('Content-length: 10;');
        $name = $_POST['name'] ?? 'World';
        $lastName = $_POST['lastName'] ?? 'World';
        $email = $_POST['email'] ?? 'World';
        $birthDay= $_POST['birthDay'] ?? 'World';
        $file = $_FILES['file']["tmp_name"];
        header('Content-Type: text/html; charset=utf-8');
        if (!$name || !$lastName || !$email || !$birthDay || !$file)
        {
            echo "<h1>Please complete the form!</h1>";
            echo "
            <form action='http://localhost:5173/form'>
                <input type='submit' value='Try again'/>
            </form>
            ";
        }
//         header('Content-length: ' . mb_strlen($postData, 'UTF-8') + 3);
        else {
            echo "<h1>Hello, $name, you posted</h1>";
            echo "<p>Your lastName is: $lastName and your email is $email. You were born at this date: $birthDay</p>";
            $fileContent = file_get_contents("$file");
            $lines = explode("\n", $fileContent);
            foreach ($lines as $line)
            {
                echo "<p>$line</p>";
            }
            echo "
            <form action='http://localhost:5173/'>
                <input type='submit' value='retour'/>
            </form>
            ";
        }
    }
?>
