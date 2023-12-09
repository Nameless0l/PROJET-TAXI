\LoadClass[a4paper,12pt]{article} % Classe du document

%--------------------- Packages ------------------------

\RequirePackage[english]{babel} %Langue du document
\RequirePackage[utf8]{inputenc} %Caractères spéciaux
%\RequirePackage[section]{placeins}%Pour placement de section
\RequirePackage[T1]{fontenc} %Quelques lettres qui sont pas inclus dans UTF-8
\RequirePackage{mathtools} %Paquet pour des équations et symboles mathématiques
\RequirePackage{siunitx} %Pour écrire avec la notation scientifique (Ex.: \num{2e+9})
\RequirePackage{float} %Pour placement d'images
\RequirePackage{graphicx} %Paquet pour insérer des images
\RequirePackage[justification=centering]{caption} %Pour les légendes centralisées
\RequirePackage{subcaption}
\RequirePackage{wallpaper}
\RequirePackage{nomencl}
%\RequirePackage{times}
%\makenomenclature
\RequirePackage{fancyhdr}
%\pagestyle{fancy}
%\fancyheadoffset{1cm}
%\setlength{\headheight}{2cm}
\RequirePackage{url}
\RequirePackage[hidelinks]{hyperref}%Paquet pour insérer légendes dans des sous-figures comme Figure 1a, 1b
\RequirePackage[left=2.5cm,right=2.5cm,top=2cm,bottom=3.5cm]{geometry} %Configuration de la page
\renewcommand{\footrulewidth}{1pt} %épaisseur de la ligne du bas de page
\renewcommand{\headrulewidth}{1pt} %épaisseur de la ligne du bas de page

%-------------------- Informations sur le rapport ----------------------

\newcommand{\UE}[1]{\renewcommand{\UE}{#1}}
\newcommand{\sujet}[1]{\renewcommand{\sujet}{#1}}
\newcommand{\titre}[1]{\renewcommand{\titre}{#1}}
\newcommand{\Encadrants}[1]{\renewcommand{\Encadrants}{#1}}
\newcommand{\eleves}[1]{\renewcommand{\eleves}{#1}}

\newcommand{\fairemarges}{
\makenomenclature
\pagestyle{fancy}
\fancyheadoffset{1cm}
\setlength{\headheight}{2cm}
\fancyfootoffset{1cm}
\setlength{\footheight}{2cm}

\rhead{\nouppercase{\leftmark}}
\rfoot{\thepage}
\cfoot{Rapport - \textbf{\titre}}
\lfoot{\UE}
}

\newcommand{\fairepagedegarde}{
\begin{titlepage}

\ThisLRCornerWallPaper{0.5}{logos/ECC2.jpg}
	\centering %Centraliser le contenu
	\includegraphics[width=0.6\textwidth]{logos/LOGO.jpg}\par\vspace{0.75cm} %Insertion du logo
	{\scshape\Large National Advanced School of Engineering Yaounde\\[0.2cm]Cours de Système d'exploitation \par} %Nom de l'université
	\vspace{0.6cm}%Espace de 1,5cm
	{\scshape\Large \UE \\ \sujet \\ \textbf{operating system course}} %sous-titre
	\vspace{0.7cm}%Espace de 1cm
    \rule{\linewidth}{0.2 mm} \\[0.4 cm]
	{\huge\bfseries \titre \par} \
    \rule{\linewidth}{0.2 mm} \\[1.1 cm]
	\vspace{0.6cm}%Espace de 3cm
    
	\begin{minipage}{0.5\textwidth} %Minipage pour faire deux colonnes
		\begin{flushleft} \large %Envoyer à gauche
		\emph{\textbf{Supervisors :}}\\ %Pour le titre au dessus des noms à gauche
        \eleves\\ %Remplacer pour chacun
		\end{flushleft}
	\end{minipage}
 
	%\begin{minipage}{0.4\textwidth}
		%\begin{flushright} \large
		%\emph{\textbf{Encadrants :}} \\
		% \Encadrants\\
	%	\end{flushright}
	%\end{minipage}\\[4cm]
    
	%\vfil
 \begin{flushright}
	{\large \today} %Affichage de la date
\end{flushright}


\end{titlepage}
}

%\newcommand{\tableofcontents}{
%\tableofcontents{table of contents}
%\newpage}

\newcommand{\insererfigure}[4]{
\begin{figure}[ht]
\centering
\includegraphics[height=#2]{#1}
\caption{#3}
\label{fig: #4}
\end{figure}
}



