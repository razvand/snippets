# Configure E-mail

These are the steps required to configure e-mail for Gnus.

Install packages:

```console
sudo apt -yqq install emacs bbdb bbdb3 msmtp isync dovecot-imapd libsasl2-modules-kdexoauth2
```

Create directories to store local e-mails for `mbsync`:

```console
mkdir -p ~/.mbsync/upb.ro/razvan.deaconescu
mkdir -p ~/.mbsync/gmail.com/razvand
mkdir -p ~/.mbsync/unikraft.io/razvand
mkdir -p ~/.mbsync/rosedu.org/razvan
mkdir -p ~/.mbsync/swarm.cs.pub.ro/razvan
mkdir -p ~/.mbsync/eduapps.ro/razvan.deaconescu
```

Copy configurations of Emacs, Gnus, `mbsync` and `msmtprc`:

```console
cp ../emacs/emacs.el ~/.emacs
cp ../emacs/gnus.el ~/.gnus.el
cp mbsyncrc ~/.mbsyncrc
cp msmtprc ~/.msmtprc
cp authinfo ~/.authinfo
mkdir -p ~/.oauth2/
cp mutt_oauth2.py ~/.oauth2/mutt_oauth2.py
```

Fill `~/.authinfo` with passwords.

Configure OAUTH2 for UPB account (using Outlook) following instructions [here](https://simondobson.org/2024/02/03/getting-email/).

Run `mbsync` to populate local e-mail directories:

```console
mbsync -a
```

Configure Dovecot, as shown [here](https://thehelpfulidiot.com/making-an-automatic-email-backup):

- Edit the `/etc/dovecot/conf.d/10-mail.conf` file.
  Locate the following line:

  ```text
  mail_location = mbox:~/mail:INBOX=/var/mail/%u
  ```

  Comment it out and replace it with:

  ```text
  mail_location=maildir:~/.mbsync/:LAYOUT=fs:INBOX=%h/.mbsync
  ```

- Edit the `/etc/dovecot/conf.d/10-auth.conf` file.
  Replace:

  ```text
  disable_plaintext_auth = yes
  ```

  with:

  ```text
  disable_plaintext_auth = no
  ```

- Edit the `/etc/dovecot/conf.d/15-mailboxes.conf` file.
  Under `namespace inbox {`, add `inbox = yes` like so:

  ```text
  namespace inbox {
    inbox = yes
  ``

  Go down farther and uncomment the blocks about the virtual `all` and `flagged` mailboxes so that it looks like this:

  ```text
  # If you have a virtual "All messages" mailbox:
  mailbox virtual/All {
    special_use = \All
  #  comment = All my messages
  }

  # If you have a virtual "Flagged" mailbox:
  mailbox virtual/Flagged {
    special_use = \Flagged
  #  comment = All my flagged messages
  }
  ```

- Restart Dovecot:

  ```console
  sudo systemctl restart dovecot
  ```

Start Emacs:

```console
emacs -nw
```

In Emacs, run Gnus:

```console
M-x gnus
```

**Note**: If you run Emacs in tmux, use an `xterm` terminal for the proper color scheme.

```console
TERM=xterm-256color emacs -nw
```
