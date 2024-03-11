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
        <a href="get.php" class="cgi request in">GET request</a>
        <a href="post.php" class="cgi request out">POST request</a>
        <a href="delete.php" class="cgi request out">DELETE request</a>
    </aside>
</header>

<main>
      <p>Date et Heure actuelle : <?php echo date('d/m/Y H:i:s'); ?></p>
        <form action = "../cgi-bin/get_hello.py" method = "get">
              First Name: <input type = "text" name = "first_name">  <br />
              <br>
              Last Name: <input type = "text" name = "last_name" />
              <input type = "submit" value = "Submit" /> <br />
          </form>
           <form action = "../cgi-bin/calc.py" method = "get">
                  Number1: <input type = "text" name = "f_num">  <br />
                  <br>
                  Oparator : <input type = "text" name = "oper">  <br />
                  <br>
                  Number2: <input type = "text" name = "s_num" />
                  <input type = "submit" value = "Submit" /> <br />
              </form>
               <form action = "../cgi-bin/set_cookie.py" method = "get">
                          Cookie Name: <input type = "text" name = "key">  <br />
                          <br>
                          Cookie Value: <input type = "text" name = "value" />
                          <input type = "submit" value = "Submit" /> <br />
                      </form>

                      <br />
                      <br />
                      <br />
                      <br />
                      <h1> Get Cookie: </h1> <br />
                      <form action = "../cgi-bin/get_cookie.py" method = "get">
                          Cookie Name: <input type = "text" name = "key">  <br />
                          <br>
                          <input type = "submit" value = "Submit" /> <br />
                      </form>
                      <form action = "../cgi-bin/acc.py" method = "get">
                              <div class="container">
                                  <label>Username : </label>
                                  <input type="text" placeholder="Enter Username" name="username" required>
                                  <label>Password : </label>
                                  <input type="password" placeholder="Enter Password" name="password" required>
                                  <button type="submit">Login</button>
                                  No Account?<a href="/register.html"> Register Here </a>
                              </div>
                          </form>
                           <form action = "../cgi-bin/acc.py" method = "get">
                                  <div class="container">
                                      <label>Username : </label>
                                      <input type="text" placeholder="Enter Username" name="username" required>
                                      <label>Password : </label>
                                      <input type="password" placeholder="Enter Password" name="password" required>
                                      <label>FirstName : </label>
                                      <input type="text" placeholder="Enter FirstName" name="firstname" required>
                                      <button type="submit">Register</button>
                                      Already Have account?<a href="/cgi-bin/acc.py"> Login </a>
                                  </div>
                              </form>
</main>


<footer>
    <p>&copy; Copyright Matthis DoQuocBao | 42 Quebec</p>
</footer>

</body>

</html>

