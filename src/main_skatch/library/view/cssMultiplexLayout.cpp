#include "cssMultiplexLayout.h"

String cssMultiplexLayout::getCSS() {
    return R"(
        <style>
            /* Desktop Layout - Horizontal split */
            @media (min-width: 1024px) {
                .desktop-multiplex-layout {
                    display: grid;
                    grid-template-columns: 300px 1fr;
                    grid-template-rows: auto 1fr;
                    gap: 5px;  /* Ridotto da 10px a 5px */
                    height: 80vh;  /* Ridotto da 100vh a 80vh per fare spazio alla navbar */
                    width: 80vw;  /* Ridotto da 100vw a 80vw per margini laterali */
                    padding: 4px;  /* Ridotto da 8px a 4px */
                    box-sizing: border-box;
                    overflow: hidden;
                    margin: 0 auto;  /* Centrato orizzontalmente */
                    margin-top: 20px;  /* Margine superiore per distanza dalla header */
                }
                
                .multiplex-header {
                    grid-column: 1 / -1;
                    flex-shrink: 0;
                    padding: 4px;  /* Ridotto da 6px a 4px */
                    background: #f8f9fa;
                    border-radius: 6px;
                    text-align: center;
                }
                
                .multiplex-controls {
                    grid-column: 1;
                    display: flex;
                    flex-direction: column;
                    gap: 6px;  /* Ridotto da 8px a 6px */
                    padding: 8px;  /* Ridotto da 12px a 8px */
                    background: white;
                    border: 1px solid #ddd;
                    border-radius: 8px;
                    overflow-y: auto;
                    max-height: calc(100vh - 100px);
                }
                
                .multiplex-graph {
                    grid-column: 2;
                    display: flex;
                    flex-direction: column;
                    min-height: 0;
                    background: white;
                    border: 1px solid #ddd;
                    border-radius: 8px;
                    padding: 2px;  /* Ridotto drasticamente da 10px a 2px */
                }
                
                .graph-header {
                    flex-shrink: 0;
                    text-align: center;
                    margin-bottom: 2px;  /* Ridotto da 8px a 2px */
                    font-size: 14px;
                }
                
                .graph-container {
                    flex: 1;
                    min-height: 0;
                    position: relative;
                    width: 100%;
                    height: 100%;
                    padding: 0;  /* Aggiunto padding: 0 */
                }
                
                .realtime-value {
                    position: absolute;
                    top: 5px;  /* Ridotto da 10px a 5px */
                    right: 5px;  /* Ridotto da 10px a 5px */
                    background: rgba(255, 255, 255, 0.9);
                    border: 2px solid #2196F3;
                    border-radius: 6px;  /* Ridotto da 8px a 6px */
                    padding: 4px 6px;  /* Ridotto da 6px 10px a 4px 6px */
                    font-weight: bold;
                    font-size: 12px;  /* Ridotto da 14px a 12px */
                    color: #2196F3;
                    z-index: 100;
                    box-shadow: 0 2px 8px rgba(0,0,0,0.1);
                }
                
                #myChart {
                    width: 100% !important;
                    height: 100% !important;
                    min-height: 250px;
                    border: 1px solid #ccc;
                    border-radius: 4px;
                    margin: 0 !important;  /* Aggiunto margin: 0 */
                    padding: 0 !important;  /* Aggiunto padding: 0 */
                }
            }
            
            /* Mobile Layout - Vertical with iOS toggles */
            @media (max-width: 1023px) {
                .desktop-multiplex-layout {
                    display: flex;
                    flex-direction: column;
                    height: 100vh;
                    padding: 4px;  /* Ridotto da 8px a 4px */
                    box-sizing: border-box;
                    overflow: hidden;
                }
                
                .multiplex-header {
                    flex-shrink: 0;
                    padding: 4px;  /* Ridotto da 6px a 4px */
                    background: #f8f9fa;
                    border-radius: 6px;
                    text-align: center;
                    margin-bottom: 4px;  /* Ridotto da 8px a 4px */
                }
                
                .multiplex-controls {
                    flex-shrink: 0;
                    display: flex;
                    flex-direction: column;
                    gap: 6px;  /* Ridotto da 8px a 6px */
                    padding: 6px;  /* Ridotto da 10px a 6px */
                    background: white;
                    border: 1px solid #ddd;
                    border-radius: 8px;
                    margin-bottom: 4px;  /* Ridotto da 8px a 4px */
                    max-height: 200px;
                    overflow-y: auto;
                }
                
                .multiplex-graph {
                    flex: 1;
                    display: flex;
                    flex-direction: column;
                    min-height: 0;
                    background: white;
                    border: 1px solid #ddd;
                    border-radius: 8px;
                    padding: 2px;  /* Ridotto drasticamente da 8px a 2px */
                }
                
                .graph-header {
                    flex-shrink: 0;
                    text-align: center;
                    margin-bottom: 2px;  /* Ridotto da 6px a 2px */
                    font-size: 12px;
                }
                
                .graph-container {
                    flex: 1;
                    min-height: 0;
                    position: relative;
                    width: 100%;
                    height: 100%;
                    padding: 0;  /* Aggiunto padding: 0 */
                }
                
                .realtime-value {
                    position: absolute;
                    top: 3px;  /* Ridotto da 5px a 3px */
                    right: 3px;  /* Ridotto da 5px a 3px */
                    background: rgba(255, 255, 255, 0.9);
                    border: 2px solid #2196F3;
                    border-radius: 4px;  /* Ridotto da 6px a 4px */
                    padding: 2px 4px;  /* Ridotto da 4px 8px a 2px 4px */
                    font-weight: bold;
                    font-size: 10px;  /* Ridotto da 12px a 10px */
                    color: #2196F3;
                    z-index: 100;
                    box-shadow: 0 2px 8px rgba(0,0,0,0.1);
                }
                
                #myChart {
                    width: 100% !important;
                    height: 100% !important;
                    min-height: 150px;
                    border: 1px solid #ccc;
                    border-radius: 4px;
                    margin: 0 !important;  /* Aggiunto margin: 0 */
                    padding: 0 !important;  /* Aggiunto padding: 0 */
                }
                
                .mobile-buttons {
                    display: none;
                }
            }
        </style>
    )";
}