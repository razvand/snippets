;;
;; Editing configuration
;;

(setq global-font-lock-mode t)
(setq x-select-enable-clipboard t)
(setq c-default-style "linux")
(add-hook 'lisp-mode-hook '(lambda ()
			     (local-set-key (kbd "RET") 'newline-and-indent)))
(require 'cc-mode)
(define-key c-mode-base-map (kbd "RET") 'newline-and-indent)
(setq-default indent-tabs-mode t)

;; set backup directory
(setq backup-directory-alist
      `((".*" . , "~/.emacs.d/backup")))
(setq
 backup-by-copying t      ; don't clobber symlinks
 delete-old-versions t
 kept-new-versions 6
 kept-old-versions 2
 version-control t)       ; use versioned backups

;;
;; Org-Mode configuration (http://orgmode.org/)
;;

;; The following lines are always needed.  Choose your own keys.
(add-to-list 'auto-mode-alist '("\\.org\\'" . org-mode))
(add-to-list 'auto-mode-alist '("\\.org_archive\\'" . org-mode))
(add-to-list 'auto-mode-alist '("\\.txt\\'" . org-mode))
(add-hook 'org-mode-hook 'turn-on-font-lock) ; not needed when global-font-lock-mode is on
(setq org-todo-keywords
      '((sequence "TODO" "WAITING" "MONITOR" "VERIFY" "FEEDBACK" "|" "DONE" "DELEGATED" "ONHOLD" "REJECTED")))
(global-set-key "\C-cl" 'org-store-link)
(global-set-key "\C-ca" 'org-agenda)
(global-set-key "\C-cb" 'org-iswitchb)

;;
;; Tab Bar Mode configuration (http://www.emacswiki.org/emacs/TabBarMode)
;;

(require 'tabbar)
(tabbar-mode 1)

(global-set-key (kbd "C-x <right>") 'tabbar-forward)
(global-set-key (kbd "C-x C-<right>") 'tabbar-forward)
(global-set-key (kbd "C-x <left>") 'tabbar-backward)
(global-set-key (kbd "C-x <up>") 'tabbar-forward-group)
(global-set-key (kbd "C-x <down>") 'tabbar-backward-group)

;;
;; Window and aspect configuration
;;

(defun toggle-fullscreen (&optional f)
  (interactive)
  (let ((current-value (frame-parameter nil 'fullscreen)))
    (set-frame-parameter nil 'fullscreen
			 (if (equal 'fullboth current-value)
			     (if (boundp 'old-fullscreen) old-fullscreen nil)
			   (progn (setq old-fullscreen current-value)
				  'fullboth)))))

;; (global-set-key [f11] 'toggle-fullscreen)
;; Make new frames fullscreen by default. Note: this hook doesn't do
;; anything to the initial frame if it's in your .emacs, since that file is
;; read _after_ the initial frame is created.
;; (add-hook 'after-make-frame-functions 'toggle-fullscreen)
;; Start in fullscreen mode
;; (toggle-fullscreen)

;; (menu-bar-mode -1)
(tool-bar-mode -1)
(scroll-bar-mode -1)

;; Hide splash-screen and startup-message
(setq inhibit-splash-screen t)
(setq inhibit-startup-message t)

;; Hide splash-screen and startup-message
(setq inhibit-splash-screen t)
(setq inhibit-startup-message t)

(defun x11-maximize-frame ()
  "Maximize the current frame (to full screen)"
  (interactive)
  (x-send-client-message nil 0 nil "_NET_WM_STATE" 32 '(2 "_NET_WM_STATE_MAXIMIZED_HORZ" 0))
  (x-send-client-message nil 0 nil "_NET_WM_STATE" 32 '(2 "_NET_WM_STATE_MAXIMIZED_VERT" 0)))

(defun x11-maximize-frame-vertical ()
  "Maximize the current frame (to full screen)"
  (interactive)
  (x-send-client-message nil 0 nil "_NET_WM_STATE" 32 '(2 "_NET_WM_STATE_MAXIMIZED_VERT" 0)))

(defun kill-other-buffers ()
  "Kill all other buffers."
  (interactive)
  (mapc 'kill-buffer (delq (current-buffer) (buffer-list))))

;; browser configuration
(setq browse-url-generic-program (executable-find "x-www-browser"))

;; disable blinking cursor
(blink-cursor-mode -1)

;; white space management
(require 'whitespace)
(setq whitespace-style '(face trailing tab-mark))
(global-whitespace-mode 1)

;; automatic startup connection to Freenode
; (erc :server "irc.freenode.net" :port 6667 :nick "razvand")

;; use iswitch
(iswitchb-mode 1)
(setq iswitchb-buffer-ignore '("^ " "*Completions*" "*Shell Command
               Output*" "*Messages*" "Async Shell Command" "*BBDB*"
               "*scratch*" "bbdb" ".newsrc-dribble" ".*_archive"
               "*Help*" "*Disabled Command*" "*Buffer List*"))

(set-default-font "Monospace 10")
