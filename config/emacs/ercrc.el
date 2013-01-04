;;
;; ERC configuration (http://www.emacswiki.org/emacs/ERC)
;;

;; user id
(setq erc-email-userid "razvan@rosedu.org")
(setq erc-user-full-name "Razvan Deaconescu")

;; http://www.emacswiki.org/emacs/ErcAutoAway
(setq erc-autoaway-idle-seconds 600)
(setq erc-autojoin-channels-alist
      '(("freenode.net" "#cs_so" "#rosedu" "#acm-seerc" "#vmxl4" "#cs_uso")))

(setq erc-echo-notices-in-minibuffer-flag t)

;;(erc-spelling-mode 1)
(require 'smiley)

;; http://www.emacswiki.org/emacs/ErcLogging
(setq erc-log-channels-directory "~/.erc/logs/")
(setq erc-save-buffer-on-part t)
(setq erc-hide-timestamps t)

;; http://www.emacswiki.org/emacs/ErcAutoQuery
(setq erc-auto-query 'window)

;; http://www.emacswiki.org/emacs/ErcChannelTracking
(setq erc-current-nick-highlight-type 'nick)
(setq erc-keywords '("\\berc[-a-z]*\\b" "\\bemms[-a-z]*\\b"))

(setq erc-track-exclude-types '("JOIN" "PART" "QUIT" "NICK" "MODE"
				"324" "329" "332" "333" "353" "477"))
(setq erc-track-use-faces t)
(setq erc-track-faces-priority-list
      '(erc-current-nick-face erc-keyword-face))
(setq erc-track-priority-faces-only 'all)
(setq erc-hide-list '("JOIN" "PART" "QUIT"))