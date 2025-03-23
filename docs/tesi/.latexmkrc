# Imposta il percorso per pdflatex
$pdflatex = 'pdflatex %O %S';

# Aggiungi il percorso al PATH
$ENV{'PATH'} = '/Library/TeX/texbin:' . $ENV{'PATH'};