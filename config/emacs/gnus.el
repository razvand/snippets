(setq user-mail-address "razvan.deaconescu@cs.pub.ro"
      user-full-name "Razvan Deaconescu"
      gnus-local-organization "Departamentul de Calculatoare")

;; You need this to be able to list all labels in gmail
; (setq gnus-ignored-newsgroups "")

; remote IMAP server connection
;(setq gnus-select-method
;      '(nnimap "swarm"
;	       (nnimap-address "swarm.cs.pub.ro")
;	       (nnimap-server-port 993)
;	       (nnimap-authenticator login)
;	       (nnimap-stream ssl)))

(setq gnus-select-method
      '(nnimap "Mail"
	       (nnimap-address "localhost")
	       (nnimap-stream network)
	       (nnimap-authenticator login)
	       (nnimap-authinfo-file "~/.authinfo")))

;(setq gnus-select-method
;       '(nnmaildir "Mail"
;                   (directory "~/offlineimap/swarm/razvan/")
;                   (directory-files nnheader-directory-files-safe)
;                   (get-new-mail nil)))

;(setq imap-shell-program "dovecot -c ~/.dovecotrc --exec-mail imap")
;(setq gnus-select-method
;      '(nnimap "Mail"
;	       (nnimap-stream shell)))

;; Prefer plain text
(setq mm-discouraged-alternatives '("text/html" "text/richtext"))

(setq send-mail-function 'smtpmail-send-it
      message-send-mail-function 'smtpmail-send-it
      starttls-use-gnutls t
      starttls-gnutls-program "gnutls-cli"
      starttls-extra-arguments '("--insecure")
      smtpmail-starttls-credentials '(("swarm.cs.pub.ro" 2525 nil nil))
      smtpmail-gnutls-credentials '(("smtp.gmail.com" 587 nil nil))
      smtpmail-auth-credentials '(("swarm.cs.pub.ro" 2525 "razvan" "Eeth]oh2"))
      smtpmail-default-smtp-server "swarm.cs.pub.ro"
      smtpmail-smtp-server "swarm.cs.pub.ro"
      smtpmail-smtp-service 2525
      smtpmail-local-domain "cs.pub.ro")

(setq gnus-posting-styles
      '(
	("^INBOX.rosedu"
	 (name "Razvan Deaconescu")
	 (address "razvan@rosedu.org")
	 (organization "ROSEdu"))
	("^INBOX.projects.lpic"
	 (name "Razvan Deaconescu")
	 (address "razvan.deaconescu@lpic.ro")
	 (organization "Academia CISCO - lpic.ro"))
	("nnml:*"
	 (From (with-current-buffer gnus-article-buffer
		 (message-fetch-field "to"))))
	((header "to" "razvan.deaconescu@cs.pub.ro")
	 (name "Razvan Deaconescu")
	 (address "razvan.deaconescu@cs.pub.ro")
	 (organization "Departamentul de Calculatoare"))
	((header "to" "razvan@rosedu.org")
	 (name "Razvan Deaconescu")
	 (address "razvan@rosedu.org")
	 (organization "ROSEdu"))
	((header "to" "razvan.deaconescu@lpic.ro")
	 (name "Razvan Deaconescu")
	 (address "razvan.deaconescu@lpic.ro")
	 (organization "Academia CISCO"))
	((header "to" "razvan.deaconescu@stagiipebune.ro")
	 (name "Razvan Deaconescu")
	 (address "razvan.deaconescu@stagiipebune.ro")
	 (organization "Stagii pe Bune"))
))

;; don't bugger me with dribbles
(setq gnus-always-read-dribble-file t)
;; don't bugger me with session password
(setq imap-store-password t)

;; mark Gcc (group Cc) messages as read
(setq gnus-gcc-mark-as-read t)

;; archive sent messages
(setq gnus-message-archive-group "INBOX.Sent")
(setq gnus-message-archive-method '(nnimap "Mail"))

;; Wrap at 72 cols.
(add-hook 'message-mode-hook
          '(lambda()
             (turn-on-auto-fill)
             (setq fill-column 72)
             )
          )

;; scan for new messages
(gnus-demon-add-handler `gnus-demon-scan-news 5 5)
(gnus-demon-init)

;; Fetch only part of the article if we can.  I saw this in someone
;; else's .gnus
(setq gnus-read-active-file 'some)

;; Tree view for groups.  I like the organisational feel this has.
(add-hook 'gnus-group-mode-hook 'gnus-topic-mode)

;; Threads!  I hate reading un-threaded email -- especially mailing
;; lists.  This helps a ton!
(setq gnus-summary-thread-gathering-function
      'gnus-gather-threads-by-subject)

;; Also, I prefer to see only the top level message.  If a message has
;; several replies or is part of a thread, only show the first
;; message.  'gnus-thread-ignore-subject' will ignore the subject and
;; look at 'In-Reply-To:' and 'References:' headers.
(setq gnus-thread-hide-subtree t)
(setq gnus-thread-ignore-subject t)

;; disable format flowed (http://www.emacswiki.org/emacs/GnusFormatFlowed)
(setq fill-flowed-display-column nil)
(add-hook 'gnus-article-mode-hook
	  (lambda ()
	    (setq
	     truncate-lines nil
	     word-wrap t)))
(setq-default
 gnus-summary-line-format "%U%R%z %(%&user-date;  %-20,20f  %B%s%)\n"
 gnus-user-date-format-alist '((t . "%Y-%m-%d %H:%M"))
 gnus-summary-thread-gathering-function 'gnus-gather-threads-by-references
 gnus-thread-sort-functions '(gnus-thread-sort-by-date)
 gnus-sum-thread-tree-false-root ""
 gnus-sum-thread-tree-indent " "
 gnus-sum-thread-tree-leaf-with-other "├► "
 gnus-sum-thread-tree-root ""
 gnus-sum-thread-tree-single-leaf "╰► "
 gnus-sum-thread-tree-vertical "│")
;(setq gnus-summary-line-format "%O%U%R%z%d %B%(%[%4L: %-22,22f%]%) %s\n")
;(setq gnus-summary-mode-line-format "Gnus: %p [%A / Sc:%4z] %Z")

;; http://www.xsteve.at/prg/gnus/
(setq gnus-ignored-from-addresses "Razvan Deaconescu")

(setq message-kill-buffer-on-exit t)

;; configure browser
(setq gnus-button-url 'browse-url-generic
      browse-url-browser-function gnus-button-url)

;; use bbdb in gnus (http://bbdb.sourceforge.net/bbdb.html#SEC2)
(add-hook 'gnus-startup-hook 'bbdb-insinuate-gnus)