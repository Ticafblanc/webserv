let page = {};
page.console = (function(){
    let console = document.querySelector('#terminal .write');

    return {
        print: function(text){
            text = (text !== undefined ? text : '');
            text = String(text);
            text = text.replace(/ /g, '\u00A0');
            setTimeout(() => {
                console.innerText += text
                console.scrollTop = console.scrollHeight - console.clientHeight;
            });
        },
        println: function(text){
            text = (text !== undefined ? text : '');
            text = String(text);
            text = text.replace(/ /g, '\u00A0');
            setTimeout(() => {
                console.innerText += text + '\n'
                console.scrollTop = console.scrollHeight - console.clientHeight;
            });
        },

        clear: function(){
            setTimeout(() => {
                console.innerHTML = ''
                console.scrollTop = console.scrollHeight - console.clientHeight;
            });
        },

        input: function(text){
            this.print(text);
            value = prompt(text);
            this.println(value);
            return value;
        },
    }
})();