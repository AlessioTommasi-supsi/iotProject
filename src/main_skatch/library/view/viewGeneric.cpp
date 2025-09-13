#include "viewGeneric.h"

String viewGeneric::html = "";

String viewGeneric::addCss(){
    // CSS super minimale - solo l'essenziale
    String css = R"(body{font-family:Arial;margin:0;padding:60px 10px 120px;display:flex;flex-direction:column;align-items:center;background:#f4f4f4})";
    return css;
}

String viewGeneric::addNavbarStyleCss(){
    String navbarStyleCss ="<style>";
    navbarStyleCss += viewGeneric::addNavbarCss();
    return navbarStyleCss;
};

String viewGeneric::addNavbarCss(){
    // CSS navbar minimalista
    String css = R"(.navbar{display:flex;justify-content:space-evenly;background:rgba(48,48,48,0.9);position:fixed;bottom:15px;left:50%;transform:translateX(-50%);width:80vw;padding:8px;border-radius:10px;z-index:2000}.navbar a{color:white;text-decoration:none;text-align:center;padding:8px}.navbar .icon{width:40px;height:40px;background:rgba(255,255,255,0.8);border-radius:6px;display:flex;align-items:center;justify-content:center;font-size:20px;color:#333}.navbar span{font-size:10px;margin-top:4px}@media(min-width:1500px){.navbar{flex-direction:column;top:50%;left:15px;transform:translateY(-50%);bottom:auto;width:auto;max-height:80vh}})";
    return css;
}

String viewGeneric::addPinCss(){
    // CSS pin super minimo
    String css = R"(.pin-container{background:rgba(255,255,255,0.9);border-radius:10px;padding:15px;margin:10px;width:80%;max-width:500px}.pin-info{margin-bottom:10px;font-weight:bold}.pin-actions button{padding:8px 12px;border:none;border-radius:4px;margin-right:8px;cursor:pointer}.pin-actions .start{background:#f44336;color:white}.pin-actions .stop{background:#999;color:white}.pin-actions .edit{background:#2196F3;color:white})";
    return css;
}

String viewGeneric::addPinStyleCss(){
    String pinStyleCss ="<style>";
    pinStyleCss += viewGeneric::addPinCss();
    pinStyleCss += "</style>";
    return pinStyleCss;
}

String viewGeneric::addFormStyleCss(){
    String formStyleCss = "<style>";
    formStyleCss += viewGeneric::addFormCss();
    formStyleCss += "</style>";
    return formStyleCss;
}

String viewGeneric::addFormCss(){
    // CSS form essenziale
    String css = R"(.form-container{width:90%;max-width:500px;background:rgba(255,255,255,0.95);padding:20px;border-radius:10px;margin:20px 0}form{display:flex;flex-direction:column}label{font-weight:bold;margin-bottom:5px}input,select{margin-bottom:10px;padding:8px;border:1px solid #ccc;border-radius:4px;font-size:14px}button{padding:10px;background:#4CAF50;color:white;border:none;border-radius:4px;cursor:pointer;font-size:14px}button:hover{background:#45a049}.history-table{width:100%;border-collapse:collapse;margin:10px 0}.history-table th,.history-table td{padding:8px;border:1px solid #ddd;font-size:14px}.history-table th{background:#f2f2f2})";
    return css;
}

String viewGeneric::addFieldFormStyleCss(){
    String formStyleCss = "<style>";
    formStyleCss += viewGeneric::addFieldFormCss();
    formStyleCss += "</style>";
    return formStyleCss;
}

String viewGeneric::addFieldFormCss(){
    // CSS form campi minimalista
    String css = R"(.form-container{background:rgba(255,255,255,0.9);border-radius:10px;padding:20px;margin:20px;width:90%;max-width:600px}fieldset{border:1px solid #ccc;border-radius:6px;margin:15px 0;padding:10px}legend{font-size:1.1em;font-weight:bold}input[type="number"],input[type="text"],select{width:100%;padding:8px;margin-bottom:10px;border:1px solid #ccc;border-radius:4px;font-size:14px}button{width:100%;padding:12px;background:#4CAF50;color:white;border:none;border-radius:4px;cursor:pointer;font-size:16px})";
    return css;
}


String viewGeneric::defaultPorfolioCss() {
    String porfolioCss = R"(
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>ALPHA</title>
        <link rel="icon" href="https://alessiotommasi.com/view/images/logo.png" type="image/png">

        <script>
        // Funzione che carica un CSS in modo asincrono
        function loadCSS(href) {
            var link = document.createElement('link');
            link.rel = 'stylesheet';
            link.href = href;
            link.onload = function() {
                console.log("CSS caricato: " + href);
            };
            link.onerror = function() {
                console.error("Errore nel caricamento del CSS: " + href);
            };
            document.head.appendChild(link);
        }

        // Carica i CSS una volta che il DOM è stato interamente caricato
        document.addEventListener("DOMContentLoaded", function() {
            loadCSS("http://alessiotommasi.com/view/css/style.css");
            loadCSS("http://alessiotommasi.com/view/css/gear.css");
            loadCSS("http://alessiotommasi.com/view/css/logo.css");
            loadCSS("http://alessiotommasi.com/view/css/glass_effect.css");
            loadCSS("http://alessiotommasi.com/view/css/autoType.css");
            loadCSS("http://alessiotommasi.com/view/css/buttons.css");
            loadCSS("http://alessiotommasi.com/view/css/dashboard.css");
            loadCSS("http://alessiotommasi.com/view/css/particle_style.css");
        });
        </script>

        <noscript>
            <link rel="stylesheet" href="http://alessiotommasi.com/view/css/style.css">
            <link rel="stylesheet" href="http://alessiotommasi.com/view/css/gear.css">
            <link rel="stylesheet" href="http://alessiotommasi.com/view/css/logo.css">
            <link rel="stylesheet" href="http://alessiotommasi.com/view/css/glass_effect.css">
            <link rel="stylesheet" href="http://alessiotommasi.com/view/css/autoType.css">
            <link rel="stylesheet" href="http://alessiotommasi.com/view/css/buttons.css">
            <link rel="stylesheet" href="http://alessiotommasi.com/view/css/dashboard.css">
            <link rel="stylesheet" href="http://alessiotommasi.com/view/css/particle_style.css">
        </noscript>
            )";
    return porfolioCss;
}

String viewGeneric::addNavbar()
{
    String navbar = R"(
        <!-- Navbar Responsive con Scorrimento Orizzontale -->
        <div class="navbar">
            <a href="/monitor">
            <div class="icon">🖥️</div>
            <span>Monitor</span>
            </a>
            <a href="/pinout">
            <div class="icon">🔌</div>
            <span>Pinout</span>
            </a>
            <a href="/currentregister">
            <div class="icon">📋</div>
            <span>Register</span>
            </a>
            <a href="/pin_history">
            <div class="icon">📌</div>
            <span>Pin History</span>
            </a>
            <a href="/modbus_history">
            <div class="icon">📊</div>
            <span>Modbus History</span>
            </a>
            <a href="/graph">
            <div class="icon">📈</div>
            <span>Graph</span>
            </a>
            <a href="/config">
            <div class="icon">📶</div>
            <span>WIfi Config</span>
            </a>
            <a href="/multiplex_config">
            <div class="icon">⚙️</div>
            <span>Multiplexer</span>
            </a>
            <a href="/ADS_history">
            <div class="icon">🔢</div>
            <span>ADS History</span>
            </a>
        </div>
        )";
    return navbar;
}

String viewGeneric::defaultHeader()
{
    html = "<!DOCTYPE html>";
    html += "<html>";
    html += "<head>";
    // html += "<meta http-equiv='refresh' content='5'>";
    html += "<title>DefaultTitle</title>";
    html += "</head>";
    html += "<body>";
    html += addNavbar();
    return html;
}

String viewGeneric::basicHeader(String title)
{
    html = "<!DOCTYPE html>";
    html += "<html>";
    html += "<head>";
    // html += "<meta http-equiv='refresh' content='5'>";
    //per  far si che riconosca emoji!
    html += R"(
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
    )";
    html += "<title>";
    html += title;
    html += "</title>";
    html += "<style>";
    html += addCss();
    html += "</style>";
    html += "</head>";
    html += "<body>";
    
    return html;
}

String viewGeneric::defaultCssHeader(String title)
{
    html = basicHeader(title);
    html += addNavbar();
    /**
     * Aggiungo il css comune a tutti i documenti anche se potrei farlo nelle singole viste per ottimizzare
     */
    String css ="";

    css += viewGeneric::dynamicUpdateContentScript(); //aggiungo script per aggiornamento dinamico
    css += viewGeneric::dynamicUpdateContent("", "/formStyle", -1); //aggiungo script per aggiornamento dinamico
    css += viewGeneric::dynamicUpdateContent("", "/pinStyle", -1); //aggiungo script per aggiornamento dinamico
    css += viewGeneric::dynamicUpdateContent("", "/navbarStyle", -1); //aggiungo script per aggiornamento dinamico

    html += css;

    return html;
}

String viewGeneric::defaultHeader(String title)
{
    html = "<!DOCTYPE html>";
    html += "<html>";
    html += "<head>";
    // html += "<meta http-equiv='refresh' content='5'>";//refresh automatico della pagina ogni 5 sec indesiderato!
    html += "<title>";
    html += title;
    html += "</title>";
    html += "</head>";
    html += "<body>";
    html += addNavbar();
    return html;
}

String viewGeneric::defaultFooter()
{
    html = "<br><br><br><br><br><br>";
    html += "</body>";
    html += "</html>";
    return html;
}

/*
    MetteContenutoNuovo Sotto al Contenuto vecchio
    timeToUpdate > 0 il contenuto nuovo deve essere messo AL posto di quello vecchio alrimenti sotto 

    String divId: stringa dell elemento univoco da sostituira con il nuovo contenuto se timeToUpdate > 0
                  se timeToUpdate < 0 non serve e non verra considerata 
*/
String viewGeneric::dynamicUpdateContent(String divId/*una stringa univoca nella pagina*/, String api, int timeToUpdate /* - 1 per dire refresh automatico disattivato altrimenti millisecondi dopo i quali fare refresh*/)
{
    String var_html = "";
    var_html += R"(
    <script> 
        // Esegue il caricamento iniziale
        try {
            loadPageContent(')" + api + R"(', ')" + divId + R"(', )" + String(timeToUpdate) + R"();
        } catch (error) {
            console.error('Errore durante il caricamento:', error);
        }
    </script>
    )";
    return var_html;
}


String viewGeneric::fetchContentScript()
{
    // JavaScript super minimale
    String script = R"(<script>async function fetchContent(a){try{const r=await fetch(a);return r.ok?await r.text():null}catch(e){console.error(e);return null}}</script>)";
    return script;
}

String viewGeneric::addExportCSVScript()
{
    // Script CSV minimalista
    String script = R"(<script>function exportToCSV(f,t){const tb=document.getElementById(t);if(!tb)return;let c=[],rs=tb.querySelectorAll('tr');for(let i=0;i<rs.length;i++){const r=[],cs=rs[i].querySelectorAll('td,th');for(let j=0;j<cs.length;j++){const inp=cs[j].querySelector('input[type="text"]');let txt=inp?inp.value:cs[j].innerText;txt=txt.replace(/"/g,'""');if(txt.search(/("|,|\n)/g)>=0)txt='"'+txt+'"';r.push(txt)}c.push(r.join(','))}const cf=new Blob([c.join('\n')],{type:'text/csv'}),dl=document.createElement('a');dl.download=f;dl.href=window.URL.createObjectURL(cf);dl.style.display='none';document.body.appendChild(dl);dl.click();document.body.removeChild(dl)}</script>)";
    return script;
}

String viewGeneric::dynamicUpdateContentScript()
{
    // JavaScript essenziale per dynamic update
    String script = fetchContentScript();
    script += R"(<script>let ci=0;function updateContent(d,c,r){if(r){const ed=document.getElementById(d);if(ed)ed.innerHTML=c}else{const nd=document.createElement('div');nd.id='contentAdd_'+(ci++);nd.innerHTML=c;document.body.appendChild(nd)}}async function loadPageContent(a,d,t){const c=await fetchContent(a);if(c)updateContent(d,c,t>0);if(t>0)setInterval(async()=>{const rc=await fetchContent(a);if(rc)updateContent(d,rc,true)},t)}</script>)";
    return script;
}

String viewGeneric::addAutoRefreshControlScript()
{
    // 🔧 Script ottimizzato per controllo auto-refresh con focus/blur
    String script = R"(<script>
window.AutoRefreshManager = {
    intervals: [],
    isPaused: false,
    init: function() {
        // Event listeners globali per tutti gli input fields
        document.addEventListener('focusin', (e) => {
            if (e.target.matches('input[type="text"], input[type="number"], textarea, select')) {
                this.pauseAll();
            }
        });
        document.addEventListener('focusout', (e) => {
            if (e.target.matches('input[type="text"], input[type="number"], textarea, select')) {
                this.resumeAll();
            }
        });
    },
    addInterval: function(intervalId) {
        this.intervals.push(intervalId);
    },
    pauseAll: function() {
        if (!this.isPaused) {
            this.isPaused = true;
            this.intervals.forEach(id => clearInterval(id));
            console.log('🔴 Auto-refresh paused (input focus)');
        }
    },
    resumeAll: function() {
        if (this.isPaused) {
            this.isPaused = false;
            // Riavvia tutti gli interval registrati
            window.location.reload(); // Soluzione semplice e robusta
            console.log('🟢 Auto-refresh resumed (input blur)');
        }
    }
};
// Inizializza quando il DOM è pronto
document.addEventListener('DOMContentLoaded', () => {
    window.AutoRefreshManager.init();
});
</script>)";
    return script;
}



