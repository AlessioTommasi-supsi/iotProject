- [x] **Fix Multiplexer**: Complete the implementation for channels and verify the conversion of resistance and other parameters.
- **Assign Modbus Addresses**:
    - Map readings to Modbus addresses from 100 to 200.
    - Associate equivalent values from 200 to 300 with linearization.
- **Implement Modbus Slave Writing**:
    - Handle analog and digital outputs.
    - Replicate data from the master to the slave.
- **Functionality for Alessio**:
    - Ensure the function returns values to Modscan in the format:
        - `3.2 FLOAT`
        - `1 INTEGER`
- **Mapping Details**:
    - **100–200**: Measured quantities (real values read).
    - **200–300**: Modified quantities (processed based on scaling, etc.).
    - **200–201**: Start and end scale (e.g., 5 bar to 100 bar). Implement reading from the slave using OpenModscan commands.
- **Write Holding Register**:
    - Replicate values read by Modscan Master into the range **300–400**.
    - Always replicate either 50 integers or 50 floats.
    - Use the master's Modbus register address as the starting address and the length as the quantity to read.

# GPIO 12 13 14 = A B C

    c0  
    Resistenza cn2 
    rilevato 0 0 1   2.5v  c3
    DOVREBBE ESSERE 0 0 0

    c1 GIUSTO!!!
    tensione non anplif cn10 
    rilevato 1 0 0    0v   c1
    DOVREBBE ESSERE 1 0 0
    SI CON START  MA DOVREBBE LEGGERE 5V E INVECE MI DA 1.03V
![alt text](image-9.png)

    c2 
    tensione CON GUADAGNO 0.3
    rilevato 1 1 0    VEDI IMG   c1
    DOVREBBE ESSERE 0 1 0

![alt text](image-7.png)

![alt text](image-8.png)


    c3 
    tensione CON GUADAGNO 0.2
    rilevato 0 1 0    VEDI IMG   c1
    DOVREBBE ESSERE 1 1 0

    Resistenza cn10 
    rilevato 0 0 1  2.5v  c3
    DOVREBBE ESSERE 0 1 1


    NOTA! SE CLICCO SU START VA GIUSTO!!! REA QUESTO L ERRORE!