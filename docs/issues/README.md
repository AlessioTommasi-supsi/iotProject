## watchdog triggered, deadlock problem when try register same register multiple time, fix crash and reboot problem

### Error details:

shown in Serizl monitor arduino IDE

``` 
Recording value: 16381 at address 123
Read value of 16381 from holding register address 123
Recording value: 16381 at address 123
E (119569) task_wdt: Task watchdog got triggered. The following tasks/users did not reset the watchdog in time:
E (119569) task_wdt:  - async_tcp (CPU 1)
E (119569) task_wdt: Tasks currently running:
E (119569) task_wdt: CPU 0: IDLE0
E (119569) task_wdt: CPU 1: IDLE1
E (119569) task_wdt: Aborting.
E (119569) task_wdt: Print CPU 1 backtrace
```


### Solution:

- [x] Fix deadlock problem when try register same register multiple time 
- [x] Fix crash and reboot problem  when try register same register multiple time
- [x] Fix watchdog triggered problem when try register same register multiple time

### Changes:

linea che causava errore: principale: 
nel file: `src/model/SystemState.cpp`  nella funzione `void SystemState::startRecordingRegister(int addr, int milliseconds)
`

```cpp
std::lock_guard<std::mutex> lock(recordingMutex);
```

togliendo questo ho risolto anche monitor di piu registri in parallelo, il watchdog si triggerava perche sistema andava in deadlock!


### Other solutions tried that did not work: or not optimized:

#### 1 Disable watchdog timer

```cpp
1.1
   setup() {
    ...
        // Disable watchdog timer
        esp_task_wdt_config_t wdt_config = {
        .timeout_ms = 0, // 0 per disabilitare
        .idle_core_mask = 0, // Disabilita il watchdog per entrambi i core
        .trigger_panic = false // Non attivare il panic handler
        };
        esp_task_wdt_init(&wdt_config); // Passa la configurazione alla funzione

        esp_task_wdt_delete(xTaskGetIdleTaskHandleForCPU(0)); // Disabilita il watchdog per il core 0
        esp_task_wdt_delete(xTaskGetIdleTaskHandleForCPU(1)); // Disabilita il watchdog per il core 1
        esp_task_wdt_delete(NULL);
        
        ...
    */
    // Disabilita il watchdog RTC
    /*non funziona
    rtc_wdt_protect_off();
    rtc_wdt_disable();
    }

```


```cpp
1.2
   setup() {
    ...
       rtc_wdt_protect_off();
       rtc_wdt_disable();
    ...

```

#### Reference link for this solution:
[Link arduino form](
    https://forum.arduino.cc/t/esp32-how-to-disable-watchdog-timer-for-http-server/970451
)

[Link thead](
    https://stackoverflow.com/questions/51750377/how-to-disable-interrupt-watchdog-in-esp32-or-increase-isr-time-limit
)