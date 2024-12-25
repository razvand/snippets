(setq user-mail-address "razvan.deaconescu@upb.ro"
      user-full-name "Razvan Deaconescu"
      gnus-local-organization "Departamentul de Calculatoare")

;; You need this to be able to list all labels in gmail
; (setq gnus-ignored-newsgroups "")

;; Disable agent.
(setq gnus-agent nil)

(setq gnus-select-method
      '(nnimap "Mail"
		(nnimap-address "localhost")
		(nnimap-server-port "imap")
		(nnimap-stream network)
		(nnimap-authenticator login)
		(nnimap-authinfo-file "~/.authinfo")))

;; Prefer plain text
(setq mm-discouraged-alternatives '("text/html" "text/richtext"))

(defun cg-feed-msmtp ()
  (if (message-mail-p)
      (save-excursion
	(let* (
	       (from
		(save-restriction
		  (message-narrow-to-headers)
		  (message-fetch-field "from")))
	       (account
		(cond
		 ((string-match "razvan@rosedu.org" from) "rosedu.org")
		 ((string-match "razvan.deaconescu@cs.pub.ro" from) "cs.pub.ro")
		 ((string-match "razvan.deaconescu@upb.ro" from) "upb.ro")
		 ((string-match "razvan@swarm.cs.pub.ro" from) "swarm.cs.pub.ro")
		 ((string-match "razvand@gmail.com" from) "gmail.com")
		 ((string-match "razvand@unikraft.io" from) "unikraft.io")
		 )
		)
	       )
	  (setq message-sendmail-extra-arguments (list '"-a" account))
	  )
	)
    )
  )

(setq message-sendmail-envelope-from 'header)
(add-hook 'message-send-mail-hook 'cg-feed-msmtp)

(setq message-send-mail-function 'message-send-mail-with-sendmail)
(setq sendmail-program "/usr/bin/msmtp")

(setq gnus-posting-styles
      '(
       ((header "from" ".*razvan.deaconescu@upb.ro")
        (eval (setq gnus-message-archive-group "nnimap+Mail:upb.ro/razvan.deaconescu/Sent Items")))
       ((header "from" ".*razvan.deaconescu@cs.pub.ro")
        (eval (setq gnus-message-archive-group "nnimap+Mail:upb.ro/razvan.deaconescu/Sent Items")))
       ((header "from" ".*razvand@gmail.com")
        (eval (setq gnus-message-archive-group "nnimap+Mail:gmail.com/razvand/[Gmail]/Sent Mail")))
       ((header "from" ".*razvand@unikraft.io")
        (eval (setq gnus-message-archive-group "nnimap+Mail:unikraft.io/razvand/[Gmail]/Sent Mail")))
       ((header "from" ".*razvan@rosedu.org")
        (eval (setq gnus-message-archive-group "nnimap+Mail:rosedu.org/razvan/[Gmail]/Sent Mail")))
       ((header "from" ".*razvan@swarm.cs.pub.ro")
        (eval (setq gnus-message-archive-group "nnimap+Mail:swarm.cs.pub.ro/razvan/Sent")))
       ))

;; don't bugger me with dribbles
(setq gnus-always-read-dribble-file t)
;; don't bugger me with session password
(setq imap-store-password t)

;; mark Gcc (group Cc) messages as read
(setq gnus-gcc-mark-as-read t)

;; archive sent messages
(setq gnus-message-archive-group "nnimap+Mail:Sent")

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

; https://emacs.stackexchange.com/questions/39415/how-to-clear-underlines-after-disabling-flyspell
(flyspell-mode 0)

; https://emacs.stackexchange.com/questions/39167/bbdb-buffer-always-pops-up
(require 'bbdb)
(require 'bbdb-gnus)
(bbdb-initialize 'gnus 'message)
(add-hook 'gnus-startup-hook 'bbdb-insinuate-gnus)
(add-hook 'gnus-startup-hook 'bbdb-insinuate-message)
;;(add-hook 'message-setup-hook 'bbdb-mail-aliases)
(setq bbdb-use-pop-up nil)
(setq bbdb-mua-pop-up nil)
(setq bbdb-mua-auto-update-p nil)

;; If you don't live in Northern America, you should disable the
;; syntax check for telephone numbers by saying
(setq bbdb-north-american-phone-numbers-p nil)
;; Tell bbdb about your email address:
(setq bbdb-user-mail-names
      (regexp-opt '("razvan.deaconescu@cs.pub.ro"
		    "razvan.deaconescu@upb.ro"
		    "razvand@gmail.com"
		    "razvan@rosedu.org"
		    "razvand@unikraft.io"
		    "razvan.deaconescu@lpic.ro"
		    "razvan@swarm.cs.pub.ro")))

;; use bbdb in gnus (http://bbdb.sourceforge.net/bbdb.html#SEC2)

;; https://ding.gnus.narkive.com/ymacizFO/bbdb-v3-integration
;; https://blog.petitepomme.net/post/28547901478/installing-and-configuring-bbdb-3

;; file where things will be saved
; (setq bbdb-file "~/.emacs.d/bbdb")
;(require 'bbdb-loaddefs)

(bbdb-mua-auto-update-init 'gnus 'message) ;; use 'gnus for incoming messages too
;(setq bbdb-mua-auto-update-p 'query) ;; or 'create to create without asking

;; What do we do when invoking bbdb interactively.
(setq bbdb-mua-update-interactive-p '(query . create))

;(setq bbdb-update-records-p '(query . create))

(setq bbdb-complete-mail-allow-cycling t)

;; size of the bbdb popup
(setq bbdb-pop-up-window-size 10)

;; Make sure we look at every address in a message and not only the
;; first one
(setq bbdb-message-all-addresses t)
(add-hook 'message-setup-hook 'bbdb-mail-aliases)

;; use ; on a message to invoke bbdb interactively
(add-hook
 'gnus-summary-mode-hook
 (lambda ()
   (define-key gnus-summary-mode-map (kbd ";") 'bbdb-mua-edit-field)
   ))

;; auto-complete emacs address using bbdb UI
(add-hook 'message-mode-hook
          '(lambda ()
             (flyspell-mode t)
             (local-set-key (kbd "TAB") 'bbdb-complete-name)))

;; Doesn't work in BBDB 3.2.
;;(add-hook 'message-setup-hook 'bbdb-define-all-aliases)
