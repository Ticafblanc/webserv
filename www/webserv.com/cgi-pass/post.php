<!doctype html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Webserv 42</title>
    <link rel="stylesheet" href="../css/reset.css">
    <link rel="stylesheet" href="../css/style.css">
</head>

<body>
<header>
    <h1><a href="../accueille.html">Werbserv 42</a></h1>
    <div class="test">
        <a href="../html/index.html" class="static out">Static request</a>
        <a href="index.php" class="cgi in">Dynamic request</a>
    </div>
    <aside>
        <a href="get.php" class="cgi request out">GET request</a>
        <a href="post.php" class="cgi request in">POST request</a>
        <a href="delete.php" class="cgi request out">DELETE request</a>
    </aside>
</header>

<main>
    <p>Date et Heure actuelle : <?php echo date('d/m/Y H:i:s'); ?></p>
</main>


<footer>
    <p>&copy; Copyright Matthis DoQuocBao | 42 Quebec</p>
</footer>

</body>

</html>
