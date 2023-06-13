// import * as readline from 'node:readline';
// import * as readline from 'node:readline/promises';
// import * as readline from 'node:readline/promises';
// import { stdin as input, stdout as output } from 'node:process';

const readline = require('readline');
const { spawn } = require('child_process');

// const rl = readline.createInterface({ input, output });
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

rl.question('Webserv > ', (command) => {
    const child = spawn('bash', ['-c', command]);
    child.stdout.on('data', (data) => {
        page.console.print(`Webserv > ${data}\n`);
    });
    // child.stderr.on('data', (data) => {
    //     write.innerText += `Webserv > ${data}\n`;
    // });
    // child.on('close', (code) => {
    //     write.innerText += `Process finished with exit code ${code}\n`;
    //     rl.close();
    // });
    // rl.on('close', () => {
    //     write.innerText += `Interface de ligne de commande fermée\n`;
    //     while (true) {
    //         // Attendre une entrée utilisateur pour fermer le programme
    //     }
    // });
});


