# Ajarpam
Ajarpam is a silly demo PAM module with a chance of being useful. It lets you
provide a weak/quick password in a totally insecure way for your screenlocker, for
example. Instead of shutting the door and locking it, you leave it ajar.
(This means you would have a different password for your screensaver)

## Build
```
make
```

## Install
If you are running Debian, you probably want to copy the PAM module (pam_ajar.so) to
/lib/x86_64-linux-gnu/security/
If you are running Archlinux: /lib/security/

You might find the following command useful to find the right target path
```
$ ldd `which passwd`  | grep libpam   # you can do ldd =passwd if using zsh
        libpam.so.0 => /lib/x86_64-linux-gnu/libpam.so.0 ...
```


## Usage
If for example you are using mate-screensaver, you can create a custom pam
configuration file and place it at /etc/pam.d/mate-screensaver
Cinnamon uses /etc/pam.d/cinnamon-screensaver


Example of pam.d configuration file:
```
#%PAM-1.0

# Fedora Core
auth       sufficient   pam_ajar.so [pass=jkl/]
auth       include      system-auth
auth       optional     pam_gnome_keyring.so
account    include      system-auth
password   include      system-auth
session    include      system-auth

```

This line indicates that the "passing" of this module is enough to authenticate us.
```
auth       sufficient   pam_ajar.so [pass=jkl/]
```

