#include "viewGraph.h"
#include <set> 

String viewGraph::html = "";
String viewGraph::generateHTML()
{
    html = "<!DOCTYPE html><html><head>";
    html += "<meta charset='UTF-8'><meta name='viewport' content='width=device-width,initial-scale=1.0'>";
    html += "<title>Graph View</title>";
    html += "<style>";
    html += viewGeneric::addCss();
    html += viewGeneric::addFormCss();
    html += viewGeneric::addNavbarCss();
    html += "</style>";
    html += "</head><body>";
    
    // Navbar sempre presente
    html += viewGeneric::addNavbar();

    html += "<h1>Graph View</h1>";

    html += "<h2>Registri:</h2>";
    std::vector<int> addresses = SystemState::getInstance()->getAllRegisterAddress();
    int i = 0;
    for (int addr : addresses)
    {
        addresses[i] += 1000; //operazione di shift
    }
    
    String apiFetch = "getRegisterValues";
    String apiFetchParam = "address";

    html += generateGraph(addresses, apiFetch, apiFetchParam);

    html += viewGeneric::defaultFooter();

    return html;
}


String viewGraph::generateGraph(std::vector<int> addresses, String apiFetch, String apiFetchParam)
{
    String var_html = "";
    
    // Pre-calculate total size needed to avoid multiple reallocations
    size_t estimated_size = 2048 + (addresses.size() * 50); // Base size + selector options
    var_html.reserve(estimated_size);

    // Creo il contenitore del grafico con dimensioni responsive
    var_html += "<div id='graphWrapper' style='width: 100%; height: 100%; min-height: 400px; position: relative; padding: 20px; box-sizing: border-box;'>";

    // Only show the selector if there are multiple addresses
    if (addresses.size() > 1) {
        var_html += generateSelectorHTML(addresses);
    }
    
    // Aggiungo bottone export CSV per i grafici
    var_html += "<div style='text-align: center; margin: 10px 0;'>";
    var_html += "<button onclick=\"exportCurrentGraphData()\" style='background-color: #2196F3; color: white; padding: 8px 16px; border: none; border-radius: 5px; cursor: pointer; font-size: 14px;'>📊 Export Graph CSV</button>";
    var_html += "</div>";

    // Canvas responsive all'interno del contenitore
    var_html += "<canvas id='myChart' style='width: 100%; height: 100%; display: block; border: 1px solid #ddd; border-radius: 8px;'></canvas>";

    var_html += "</div>";

    // JavaScript diviso in parti più piccole per ridurre l'uso di memoria
    var_html += generateBasicJavaScript();
    var_html += generateDrawFunctionJS();
    var_html += generateUpdateFunctionJS(apiFetch, apiFetchParam);
    var_html += generateGraphExportJS(apiFetch, apiFetchParam);
    var_html += generateInitializationJS();

    return var_html;
}

String viewGraph::generateSelectorHTML(std::vector<int> addresses)
{
    String html = "";
    html.reserve(512);
    
    html += "<div style='margin-bottom: 10px; text-align: center;'>";
    html += "<label for='register-select' style='font-weight: bold; margin-right: 8px; font-size: 14px;'>Seleziona:</label>";
    html += "<select id='register-select' onchange='updateGraph()' style='padding: 4px 8px; border: 1px solid #ccc; border-radius: 4px; font-size: 14px;'>";

    std::set<int> seen;
    for (int addr : addresses)
    {
        if (seen.find(addr) != seen.end()) {
            continue;
        }
        seen.insert(addr);

        if (addr > 0 && addr < 1000) {
            html += "<option value='" + String(addr) + "'>" + String(addr) + "</option>";
        } else if (addr <= 0) {
            html += "<option value='" + String(addr) + "'>Multiplex:" + String(-addr) + "</option>";
        } else if (addr >= 1000 && addr < 2000) {
            html += "<option value='" + String(addr - 1000) + "'>ModbusValue:" + String(addr - 1000) + "</option>";
        } else if (addr == 999) {
            html += "<option value='999'>🧪 TEST Mode</option>";
        } else {
            //caso di scritture non valide non le inserisco
            //html += "<option value='" + String(addr) + "'>Errore inserimento!" + String(addr - 3000) + "</option>";
        }
    }

    html += "</select></div>";
    return html;
}

String viewGraph::generateBasicJavaScript()
{
    return "<script>let chartData=[];</script>";
}

String viewGraph::generateDrawFunctionJS()
{
    // JavaScript super compresso per il grafico
    String js = R"(<script>function resizeCanvas(){const c=document.getElementById('myChart');if(c&&c.parentElement){const r=c.parentElement.getBoundingClientRect();c.width=r.width-40;c.height=r.height-40;if(chartData.length>0)drawChart(c,chartData)}}function drawChart(c,d){const ctx=c.getContext('2d'),w=c.width,h=c.height,p=40,cw=w-2*p,ch=h-2*p;ctx.clearRect(0,0,w,h);if(d.length===0){ctx.fillStyle='#666';ctx.font='14px Arial';ctx.textAlign='center';ctx.fillText('No data',w/2,h/2);return}const min=Math.min(...d),max=Math.max(...d),range=max-min||1;ctx.strokeStyle='#f0f0f0';ctx.lineWidth=1;for(let i=0;i<=5;i++){const y=p+(ch*i/5);ctx.beginPath();ctx.moveTo(p,y);ctx.lineTo(w-p,y);ctx.stroke()}ctx.strokeStyle='#333';ctx.lineWidth=2;ctx.beginPath();ctx.moveTo(p,p);ctx.lineTo(p,h-p);ctx.lineTo(w-p,h-p);ctx.stroke();ctx.fillStyle='#333';ctx.font='11px Arial';ctx.textAlign='right';for(let i=0;i<=5;i++){const v=min+(range*i/5),y=h-p-(ch*i/5);ctx.fillText(v.toFixed(1),p-5,y+3)}ctx.strokeStyle='#4CAF50';ctx.lineWidth=2;ctx.beginPath();const sx=cw/Math.max(d.length-1,1);for(let i=0;i<d.length;i++){const x=p+(sx*i),nv=(d[i]-min)/range,y=h-p-(ch*nv);if(i===0)ctx.moveTo(x,y);else ctx.lineTo(x,y)}ctx.stroke();if(d.length<=30){ctx.fillStyle='#2196F3';for(let i=0;i<d.length;i++){const x=p+(sx*i),nv=(d[i]-min)/range,y=h-p-(ch*nv);ctx.beginPath();ctx.arc(x,y,2,0,2*Math.PI);ctx.fill()}}if(d.length>0){const lv=d[d.length-1];ctx.fillStyle='#2196F3';ctx.font='bold 12px Arial';ctx.textAlign='left';ctx.fillText('Last: '+lv.toFixed(2),p,20)}}</script>)";
    return js;
}

String viewGraph::generateUpdateFunctionJS(String apiFetch, String apiFetchParam)
{
    // JavaScript update minimalista
    String js = R"(<script>function updateGraph(){const s=document.getElementById('register-select'),a=s?s.value:0;fetch(')" + apiFetch + "?" + apiFetchParam + R"(='+a).then(r=>r.json()).then(d=>{chartData=d;const c=document.getElementById('myChart');if(c)drawChart(c,d)}).catch(e=>{console.error(e);const c=document.getElementById('myChart');if(c){const ctx=c.getContext('2d');ctx.clearRect(0,0,c.width,c.height);ctx.fillStyle='#f44336';ctx.font='14px Arial';ctx.textAlign='center';ctx.fillText('Load Error',c.width/2,c.height/2)}})}</script>)";
    return js;
}

String viewGraph::generateGraphExportJS(String apiFetch, String apiFetchParam)
{
    // Export minimalista
    String js = R"(<script>function exportCurrentGraphData(){const s=document.getElementById('register-select'),a=s?s.value:0;fetch(')" + apiFetch + "?" + apiFetchParam + R"(='+a).then(r=>r.json()).then(d=>{if(d.length===0){alert('No data');return}let csv='Index,Value\n';d.forEach((v,i)=>{csv+=i+','+v+'\n'});const cf=new Blob([csv],{type:'text/csv'}),dl=document.createElement('a');dl.download='graph_data_'+a+'.csv';dl.href=window.URL.createObjectURL(cf);dl.style.display='none';document.body.appendChild(dl);dl.click();document.body.removeChild(dl)}).catch(e=>console.error(e))}</script>)";
    return js;
}

String viewGraph::generateInitializationJS()
{
    // Inizializzazione minimalista
    String js = R"(<script>document.addEventListener('DOMContentLoaded',function(){requestAnimationFrame(()=>{resizeCanvas();updateGraph();setInterval(updateGraph,10000);window.addEventListener('resize',()=>{setTimeout(resizeCanvas,100)})})});</script>)";
    return js;
}

String viewGraph::initCirularProgressBarGraph()
{
    String html = "";
    html += "<div style='display:flex;flex-wrap:wrap;gap:20px;padding:20px;'>";
    
    // JavaScript ultra-compatto - funzioni globali una sola volta
    html += "<script>";
    html += "if(!window.cp){";
    html += "window.cp={";
    html += "d:function(c,p){";
    html += "const x=c.getContext('2d'),w=c.width,h=c.height,cx=w/2,cy=h/2,r=70;";
    html += "x.clearRect(0,0,w,h);";
    html += "x.beginPath();x.arc(cx,cy,r,0,2*Math.PI);x.lineWidth=15;x.strokeStyle='#ddd';x.stroke();";
    html += "if(p>0){";
    html += "const s=-Math.PI/2,e=s+(2*Math.PI*p/100);";
    html += "x.beginPath();x.arc(cx,cy,r,s,e);x.lineWidth=15;x.strokeStyle='#4caf50';x.lineCap='round';x.stroke()";
    html += "}},";
    html += "u:function(a,c,l){";
    html += "fetch(a).then(r=>r.json()).then(d=>{";
    html += "let p=0,u=0,t=0;";
    html += "if(d&&d.heap){u=d.heap.used||0;t=d.heap.total||0}";
    html += "else if(d&&d.used!==undefined){u=d.used||0;t=d.total||0}";
    html += "if(t>0)p=Math.max(0,Math.min(100,(u/t)*100));";
    html += "const cv=document.getElementById(c);if(cv)window.cp.d(cv,p);";
    html += "const lb=document.getElementById(l);if(lb)lb.innerText=p.toFixed(1)+'%'";
    html += "}).catch(e=>{";
    html += "const cv=document.getElementById(c);if(cv)window.cp.d(cv,0);";
    html += "const lb=document.getElementById(l);if(lb)lb.innerText='0%'";
    html += "})";
    html += "}}}";
    html += "</script>";
    
    return html;
}

String viewGraph::endCirularProgressBarGraph()
{
    return "</div>";
}

String viewGraph::generateCirularProgressBarGraph(String circle_progressbar_label, float circle_progressbar_used_value, float circle_progressbar_total_value, String apiFetchData, int timeToUpdate)
{
    float p = (circle_progressbar_total_value > 0) ? (circle_progressbar_used_value / circle_progressbar_total_value) * 100 : 0;
    
    String html = "";
    html += "<div style='display:flex;flex-direction:column;align-items:center;width:45%;max-width:300px;min-width:150px;position:relative;'>";
    html += "<div style='font-size:1.2rem;margin-bottom:10px;'>" + circle_progressbar_label + "</div>";
    html += "<canvas id='c" + circle_progressbar_label + "' width='200' height='200' style='width:200px;height:200px;'></canvas>";
    html += "<div id='l" + circle_progressbar_label + "' style='position:absolute;top:50%;left:50%;transform:translate(-50%,-50%);font-size:2rem;font-weight:bold;'>" + String((int)p) + "%</div>";
    html += "<div style='font-size:1rem;margin-top:10px;'>Uso:" + String(circle_progressbar_used_value, 1) + "/" + String(circle_progressbar_total_value, 1) + "</div>";
    html += "</div>";
    
    html += "<script>";
    html += "document.addEventListener('DOMContentLoaded',function(){";
    html += "const c=document.getElementById('c" + circle_progressbar_label + "');";
    html += "if(c&&window.cp)window.cp.d(c," + String(p, 1) + ");";
    if (timeToUpdate > 0) {
        html += "setInterval(function(){if(window.cp)window.cp.u('" + apiFetchData + "','c" + circle_progressbar_label + "','l" + circle_progressbar_label + "');}," + String(timeToUpdate) + ");";
    }
    html += "});";
    html += "</script>";
    
    return html;
}

String viewGraph::generateCirularProgressBarGraph(String circle_progressbar_label, float circle_progressbar_used_value, float circle_progressbar_total_value)
{
    float p = (circle_progressbar_total_value > 0) ? (circle_progressbar_used_value / circle_progressbar_total_value) * 100 : 0;
    
    String html = "";
    html += "<div style='display:flex;flex-direction:column;align-items:center;width:45%;max-width:300px;min-width:150px;position:relative;'>";
    html += "<div style='font-size:1.2rem;margin-bottom:10px;'>" + circle_progressbar_label + "</div>";
    html += "<canvas id='c" + circle_progressbar_label + "' width='200' height='200' style='width:200px;height:200px;'></canvas>";
    html += "<div id='l" + circle_progressbar_label + "' style='position:absolute;top:50%;left:50%;transform:translate(-50%,-50%);font-size:2rem;font-weight:bold;'>" + String((int)p) + "%</div>";
    html += "<div style='font-size:1rem;margin-top:10px;'>Uso:" + String(circle_progressbar_used_value, 1) + "/" + String(circle_progressbar_total_value, 1) + "</div>";
    html += "</div>";
    
    html += "<script>";
    html += "document.addEventListener('DOMContentLoaded',function(){";
    html += "const c=document.getElementById('c" + circle_progressbar_label + "');";
    html += "if(c&&window.cp)window.cp.d(c," + String(p, 1) + ");";
    html += "});";
    html += "</script>";

    return html;
}

