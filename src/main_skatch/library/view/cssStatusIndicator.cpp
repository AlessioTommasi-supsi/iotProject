#include "cssStatusIndicator.h"

String cssStatusIndicator::getCSS() {
    return R"(
        <style>
            .status-indicator {
                position: fixed;
                top: 10px;
                right: 10px;
                background: white;
                border: 2px solid #ddd;
                border-radius: 6px;
                padding: 8px 12px;
                font-weight: bold;
                font-size: 14px;
                z-index: 1000;
                box-shadow: 0 2px 4px rgba(0,0,0,0.1);
                transition: all 0.3s ease;
            }
            
            .status-indicator.success {
                color: #4CAF50;
                border-color: #4CAF50;
                background-color: #f8fff8;
            }
            
            .status-indicator.info {
                color: #2196F3;
                border-color: #2196F3;
                background-color: #f0f8ff;
            }
            
            .status-indicator.warning {
                color: #FF9800;
                border-color: #FF9800;
                background-color: #fff8f0;
            }
            
            .status-indicator.error {
                color: #f44336;
                border-color: #f44336;
                background-color: #fff0f0;
            }
            
            .status-indicator.default {
                color: #666;
                border-color: #ddd;
                background-color: white;
            }
            
            /* Mobile positioning */
            @media (max-width: 1023px) {
                .status-indicator {
                    position: static;
                    margin: 10px 0;
                    text-align: center;
                }
            }
            
            /* Pulse animation for active states */
            .status-indicator.pulse {
                animation: pulse 2s infinite;
            }
            
            @keyframes pulse {
                0% { transform: scale(1); }
                50% { transform: scale(1.05); }
                100% { transform: scale(1); }
            }
        </style>
    )";
}