// Exercice 3
page.console.println('Entrez une équation quadratique: ');
let a = page.console.input('A = ');
let b = page.console.input('B = ');
let c = page.console.input('C = ');
let calc = (b * b) - (4 * a * c);

page.console.println('\nRésultat: ');
if(calc < 0){
    page.console.println('Aucune solution');
}
else{
    x1 = (-b + Math.sqrt(calc)) / (2 * a)
    x2 = (-b - Math.sqrt(calc)) / (2 * a)

    page.console.println('X1 = ' + x1);
    if(x1 !== x2){
        page.console.println('X2 = ' + x2);
    }
}