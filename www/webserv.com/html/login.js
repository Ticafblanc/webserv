document.getElementById('loginForm').onsubmit = function(e) {
    e.preventDefault();

    var username = document.getElementById('username').value;
    var password = document.getElementById('password').value;

    if(username === "user" && password === "pass") {
        window.location.href = "/accueil.html"; // Redirection vers la page d'accueil
    } else {
        alert("Nom d'utilisateur ou mot de passe incorrect !");
    }
}