#include "viewEditPin.h"

String viewEditPin::html = "";
Pin *viewEditPin::selectedPin = nullptr;

/********************************************************************************
 * il pin che viene passato deve essere un pin valido ovvero precedentemente    *
 *  aggiunto al pinout altrimenti si prendera un defaultpin ma le modifiche     *
 * non verraanno salvate poiche non saranno piu accessibili da pinout!          *
 * ******************************************************************************/
 

String viewEditPin::generateForm( int pinNumber)
{
    String form;
    selectedPin = &SystemState::getInstance()->pinoutData->getPin(pinNumber);
    form += R"(
        <div class="form-container">
        <form id="configurePinForm" action="action_submit_button" method="get">
            <p style="text-align: center;">Configure Pin<br>
                <label for="pinNumber">Number: )" +
            String(pinNumber) + R"(;
                </label>
                <br><br><br>
            </p>
            <label for="pin">Pin Number:</label>
            <input type="text" id="pin" name="pin" value=")" +String(pinNumber) + R"("required>
            <label for="pinType">Pin Type:</label>
            <select id="pinType" name="pinType" required> )";
    String current_type = selectedPin->getType();
    for (int i = 0; i < static_cast<int>(PinType::SIZE); ++i)
    {
        String pin_type = Pin::pinTypeToString(static_cast<PinType>(i));
        form += "<option value=\"" + pin_type + "\" " + (current_type == pin_type ? "selected" : "") + ">" + pin_type + "</option>";
    }
    form += R"(
            </select>
            <label for="isInput">Is Input:</label>
            <select id="isInput" name="isInput" required onchange="showOutputValue() ">
                <option value="true" >True</option>
                <option value="false" )";
    form += (!selectedPin->getIsInput()? "selected" : "");
    form += R"(
                >False</option>
            </select>
            <div id="outputValueContainer" style="display: )" ;
    form+= (selectedPin->getIsInput() ? "none" : "block");
    form+= R"(">
                <label for="outputValue">Output Value:</label>
                <select id="outputValue" name="outputValue">
                    <option value="0">0V</option>
                    <option value="3.3" )";
    form += (selectedPin->getVoltage() != 0  ? "selected" : "");
    form += R"(
                        >3.3V</option>
                </select>
            </div>
            <label for="pinNote">Note:</label>
            <input type="text" id="pinNote" name="pinNote" value=")";
    char noteBuffer[200];
    selectedPin->getNote(noteBuffer, sizeof(noteBuffer));
    form += String(noteBuffer);
    form += R"(">
            <button type="button" onclick="applyConfig() ">Apply</button>
            <label> </label> <!-- Add a space between the two buttons -->
            <button type="button" onclick="saveConfig() ">Save</button>
        </form>
    </div>
    )";

    return form;
}

String viewEditPin::generateHTML() // codice generato solo la prima volta quando nessun registro e stato ancora selezionato!
{
    html = viewGeneric::defaultCssHeader("Edit Pin");

    html += R"(passaggio parametri non corretti! <br> 
        Devi passare il parametro Pin come se fosse un intero!
    )";

    html += viewGeneric::defaultFooter();

    return html;
}

String viewEditPin::generateHTML(int pinNumber)
{
    String script = viewEditPin::addDefaultScript();
    return viewEditPin::generateHTML(pinNumber, script);
}

String viewEditPin::generateHTML(int pinNumber, String script)
{
    // 🔥 FIX: Pagina COMPLETAMENTE STATICA - niente caricamento dinamico!
    html = "<!DOCTYPE html><html><head>";
    html += "<meta charset='UTF-8'><meta name='viewport' content='width=device-width,initial-scale=1.0'>";
    html += "<title>Edit Pin</title>";
    
    // CSS completo inline
    html += "<style>";
    html += "body{margin:0;padding:60px 10px 120px;background:#f4f4f4;font-family:Arial,sans-serif}";
    html += ".navbar{display:flex;justify-content:space-evenly;background:rgba(48,48,48,0.9);position:fixed;bottom:15px;left:50%;transform:translateX(-50%);width:80vw;padding:8px;border-radius:10px;z-index:2000}";
    html += ".navbar a{color:white;text-decoration:none;text-align:center;padding:8px}";
    html += ".navbar .icon{width:40px;height:40px;background:rgba(255,255,255,0.8);border-radius:6px;display:flex;align-items:center;justify-content:center;font-size:20px;color:#333}";
    html += ".navbar span{font-size:10px;margin-top:4px}";
    html += ".form-container{background:rgba(255,255,255,0.95);border-radius:10px;padding:20px;margin:20px auto;max-width:500px}";
    html += "form{display:flex;flex-direction:column}label{font-weight:bold;margin-bottom:5px;font-size:14px}";
    html += "input,select{margin-bottom:10px;padding:8px;border:1px solid #ccc;border-radius:4px;font-size:14px}";
    html += "button{padding:10px;background:#4CAF50;color:white;border:none;border-radius:4px;cursor:pointer;font-size:14px;margin:5px 0}";
    html += "button:hover{background:#45a049}";
    html += "@media(min-width:1500px){.navbar{flex-direction:column;top:50%;left:15px;transform:translateY(-50%);bottom:auto;width:auto;max-height:80vh}}";
    html += "</style>";
    
    html += "</head><body>";
    
    // Navbar statica
    html += "<div class='navbar'>";
    html += "<a href='/monitor'><div class='icon'>🖥️</div><span>Monitor</span></a>";
    html += "<a href='/pinout'><div class='icon'>🔌</div><span>Pinout</span></a>";
    html += "<a href='/currentregister'><div class='icon'>📋</div><span>Register</span></a>";
    html += "<a href='/pin_history'><div class='icon'>📌</div><span>Pin History</span></a>";
    html += "<a href='/modbus_history'><div class='icon'>📊</div><span>Modbus History</span></a>";
    html += "<a href='/graph'><div class='icon'>📈</div><span>Graph</span></a>";
    html += "<a href='/config'><div class='icon'>📶</div><span>WIfi Config</span></a>";
    html += "<a href='/multiplex_config'><div class='icon'>⚙️</div><span>Multiplexer</span></a>";
    html += "<a href='/ADS_history'><div class='icon'>🔢</div><span>ADS History</span></a>";
    html += "</div>";
    
    // Contenuto principale statico
    html += "<h1 style='text-align:center;margin:20px 0'>✏ Edit Pin " + String(pinNumber) + "</h1>";
    html += generateForm(pinNumber);
    
    // 🔥 JavaScript GLOBALE direttamente nell'HTML principale
    html += "<script>";
    html += "function showOutputValue(){";
    html += "const i=document.getElementById('isInput').value,";
    html += "o=document.getElementById('outputValueContainer');";
    html += "o.style.display=i==='false'?'block':'none'";
    html += "}";
    html += "function applyConfig(){";
    html += "const form=document.getElementById('configurePinForm');";
    html += "if(!form){alert('Form not found');return;}";
    html += "const formData=new FormData(form);";
    html += "const params=new URLSearchParams();";
    html += "for(let[key,value] of formData.entries())params.append(key,value);";
    html += "window.location.href='/applyPin?'+params.toString();";
    html += "}";
    html += "function saveConfig(){";
    html += "const form=document.getElementById('configurePinForm');";
    html += "if(!form){alert('Form not found');return;}";
    html += "const formData=new FormData(form);";
    html += "const params=new URLSearchParams();";
    html += "for(let[key,value] of formData.entries())params.append(key,value);";
    html += "window.location.href='/savePin?'+params.toString();";
    html += "}";
    html += "function showPopup(msg){";
    html += "const popup=document.createElement('div');";
    html += "popup.style.cssText='position:fixed;top:20px;right:20px;background:#4CAF50;color:white;padding:15px;border-radius:5px;z-index:1000';";
    html += "popup.textContent=msg;";
    html += "document.body.appendChild(popup);";
    html += "setTimeout(()=>popup.remove(),3000)";
    html += "}";
    
    // 🔥 Controlla se c'è il parametro applied nell'URL per mostrare popup
    html += "if(window.location.href.includes('applied=true')){";
    html += "setTimeout(function(){showPopup('✅ Pin " + String(pinNumber) + " applicato con successo!')},500);";
    html += "}";
    
    html += "</script>";
    html += "</body></html>";
    
    return html;
}

String viewEditPin::addCustomScript(String script)
{
    return script;
}

String viewEditPin::addDefaultScript(){
    // Script corretto per Apply e Save con funzionamento completo
    return "<script>"
           "function showOutputValue(){"
           "const i=document.getElementById('isInput').value,"
           "o=document.getElementById('outputValueContainer');"
           "o.style.display=i==='false'?'block':'none'"
           "}"
           "function applyConfig(){"
           "const form=document.getElementById('configurePinForm');"
           "if(!form){alert('Form not found');return;}"
           // Apply: invia dati a /applyPin (rimane su editPin)
           "const formData=new FormData(form);"
           "const params=new URLSearchParams();"
           "for(let[key,value] of formData.entries())params.append(key,value);"
           "window.location.href='/applyPin?'+params.toString();"
           "}"
           "function saveConfig(){"
           "const form=document.getElementById('configurePinForm');"
           "if(!form){alert('Form not found');return;}"
           // Save: invia dati a /savePin (torna a pinout)
           "const formData=new FormData(form);"
           "const params=new URLSearchParams();"
           "for(let[key,value] of formData.entries())params.append(key,value);"
           "window.location.href='/savePin?'+params.toString();"
           "}"
           "function showPopup(msg){"
           "const popup=document.createElement('div');"
           "popup.style.cssText='position:fixed;top:20px;right:20px;background:#4CAF50;color:white;padding:15px;border-radius:5px;z-index:1000';"
           "popup.textContent=msg;"
           "document.body.appendChild(popup);"
           "setTimeout(()=>popup.remove(),3000)"
           "}"
           "</script>";
}