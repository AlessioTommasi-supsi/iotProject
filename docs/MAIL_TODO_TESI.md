elenco delle richieste minime che dobbiamo riuscire a raggiungere:
 
1_ acquisizione di tutti i segnali analogici: tensione – corrente – resistenza – termocoppia – pt100
2_ possibilità di impostazione da parte dell’utente dei seguenti parametri:
                
Per ingresso in tensione: inizio scala – fondo scala 
Per ingresso in corrente: inizio scala – fondo scala
Per ingresso in termocoppia: tipo di termocoppia
Per ingresso (rtd) tipo Pt100 ad esempio: tipo di temo resistenza
 
3_ possibilità di leggere ogni grandezza su modbus RTU
 
4_ possibilità di interrogare mediante modbus RTU master un altro dispositivo e rileggere i parametri mediante interfaccia web e seriale modbus RTU slave
 
5_ gestione uscite analogiche:
                ogni uscita potrà essere associata dall’utente ad uno degli ingressi analogici
esempio: l’utilizzatore vuole leggere una tensione d’ingresso 0…10V e vuole che a questo 0…10V corrisponda un’uscita analogica 0…10V
                prevedere tutte le impostazioni che l’utente può effettuare per configurare le uscite
 
6_ gestione delle uscite digitali:
                ogni uscita digitale potrà essere associata ad uno degli ingressi analogici o digitali.
                Se associata ad un ingresso digitale la funzionalità sarà del tipo: se ingresso attivo allora uscita attiva
Se associato ad un ingresso analogico allora dovremo definire l’uscita digitale come una sorta di allarme, esempio:
L’utente vuole leggere una corrente 0…20mAdc e impostare una soglia di allarme (che può essere allarme di minima o di massima) ad un determinato valore impostabile (nel ns esempio consideriamo sgolia di massima e valore di soglia di 10mA).
Quando l’ingresso analogico supererà i 10mA letti allora l’uscita corrispondente verrà chiusa
 
7_ documento di sintesi e spiegazione di tutto il software che dovrà comunque essere commentato opportunamente
 
8_ step di verifica di tutte le funzionalità e spiegazione di tutto il software prima della sessione d’esame
 
9_ questo punto è un plus :implementazione Ethernet con protocollo  modbus TCP/IP