// Exercice 1
let nbZerosArret = page.console.input('Entrez un nombre de zéros avant d\'arrêter: ');
let nbZeros = 0;
let nbGen = 0;

nbZerosArret = nbZerosArret || 10;
while(nbZeros < nbZerosArret){
    let chiffre = Math.random() < 0.5 ? 0 : 1;
    page.console.print(chiffre);

    nbGen++;
    if(chiffre === 0) {
        nbZeros++;
    }
    else{
        nbZeros = 0;
    }
}


page.console.println();
page.console.println('Quantité de nombres générés: ' + nbGen);