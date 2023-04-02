// Exercice 2
let phrase = page.console.input('Entrez une phrase: ');
phrase = phrase || '';

let i = 0;
let j = phrase.length - 1;

while(i < j){
    if(phrase.charAt(i) !== phrase.charAt(j)){
        break;
    }

    i++;
    j--;
}

if(i >= j){
    page.console.print('Cette phrase est un palyndrôme');
}
else{
    page.console.print('Cette phrase n\'est pas un palyndrôme');
}
