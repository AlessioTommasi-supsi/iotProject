## MacOs
Latex extention: 
[Link:](https://marketplace.visualstudio.com/items?itemName=James-Yu.latex-workshop)

Latex prerequisites:
[Miktex:](https://miktex.org/download)

## Windows
Latex extention: 
[Link:](https://marketplace.visualstudio.com/items?itemName=James-Yu.latex-workshop)

Latex prerequisites:
[Miktex:](https://miktex.org/download)
[Perl:](https://strawberryperl.com/)

## Arch
Latex extention: 
[Link:](https://marketplace.visualstudio.com/items?itemName=James-Yu.latex-workshop)


### texlive:
```bash
    sudo pacman -S texlive
```

controlla che sia installato:
```bash
    pdflatex --version
```

per installare librerie aggiuntive:
```bash
    sudo pacman -S LATEX-PACKAGE-NAME
```

---

modifica file **settings.json** come segue:

si trova in questa cartella: /home/none/.config/Code/User/settings.json

oppure Ctrl + shift + p e cerca >user settings.json

aggiungi al file la seguente righe:
 
```json

    // Configurazioni LaTeX Workshop
    "latex-workshop.latex.tools": [
        {
            "name": "pdflatex",
            "command": "pdflatex",
            "args": [
                "-synctex=1",
                "-interaction=nonstopmode",
                "-file-line-error",
                "-output-directory=%OUTDIR%",
                "%DOC%"
            ]
        },
        // Aggiungi un nuovo strumento per spostare il file
        {
            "name": "mv-pdf",
            "command": "mv",
            "args": [
                "%OUTDIR%/%DOCFILE%.pdf",
                "%DIR%"
            ]
        }
    ],
    "latex-workshop.latex.recipes": [
        {
            "name": "Compile and Move PDF",
            "tools": [
                "pdflatex", // Compila il documento e mette tutto in 'out'
                "mv-pdf"    // Sposta il PDF nella cartella principale
            ]
        }
    ],
    "latex-workshop.latex.recipe.default": "Compile and Move PDF",
    "latex-workshop.latex.outDir": "./LatexBuildFiles",

```



oppure compila manualmente da terminale con un terminale nella stessa cartella del file .tex: mettendo tutti i file inutili in una cartella chiamata  ./LatexBuildFiles: 

```bash
    ./prova.tex && mv prova.{aux,log,fls} ./LatexBuildFiles
```

