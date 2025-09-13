#include "viewMultiplex.h"
#include "SystemState.h"


String viewMultiplex::Config(){
    String html = "";
    html = viewGeneric::basicHeader("Multiplex ConfigPage");
    html += viewGeneric::dynamicUpdateContentScript(); //aggiungo script per aggiornamento dinamico
    html += viewGeneric::dynamicUpdateContent("id_navbarStyle", "/navbarStyle", -1); //aggiungo script per aggiornamento dinamico
    html += viewGeneric::dynamicUpdateContent("id_fieldFormStyle", "/fieldFormStyle", -1);
    String page_content = "";
    page_content += viewGeneric::addNavbar();

    page_content += viewMultiplex::pageContent();
    
    page_content += viewGeneric::defaultFooter();

    return html+page_content;
}


String viewMultiplex::pageContent(){

    String content = R"rawliteral(
        <!-- Contenitore principale del form -->
        <div class="form-container">
            <h2>Configurazione Sistema</h2>
            <form id="configForm" action="multiplex_graph" method="get">
            
                <!-- Sezione: Seleziona il tipo di segnale -->
                <fieldset>
                    <legend>Seleziona il tipo di segnale</legend>
                    <label for="signalType">Tipo di segnale:</label>
                    <select id="signalType" name="signalType" onchange="updateSignalMessage()">
                        <option value="resistenza">Resistenza CN2 [Ohm]</option>
                        <option value="tensione_non_amplificato">Corrente CN2 [mA]</option>
                        <option value="tensione_amp_331">ADS RAW Voltage con CH mux = 2</option>
                        <option value="tensione_amp_0.216">Tensione CN2[&micro;V]</option>
                        <option value="termocoppia_cn2">Termocoppia K CN2</option>
                        <option value="PT100_cn2">PT100 CN2</option>
                        <option value="PT1000_cn2">PT1000 CN2</option>


                        <option value="CN10_resistenza">Resistenza CN10</option>
                        <option value="CN10_tensione_non_amplificato">Corrente CN10 [mA]</option>
                        <option value="CN10_tensione_amp_331">ADS RAW Voltage con CH mux = 6</option>
                        <option value="CN10_tensione_amp_0.216">Tensione CN10 [&micro;V]</option>
                        <option value="termocoppia_cn10">Termocoppia K CN10</option>
                        <option value="PT100_cn10">PT100 CN10</option>
                        <option value="PT1000_cn10">PT1000 CN10</option>
                        
                        <option value="TEST">🧪 TEST - Simulazione valori casuali</option>

                    </select>
                </fieldset>
                
                <!-- Messaggio che compare in base alla selezione -->
                <div id="signalMessage" style="margin: 20px 0; font-weight: bold;"></div>
                
                <!-- Pulsante di invio -->
                <button type="submit">Invia Configurazione</button>
            </form>
        </div>
        
        <script>
            function updateSignalMessage() {
                var signalType = document.getElementById("signalType").value;
                var messageDiv = document.getElementById("signalMessage");
                        
                switch (signalType) {
                    case "resistenza":
                        messageDiv.textContent = "La resistenza PT100 la devi collegare tra il morsetto 8 e il morsetto 2 della morsettiera CN2.";
                        break;
                    case "tensione_non_amplificato":
                        messageDiv.textContent = "Devi collegare segnale al morsetto 7 della morsettiera CN2.";
                        break;
                    case "tensione_amp_331":
                        messageDiv.textContent = "Collegare al morsetto 6 della morsettiera CN2: max signal readed +5v, -5v.";
                        break;
                    case "tensione_amp_0.216":
                        messageDiv.textContent = "Collegare al morsetto 1 dekka morsettiera CN2.";
                        break;
                    case "CN10_resistenza":
                        messageDiv.textContent = "La resistenza PT100 la devi collegare tra il morsetto 8 e il morsetto 2 della morsettiera CN10.";
                        break;
                    case "CN10_tensione_non_amplificato":
                        messageDiv.textContent = "Devi collegare segnale al morsetto 7 della morsettiera CN10.";
                        break;
                    case "CN10_tensione_amp_331":
                        messageDiv.textContent = "Collegare al morsetto 6 della morsettiera CN10: max signal readed +5v, -5v.";
                        break;
                    case "CN10_tensione_amp_0.216":
                        messageDiv.textContent = "Collegare al morsetto 1 dekka morsettiera CN10.";
                        break;
                    case "TEST":
                        messageDiv.textContent = "🧪 Modalità TEST: Simulazione con valori casuali per testare l'interfaccia senza hardware ADS1115.";
                        messageDiv.style.color = "#FF9800";
                        messageDiv.style.fontWeight = "bold";
                        break;
                    default:
                        messageDiv.textContent = "";
                        messageDiv.style.color = "";
                        messageDiv.style.fontWeight = "";
                }
            }
            
            document.addEventListener("DOMContentLoaded", function() {
                updateSignalMessage();
            });
        </script>
        )rawliteral";
        
    return content;
}

/*Devo ancora modificare grafico, se prende in input un determinato numero di pin non mostra tutto menu a tendina ma fa diverso! solo signaltype!*/
String viewMultiplex::  pinStartAndStopForm(int channelAdsNumber, String signalType){
    String form = "";

    // Include CSS classes
    form += cssToggleButton::getCSS();
    form += cssMultiplexLayout::getCSS();
    form += cssStatusIndicator::getCSS();
    form += cssControlGroup::getCSS();
    
    form += R"rawliteral(
        <div class="desktop-multiplex-layout">
            <!-- Header Section -->
            <div class="multiplex-header">
                <h2 style="margin: 0; color: #333;">Multiplex Graph - )rawliteral" + signalType + R"rawliteral(</h2>
            </div>
            
            <!-- Controls Section -->
            <div class="multiplex-controls">
                <div class="control-group">
                    <label>Registra:</label>
                    <label class="ios-toggle-switch">
                        <input type="checkbox" id="recordingToggle" onchange="toggleRecording(')rawliteral" + signalType + R"rawliteral(')">
                        <span class="ios-toggle-slider"></span>
                    </label>
                </div>
                
                <div class="control-group">
                    <label for="milliseconds">Intervallo:</label>
                    <input type="number" id="milliseconds" name="milliseconds" value="1000" min="100" max="10000">
                    <span class="unit-label">ms</span>
                </div>
                
                <div class="control-group">
                    <label>Monitor:</label>
                    <label class="ios-toggle-switch">
                        <input type="checkbox" id="monitorToggle" onchange="toggleMonitor(')rawliteral" + signalType + R"rawliteral(')">
                        <span class="ios-toggle-slider"></span>
                    </label>
                </div>
                
                <div class="control-group">
                    <label for="exit_type">Uscita:</label>
                    <select id="exit_type" name="out_pin_number">
                        <option value="25">Pin 25 (Digitale)</option>
                        <option value="26">Pin 26 (Analogico)</option>    
                    </select>
                </div>
                
                <div class="control-group">
                    <label>Allarme:</label>
                    <label class="ios-toggle-switch">
                        <input type="checkbox" id="alertToggle" onchange="toggleAlert(')rawliteral" + signalType + R"rawliteral(')">
                        <span class="ios-toggle-slider"></span>
                    </label>
                </div>
                
                <div class="control-group">
                    <label for="alert_value">Soglia:</label>
                    <input type="number" id="alert_value" name="alert_value" value="0" step="0.1">
                </div>
                
                <div class="control-group">
                    <label for="alert_exit_type">Uscita Allarme:</label>
                    <select id="alert_exit_type" name="alert_out_pin_number">
                        <option value="25">Pin 25 (Digitale)</option>
                        <option value="26">Pin 26 (Analogico)</option>    
                    </select>
                </div>
                
                <!-- Status Indicator -->
                <div id="status" class="status-indicator" style="position: static; margin-top: 15px; text-align: center;">
                    Pronto per uso
                </div>
            </div>
            
            <!-- Graph Section -->
            <div class="multiplex-graph">
                <div class="graph-header">
                    <h3 style="margin: 0; color: #333;">Grafico in Tempo Reale</h3>
                    <!-- Aggiungo bottone export CSV per multiplex -->
                    <button onclick=\"exportGraphDataToCSV('multiplex_data.csv', '/getADSValues', '')\" style='background-color: #2196F3; color: white; padding: 6px 12px; border: none; border-radius: 4px; cursor: pointer; font-size: 12px; margin-left: 10px;'>📊 Export CSV</button>
                </div>
                <div class="graph-container">
                    <!-- Real-time value display -->
                    <div id="realtimeValue" class="realtime-value">
                        -- --
                    </div>
                    <div id="graphContainer" style="width: 100%; height: 100%;">
                    </div>
                </div>
            </div>
        </div>
        
        <script>
            let recordingActive = false;
            let monitoringActive = false;
            let alertActive = false;
            let currentValue = 0;
            let updateInterval = null;
            
            // Function to update real-time value
            function updateRealtimeValue() {
                fetch('/getMultiplexValue?signalType=)rawliteral" + signalType + R"rawliteral(')
                    .then(response => {
                        if (!response.ok) {
                            throw new Error('ADS1115 not available');
                        }
                        return response.json();
                    })
                    .then(data => {
                        if (data.error) {
                            document.getElementById('realtimeValue').textContent = 'ADS Error';
                            document.getElementById('realtimeValue').style.color = '#f44336';
                            return;
                        }
                        currentValue = data.value || 0;
                        const unit = getSignalUnit(')rawliteral" + signalType + R"rawliteral(');
                        const displayElement = document.getElementById('realtimeValue');
                        displayElement.textContent = currentValue.toFixed(2) + ' ' + unit;
                        displayElement.style.color = '#2196F3';
                    })
                    .catch(error => {
                        console.error('Error fetching realtime value:', error);
                        const displayElement = document.getElementById('realtimeValue');
                        displayElement.textContent = 'ADS Error';
                        displayElement.style.color = '#f44336';
                    });
            }
            
            // Function to get signal unit
            function getSignalUnit(signalType) {
                const units = {
                    'resistenza': 'Ω',
                    'tensione_non_amplificato': 'mA',
                    'tensione_amp_331': 'V',
                    'tensione_amp_0.216': 'μV',
                    'termocoppia_cn2': '°C',
                    'termocoppia_cn10': '°C',
                    'PT100_cn2': '°C',
                    'PT100_cn10': '°C',
                    'PT1000_cn2': '°C',
                    'PT1000_cn10': '°C',
                    'CN10_resistenza': 'Ω',
                    'CN10_tensione_non_amplificato': 'mA',
                    'CN10_tensione_amp_331': 'V',
                    'CN10_tensione_amp_0.216': 'μV',
                    'TEST': '🧪'
                };
                return units[signalType] || '';
            }
            
            function toggleRecording(signalType) {
                const toggle = document.getElementById('recordingToggle');
                const milliseconds = document.getElementById('milliseconds').value;
                const status = document.getElementById('status');
                
                if (toggle.checked) {
                    recordingActive = true;
                    fetch(`/multiplex_graph?signalType=${signalType}&milliseconds=${milliseconds}&action=start_recording`)
                        .then(response => response.text())
                        .then(data => {
                            status.textContent = 'Registrazione attiva';
                            status.className = 'status-indicator success';
                        })
                        .catch(error => {
                            console.error('Error:', error);
                            toggle.checked = false;
                            recordingActive = false;
                            status.textContent = 'Errore nella registrazione';
                            status.className = 'status-indicator error';
                        });
                } else {
                    recordingActive = false;
                    fetch(`/multiplex_graph?signalType=${signalType}&action=stop_recording`)
                        .then(response => response.text())
                        .then(data => {
                            status.textContent = 'Registrazione fermata';
                            status.className = 'status-indicator default';
                        });
                }
            }
            
            function toggleMonitor(signalType) {
                const toggle = document.getElementById('monitorToggle');
                const outPin = document.getElementById('exit_type').value;
                const status = document.getElementById('status');
                
                if (toggle.checked) {
                    monitoringActive = true;
                    fetch(`/multiplex_graph?signalType=${signalType}&out_pin_number=${outPin}&action=start_monitor`)
                        .then(response => response.text())
                        .then(data => {
                            status.textContent = 'Monitoraggio attivo';
                            status.className = 'status-indicator info';
                        });
                } else {
                    monitoringActive = false;
                    fetch(`/multiplex_graph?signalType=${signalType}&action=stop_monitor`)
                        .then(response => response.text())
                        .then(data => {
                            status.textContent = 'Monitoraggio fermato';
                            status.className = 'status-indicator default';
                        });
                }
            }
            
            function toggleAlert(signalType) {
                const toggle = document.getElementById('alertToggle');
                const alertValue = document.getElementById('alert_value').value;
                const outPin = document.getElementById('alert_exit_type').value;
                const status = document.getElementById('status');
                
                if (toggle.checked) {
                    alertActive = true;
                    fetch(`/multiplex_graph?signalType=${signalType}&alert_value=${alertValue}&out_pin_number=${outPin}&action=start_monitor_alert`)
                        .then(response => response.text())
                        .then(data => {
                            status.textContent = 'Allarme attivo';
                            status.className = 'status-indicator warning';
                        });
                } else {
                    alertActive = false;
                    fetch(`/multiplex_graph?signalType=${signalType}&action=stop_monitor_alert`)
                        .then(response => response.text())
                        .then(data => {
                            status.textContent = 'Allarme fermato';
                            status.className = 'status-indicator default';
                        });
                }
            }
            
            // Initialize page
            document.addEventListener('DOMContentLoaded', function() {
                // Start updating real-time value every second
                updateRealtimeValue();
                updateInterval = setInterval(updateRealtimeValue, 1000);
                
                // Initialize graph if needed
                // Add your graph initialization code here
            });
            
            // Cleanup on page unload
            window.addEventListener('beforeunload', function() {
                if (updateInterval) {
                    clearInterval(updateInterval);
                }
            });
        </script>
    )rawliteral";

    return form;
}