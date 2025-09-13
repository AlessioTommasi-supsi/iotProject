#include "cssControlGroup.h"

String cssControlGroup::getCSS() {
    return R"(
        <style>
            .control-group {
                display: flex;
                align-items: center;
                gap: 10px;
                background: #f9f9f9;
                padding: 8px 12px;
                border-radius: 6px;
                border: 1px solid #e0e0e0;
                transition: all 0.3s ease;
            }
            
            .control-group:hover {
                background: #f0f0f0;
                border-color: #d0d0d0;
                box-shadow: 0 2px 4px rgba(0,0,0,0.1);
            }
            
            .control-group label {
                font-weight: bold;
                white-space: nowrap;
                margin: 0;
                font-size: 14px;
                color: #333;
                min-width: 80px;
            }
            
            .control-group input, .control-group select {
                margin: 0;
                padding: 4px 8px;
                border: 1px solid #ccc;
                border-radius: 4px;
                font-size: 14px;
                background: white;
                transition: border-color 0.3s ease;
            }
            
            .control-group input:focus, .control-group select:focus {
                outline: none;
                border-color: #2196F3;
                box-shadow: 0 0 0 2px rgba(33, 150, 243, 0.1);
            }
            
            .control-group input[type="number"] {
                width: 80px;
            }
            
            .control-group select {
                cursor: pointer;
                flex: 1;
                min-width: 120px;
            }
            
            .control-group .unit-label {
                font-size: 12px;
                color: #666;
                font-weight: normal;
            }
            
            /* Mobile adjustments */
            @media (max-width: 1023px) {
                .control-group {
                    padding: 10px 12px;
                }
                
                .control-group label {
                    font-size: 13px;
                    min-width: 70px;
                }
                
                .control-group input, .control-group select {
                    font-size: 13px;
                    padding: 6px 8px;
                }
                
                .control-group input[type="number"] {
                    width: 70px;
                }
                
                .control-group select {
                    min-width: 100px;
                }
            }
            
            /* Disabled state */
            .control-group.disabled {
                opacity: 0.6;
                pointer-events: none;
            }
            
            /* Error state */
            .control-group.error input, .control-group.error select {
                border-color: #f44336;
            }
            
            /* Success state */
            .control-group.success input, .control-group.success select {
                border-color: #4CAF50;
            }
        </style>
    )";
}