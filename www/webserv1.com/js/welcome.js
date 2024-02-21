let login;
while (login !== 'Matthis'){
    login = page.console.input('window.location.hostname');
    if(login == null)
        window.location.href = window.location.protocol +"/webserv1.com/goodbye.html" ;

}

while (login !== 'coucou'){
    login = page.console.input('Enter your password : ');
    if(login == null)
        window.location.href = window.location.protocol +"/webserv1.com/goodbye.html" ;
}
