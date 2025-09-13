#include "cssToggleButton.h"

String cssToggleButton::getCSS() {
    return R"(
        <style>
            /* iOS-style toggle switch */
            .ios-toggle-switch {
                position: relative;
                display: inline-block;
                width: 20px;
                height: 28px;
                margin: 0;
            }
            
            .ios-toggle-switch input {
                opacity: 0;
                width: 0;
                height: 0;
            }
            
            .ios-toggle-slider {
                position: absolute;
                cursor: pointer;
                top: 0;
                left: 0;
                right: 0;
                bottom: 0;
                background-color: #ccc;
                transition: .4s;
                border-radius: 28px;
            }
            
            .ios-toggle-slider:before {
                position: absolute;
                content: "";
                height: 22px;
                width: 22px;
                left: 3px;
                bottom: 3px;
                background-color: white;
                transition: .4s;
                border-radius: 50%;
            }
            
            .ios-toggle-switch input:checked + .ios-toggle-slider {
                background-color: #2196F3;
            }
            
            .ios-toggle-switch input:focus + .ios-toggle-slider {
                box-shadow: 0 0 1px #2196F3;
            }
            
            .ios-toggle-switch input:checked + .ios-toggle-slider:before {
                transform: translateX(50px);
            }
            
            /* Hover effects */
            .ios-toggle-slider:hover {
                background-color: #bbb;
            }
            
            .ios-toggle-switch input:checked + .ios-toggle-slider:hover {
                background-color: #1976D2;
            }
            
            /* Disabled state */
            .ios-toggle-switch input:disabled + .ios-toggle-slider {
                cursor: not-allowed;
                opacity: 0.6;
            }
        </style>
    )";
}