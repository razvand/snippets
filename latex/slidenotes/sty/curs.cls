% 2012, Razvan Deaconescu, razvan@rosedu.org
%
% Update on ROSEdu curs
% Based on workshop, based itself on osss
% Based on osss, based itself on so.cs.pub.ro
% Based on so.cs.pub.ro by Vlad Dogaru, 2010, based itself on thesis.cs.pub.ro
% Based on thesis.cs.pub.ro by Mircea Bardac, 2008
%
% .cls - class for ROSEdu Lectures ("Cursuri")

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{curs}[2012/09/16]

\LoadClassWithOptions{beamer}


%%% LaTeX Beamer Options %%%

\mode<presentation>
{ \usetheme{Curs} }

% So that we don't have to declare it a bazillion times.
\institute[ROSEdu]{Cursuri ROSEdu}

% Slide-urile cu mai multe părți sunt marcate cu textul (cont.)
\setbeamertemplate{frametitle continuation}[from second]

% Show page frame number.
\setbeamertemplate{footline}[frame number]

% Disable useless navigation symbols.
\setbeamertemplate{navigation symbols}{}

% Show contents at every section beginning. Ripped off from manual.
\AtBeginSection[] % Do nothing for \section*
{
  \begin{frame}<beamer>
    \frametitle{Cuprins}
  \tableofcontents[currentsection]
    \end{frame}
}


%%% Slide format options %%%

\ifdefined\dualscreen
  \usepackage{pgfpages}
  \setbeameroption{show notes on second screen=left}
\fi

\ifdefined\fouronone
  \usepackage{handoutWithNotes}
  \pgfpagesuselayout{4 on 1 with notes}[a4paper,border shrink=5mm]
\else
  \ifdefined\eightonone
    \usepackage{handoutWithNotes}
    \pgfpagesuselayout{8 on 1}[a4paper,border shrink=5mm]
  \fi
\fi


%%% Generic package/commands options %%%

% Romanian Language support
\usepackage{ucs}
\usepackage[utf8x]{inputenc}
\PrerenderUnicode{aâîțșĂÎÂȚȘ}
\usepackage[english,romanian]{babel}

\usepackage{hyperref}   % use \url{http://$URL} or \href{http://$URL}{Name}
\usepackage{underscore} % underscores need not be escaped
\usepackage{booktabs}   % nice looking tables
\usepackage{array}      % column size options in tables

% support for including graphics
\usepackage{graphicx}
\DeclareGraphicsExtensions{.pdf,.png,.jpg}

% Fix verbatim environment: smaller text size.
\let\oldverbatim=\verbatim
\renewenvironment{verbatim}{
  \begin{small}
  \begin{oldverbatim}
  %\vspace*{1em}
}%
{%
  %\vspace*{1em}
  \end{oldverbatim}
  \end{small}
}

% command for specifying TODOs
\newcommand{\todo}[1]{
  \textbf{TODO:} #1 \par
}

% command for formatting file or directory names
\newcommand{\file}[1]{\texttt{#1}}

% command for formatting inline commands
\newcommand{\cmd}[1]{\textbf{\texttt{#1}}}
% command for formatting inline function names
\newcommand{\func}[1]{\textbf{\texttt{#1}}}

\renewcommand{\arraystretch}{1.3}
