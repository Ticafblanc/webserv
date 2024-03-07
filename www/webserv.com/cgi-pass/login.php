<?php
// login.php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $username = $_POST['username'];
    $password = $_POST['password'];

    // Exemple de vérification statique, remplacez ceci par une vérification de base de données dans la pratique
    if ($username == 'user' && $password == 'pass') {
        // Redirection vers la page sécurisée
        header('Location: accueil.php');
        exit();
    } else {
        // Retourner une erreur ou rediriger vers le formulaire de connexion avec un message d'erreur
        echo "Nom d'utilisateur ou mot de passe incorrect.";
        // Pour rediriger vers le formulaire de connexion avec un message d'erreur, vous pouvez utiliser des sessions ou des paramètres GET
        // header('Location: login.html?error=invalidcredentials');
        // exit();
    }
}
?>